#include "disparitycalcthread.h"

using namespace cv;
using namespace std;
//using namespace pcl;


DisparityCalcThread::DisparityCalcThread(QObject *parent) : QThread(parent)
{

}

void on_trackbar( int, void* )
{//This function gets called whenever a
    // trackbar position is changed

    sgbm->setPreFilterCap(prefilterCap);
    sgbm->setBlockSize(blockSize);
    sgbm->setUniquenessRatio(uniquenessRatio);
    sgbm->setSpeckleWindowSize(speckleWindowSize);
    sgbm->setSpeckleRange(speckleRange);
    sgbm->setDisp12MaxDiff(disp12MaxDiff);
    sgbm->setP1(P1);
    sgbm->setP2(P2);

}

void on_prefilterCap(int prefilterCap, void* _disp_obj)
{
    //sgbm->setPreFilterCap(prefilterCap);
    DisparityCalcThread * disp_obj = (DisparityCalcThread *) _disp_obj;
    disp_obj -> _setPrefilterCap(prefilterCap);
}
/*
void DisparityCalcThread::on_blockSize( int, void* );
void DisparityCalcThread::on_textureThreashold( int, void* );
void DisparityCalcThread::on_uniquenessRatio( int, void* );
void DisparityCalcThread::on_speckleWindowSize( int, void* );
void DisparityCalcThread::on_speckleRange( int, void* );
void DisparityCalcThread::on_disp12MaxDiff( int, void* );
void DisparityCalcThread::on_P1( int, void* );
void DisparityCalcThread::on_P2( int, void* );
*/
void DisparityCalcThread::createTrackbars()
{
    namedWindow(trackbarWindowName);

    sprintf( TrackbarName, "prefilterCap", prefilterCap);
    sprintf( TrackbarName, "blockSize", blockSize);
    sprintf( TrackbarName, "textureThreashold", textureThreashold);
    sprintf( TrackbarName, "uniquenessRatio", uniquenessRatio);
    sprintf( TrackbarName, "speckleWindowSize", speckleWindowSize);
    sprintf( TrackbarName, "speckleRange", speckleRange);
    sprintf( TrackbarName, "disp12MaxDiff", disp12MaxDiff);
    sprintf( TrackbarName, "P1", P1);
    sprintf( TrackbarName, "P1", P1);

    //create trackbars and insert them into window
    //3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
    //the max value the trackbar can move (eg. H_HIGH),
    //and the function that is called whenever the trackbar is moved(eg. on_trackbar)
    //                                  ---->    ---->     ---->
    createTrackbar( "prefilterCap", trackbarWindowName, &prefilterCap, TRACKBAR_MAX, on_prefilterCap, (void *)this );
    createTrackbar( "blockSize", trackbarWindowName, &blockSize, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "textureThreashold", trackbarWindowName, &textureThreashold, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "uniquenessRatio", trackbarWindowName, &uniquenessRatio, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "speckleWindowSize", trackbarWindowName, &speckleWindowSize, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "speckleRange", trackbarWindowName, &speckleRange, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "disp12MaxDiff", trackbarWindowName, &disp12MaxDiff, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "P1", trackbarWindowName, &P1, TRACKBAR_MAX, on_trackbar );
    createTrackbar( "P2", trackbarWindowName, &P2, TRACKBAR_MAX, on_trackbar );

    on_prefilterCap(prefilterCap,this);
}

void DisparityCalcThread::newFrameForProcessing(Mat frame, string frameSide)
{
/*
    if(frameSide == "Left Camera"){
        //framesArrived.aquire(1);
        leftFrame = frame;
        cvtColor(leftFrame,leftGray, CV_BGR2GRAY);
        if(!bothFramesArrived){
            leftFrameArrived.release();

        }
        qDebug() << "New rightFrame";

        //qDebug() << "New leftFrame";
    }else if(frameSide == "Right Camera"){
        //framesArrived.aquire(1);
        rightFrame = frame;
        cvtColor(rightFrame,rightGray, CV_BGR2GRAY);
        if(!bothFramesArrived){
            rightFrameArrived.release();
        }
        qDebug() << "New rightFrame";
    }
    */
}

/*
// Callback functions for minDisparity and numberOfDisparities trackbars
void on_minDisp(int min_disp, void * _disp_obj)
{
    disparity * disp_obj = (disparity *) _disp_obj;
    disp_obj -> set_minDisp(min_disp - 30);
}

void on_numDisp(int num_disp, void * _disp_obj)
{
    disparity * disp_obj = (disparity *) _disp_obj;
    num_disp = (num_disp / 16) * 16;
    setTrackbarPos("numDisparity", "Disparity", num_disp);
    disp_obj -> set_numDisp(num_disp);
}
*/

void DisparityCalcThread::beginDisparityCalcThread(QString fileName, cv::Size image_size)
{
    fileName.append("/samples/stereo/stereo_calib.xml");
    qDebug() << "path to calibFile: "+fileName;

    // Read pixel maps from XML file
    cv::FileStorage fs(fileName.toLocal8Bit().constData(), cv::FileStorage::READ);
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
    videoLeft.beginVideoStream(videoStreamAddress[0],"left");
    videoRight.beginVideoStream(videoStreamAddress[1],"right");

    start();
}


