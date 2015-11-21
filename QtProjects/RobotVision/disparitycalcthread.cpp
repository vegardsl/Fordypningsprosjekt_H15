#include "disparitycalcthread.h"

using namespace cv;
using namespace std;
//using namespace pcl;


DisparityCalcThread::DisparityCalcThread(QObject *parent) : QObject(parent)
{

}

DisparityCalcThread::~DisparityCalcThread(){

}

void DisparityCalcThread::start(QString appPath)
{
    Size image_size = Size(1280,1024);
    initDisparityCalcThread(appPath,image_size);

    disparityLoop();
}

void DisparityCalcThread::initDisparityCalcThread(QString filePath, cv::Size image_size)
{
    filePath.append("/samples/stereo/stereo_calib.xml");
    qDebug() << "path to calibFile: "+filePath;

    // Read pixel maps from XML file
    cv::FileStorage fs(filePath.toLocal8Bit().constData(), cv::FileStorage::READ);
    qDebug() << "Calibration file procured";
    fs["map_l1"] >> map_l1;
    fs["map_l2"] >> map_l2;
    fs["map_r1"] >> map_r1;
    fs["map_r2"] >> map_r2;
    fs["Q"] >> Q;
    if(map_l1.empty() || map_l2.empty() || map_r1.empty() || map_r2.empty())
    {
        cout << "WARNING: Loading of mapping matrices not successful" << endl;
    }
    const string videoStreamAddress[] = { "http://admin:admin@192.168.0.100:80/video.mjpg", "http://admin:admin@192.168.0.102:80/video.mjpg" };
    videoLeft.beginVideoStream(videoStreamAddress[0],LEFT);
    videoRight.beginVideoStream(videoStreamAddress[1],RIGHT);

    qDebug() << "Running DisparityCalcThread";

    //leftFrameArrived.acquire();
    //rightFrameArrived.acquire();

    //qDebug() << "Both frames arrived";
    bothFramesArrived = true;

    disp8U = Mat(leftGray.rows,leftGray.cols,CV_8UC1);
    disp16S = Mat(leftGray.rows,leftGray.cols,CV_16S);

    bm = StereoBM::create(numDisparities, SADWindowSize);
    sgbm = StereoSGBM::create(minDisparity,numDisparities, SADWindowSize);

    //Ptr<cuda::StereoBM> sbm = cuda::createStereoBM(numDisparities, SADWindowSize);
/*
    bm->setPreFilterCap(61);
    bm->setBlockSize(15);
    bm->setMinDisparity(10);
    bm->setTextureThreshold(3);
    bm->setUniquenessRatio(15);
    bm->setSpeckleWindowSize(21);
    bm->setSpeckleRange(30);
    bm->setDisp12MaxDiff(1);
*/


    sgbm->setPreFilterCap(prefilterCap);
    sgbm->setBlockSize(blockSize);
    sgbm->setMinDisparity(minDisparity);
    sgbm->setUniquenessRatio(uniquenessRatio);
    sgbm->setSpeckleWindowSize(speckleWindowSize);
    sgbm->setSpeckleRange(speckleRange);
    sgbm->setDisp12MaxDiff(disp12MaxDiff);
    sgbm->setP1(P1);
    sgbm->setP2(P2);

    depthFilter.initDepthFilter(minDisparity,numDisparities);
}


void DisparityCalcThread::disparityLoop()
{
    qDebug() << "Entering Streaming Loop";
    Mat imgResult;
    while(1) {
        leftFrame = videoLeft.getCameraFeed();
        rightFrame = videoRight.getCameraFeed();


        if(leftFrame.empty()||rightFrame.empty()){
            //cout << "Waiting for video stream. Stand by." << endl;
            continue;
        }

        remap(leftFrame, framel_rect, map_l1, map_l2, INTER_LINEAR);
        remap(rightFrame, framer_rect, map_r1, map_r2, INTER_LINEAR);

        cvtColor(framel_rect,leftGray, CV_BGR2GRAY);
        cvtColor(framer_rect,rightGray, CV_BGR2GRAY);

        Mat dstl, dstr, tmpl, tmpr;
        /* ... */
        tmpl = framel_rect;
        dstl = tmpl;

        tmpr = framer_rect;
        dstr = tmpr;

        // Downsample left matrix to speed up calculations.
        pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );
        tmpl = dstl;
        pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );
        //tmpl = dstl;
        //pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );

        // Downsample right matrix to speed up calculations.
        pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );
        tmpr = dstr;
        pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );
        //tmpr = dstr;
        //pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );

        //bm->compute(framel_rect,framer_rect, disp16S);
        sgbm->compute(tmpl,tmpr,disp16S);


        //Scale up disparity map.
        tmp = disp16S;
        pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
        dst = tmp;
        pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
        dst1 = dst;

        minMaxLoc(dst, &minVal, &maxVal);

        dst.convertTo(disp8U, CV_8UC1, 255/(maxVal - minVal));
        dst.convertTo(disp32F, CV_32F,1./16);

        // Calculate 3D co-ordinates from disparity image
        reprojectImageTo3D(disp32F, pointcloud, Q, true);

        //Canny( disp8U, edge, 100, 200, 3);

        //imshow("Left", framel_rect);
        //imshow("Right", framer_rect);



        if(!disp8U.empty() && !leftFrame.empty() && !rightFrame.empty())
        {
            //imshow("Disparity Map", disp8U);

            depthFilter.extractObstacles(framel_rect,disp8U,pointcloud,imgResult);
            depthFilter.getResult(imgResult);
            emit frameReady(imgResult,LEFT,DISPARITY);
            emit frameReady(disp8U,RIGHT,DISPARITY);
        }
    }
    qDebug() << "DisparityCalcThread finished.";
}