void DisparityCalcThread::run()
{
    /*
    VideoCapture capr(1), capl(2);
    //reduce frame size
    capl.set(CV_CAP_PROP_FRAME_HEIGHT, image_size.height);
    capl.set(CV_CAP_PROP_FRAME_WIDTH, image_size.width);
    capr.set(CV_CAP_PROP_FRAME_HEIGHT, image_size.height);
    capr.set(CV_CAP_PROP_FRAME_WIDTH, image_size.width);
    */

    qDebug() << "Running DisparityCalcThread";

    //leftFrameArrived.acquire();
    //rightFrameArrived.acquire();

    qDebug() << "Both frames arrived";
    bothFramesArrived = true;

/*
    min_disp = 30;
    num_disp = ((image_size.width / 8) + 15) & -16;
    namedWindow("Disparity", CV_WINDOW_NORMAL);
    namedWindow("Left", CV_WINDOW_NORMAL);
    createTrackbar("minDisparity + 30", "Disparity", &min_disp, 60, on_minDisp, (void *)this);
    createTrackbar("numDisparity", "Disparity", &num_disp, 150, on_numDisp, (void *)this);
    on_minDisp(min_disp, this);
    on_numDisp(num_disp, this);
*/
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

    namedWindow("Disparity Map");

    int numCudaDevices = cuda::getCudaEnabledDeviceCount();
    string s = to_string(numCudaDevices);
    cout << "Cuda enambled devices: "+s << endl;

    char choice = 'z';
    while(char(waitKey(1)) != 'q') {
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

        pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );
        tmpl = dstl;
        pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );
        //tmpl = dstl;
        //pyrDown( tmpl, dstl, Size( tmpl.cols/2, tmpl.rows/2 ) );

        pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );
        tmpr = dstr;
        pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );
        //tmpr = dstr;
        //pyrDown( tmpr, dstr, Size( tmpr.cols/2, tmpr.rows/2 ) );

        //bm->compute(framel_rect,framer_rect, disp16S);
        sgbm->compute(tmpl,tmpr,disp16S);


        tmp = disp16S;
        pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
        dst = tmp;
        pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
        dst1 = dst;
        /*
        if(!dst4.empty())
        {
            dst_avg = (dst1 + dst2 + dst3 + dst4)/4;
        }
        else
        {
            dst_avg = dst;
        }
*/
        minMaxLoc(dst, &minVal, &maxVal);

        dst.convertTo(disp8U, CV_8UC1, 255/(maxVal - minVal));
        dst.convertTo(disp32F, CV_32F,1./16);

        Canny( disp8U, edge, 100, 200, 3);

        imshow("Left", framel_rect);
        imshow("Right", framer_rect);


        if(!disp8U.empty() && !leftFrame.empty() && !rightFrame.empty())
        {
            imshow("Disparity Map", disp8U);
            //imshow("3D", image3D);
            //print_3D_points(disp8U, image3D);
            //PointCloud<PointXYZ>::Ptr pointCloud = MatToPoinXYZ(image3D);
            //viewer.showCloud(pointCloud);
            if(choice == 'v')
            {
                waitKey();
            }

        }
        if(!edge.empty())
        {
            imshow("Edge",edge);
        }
        choice = char(waitKey(1)); // User input.
    }

    qDebug() << "DisparityCalcThread finished.";
}

    /*
    *  Function: Get from a Mat to pcl pointcloud datatype
    *  In: cv::Mat
    *  Out: pcl::PointCloud
    */
/*
PointCloud<PointXYZ>::Ptr DisparityCalcThread::MatToPoinXYZ(Mat OpenCVPointCloud)
{

    double X,Y,Z;
    char pr=100, pg=100, pb=100;
    PointCloud<PointXYZ>::Ptr point_cloud_ptr(new PointCloud<PointXYZ>);//(new pcl::pointcloud<pcl::pointXYZ>);

    for(int i=0;i<OpenCVPointCloud.cols;i++)
    {
        //cout<<i<<endl;
        X = OpenCVPointCloud.at<float>(0,i);
        Y = OpenCVPointCloud.at<float>(1,i);
        Z = OpenCVPointCloud.at<float>(2,i);

        PointXYZ point;
        point.x = X;
        point.y = Y;
        point.z = Z;

        //uint32_t rgb = (static_cast<uint32_t>(pr) << 16 | static_cast<uint32_t>(pg) << 8 | static_cast<uint32_t>(pb));
        //point.rgb = *reinterpret_cast<float*>(&rgb); // Hæ?
        point_cloud_ptr -> points.push_back(point);


    }
    point_cloud_ptr->width = (int)point_cloud_ptr->points.size();
    point_cloud_ptr->height = 1;

    return point_cloud_ptr;

}

*/

