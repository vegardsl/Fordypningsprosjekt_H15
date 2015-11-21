#include "stereorectifier.h"

using namespace cv;
using namespace std;

StereoRectifier::StereoRectifier(QObject *parent) : QObject(parent)
{

}

StereoRectifier::~StereoRectifier()
{

}

void StereoRectifier::start(QString _appPath)
{
    QString appPath = _appPath;
    Size image_size(1280, 1024);
    bool success = rectify(appPath,image_size);
    if(success)
    {
        show_rectified(image_size);
    }
    else
    {
        // TODO: Handle this case.
        qDebug() << "Unsuccessful image rectification.";
    }

}

bool StereoRectifier::rectify(QString fileName, Size image_size) {
    // Read individal camera calibration information from saved XML file
    fileName.append("/samples/stereo/stereo_calib.xml");
    qDebug() << "path to calibFile: "+fileName;
    Mat l_cameraMatrix, l_distCoeffs, r_cameraMatrix, r_distCoeffs, R, T;
    FileStorage fs(fileName.toLocal8Bit().constData(), FileStorage::READ);
    fs["l_cameraMatrix"] >> l_cameraMatrix;
    fs["l_distCoeffs"] >> l_distCoeffs;
    fs["r_cameraMatrix"] >> r_cameraMatrix;
    fs["r_distCoeffs"] >> r_distCoeffs;
    fs["R"] >> R;
    fs["T"] >> T;
    fs.release();

    if(l_cameraMatrix.empty()
            || r_cameraMatrix.empty()
            || l_distCoeffs.empty()
            || r_distCoeffs.empty()
            || R.empty()
            || T.empty())
    {
        cout << "Rectifier: Loading of files not successful" << endl;
        return false;
    }

    // Calculate transforms for rectifying images
    Mat Rl, Rr, Pl, Pr, Q;
    stereoRectify(l_cameraMatrix, l_distCoeffs, r_cameraMatrix, r_distCoeffs,
                  image_size, R, T, Rl, Rr, Pl, Pr, Q
                  );

    // Calculate pixel maps for efficient rectification of images via lookup tables
    cv::initUndistortRectifyMap(l_cameraMatrix, l_distCoeffs, Rl, Pl, image_size, CV_16SC2, map_l1, map_l2);
    cv::initUndistortRectifyMap(r_cameraMatrix, r_distCoeffs, Rr, Pr, image_size, CV_16SC2, map_r1, map_r2);

    fs.open(fileName.toLocal8Bit().constData(), FileStorage::APPEND);
    fs << "Rl" << Rl;
    fs << "Rr" << Rr;
    fs << "Pl" << Pl;
    fs << "Pr" << Pr;
    fs << "Q" << Q;
    fs << "map_l1" << map_l1;
    fs << "map_l2" << map_l2;
    fs << "map_r1" << map_r1;
    fs << "map_r2" << map_r2;
    fs.release();

    return true;
}

void StereoRectifier::show_rectified(Size image_size)
{
    const string videoStreamAddress[] = { "http://admin:admin@192.168.0.100:80/video.mjpg", "http://admin:admin@192.168.0.102:80/video.mjpg" };

    leftVideoStreamThread.beginVideoStream(videoStreamAddress[0],LEFT);
    rightVideoStreamThread.beginVideoStream(videoStreamAddress[1],RIGHT);

    destroyAllWindows();
    namedWindow("Combo");

    while(char(waitKey(1)) != 'q') {
        /*
        //grab raw frames first
        capl.grab();
        capr.grab();
        //decode later so the grabbed frames are less apart in time
        Mat framel, framel_rect, framer, framer_rect;
        capl.retrieve(framel);
        capr.retrieve(framer);
        if(framel.empty() || framer.empty()){
            continue;
        }
        */

        leftCameraFeed = leftVideoStreamThread.getCameraFeed();
        rightCameraFeed = rightVideoStreamThread.getCameraFeed();

        if(leftCameraFeed.empty()||rightCameraFeed.empty()){
            //cout << "Waiting for video stream. Stand by." << endl;
            continue;
        }

        // Remap images by pixel maps to rectify
        remap(leftCameraFeed, leftCameraFeed_rect, map_l1, map_l2, INTER_LINEAR);
        remap(rightCameraFeed, rightCameraFeed_rect, map_r1, map_r2, INTER_LINEAR);

        // Make a larger image containing the left and right rectified images side-by-side
        Mat combo(image_size.height, 2 * image_size.width, CV_8UC3);
        leftCameraFeed_rect.copyTo(combo(Range::all(), Range(0, image_size.width)));
        rightCameraFeed_rect.copyTo(combo(Range::all(), Range(image_size.width, 2*image_size.width)));

        // Draw horizontal red lines in the combo image to make comparison easier
        for(int y = 0; y < combo.rows; y += 20)
        {
            line(combo, Point(0, y), Point(combo.cols, y), Scalar(0, 0, 255));
        }

        //QThread::currentThread()->msleep(500);
        Mat leftImage, rightImage;
        leftImage = Mat(combo, Rect(0,0,640,1024));
        rightImage = Mat(combo,Rect(641,0,1280,1024));
        emit frameReady(leftImage,LEFT,CAM_RECIFY);
        emit frameReady(rightImage,RIGHT,CAM_RECIFY);
        imshow("Combo", combo);
    }
    leftVideoStreamThread.setRun(false);
    rightVideoStreamThread.setRun(false);
    while(!leftVideoStreamThread.isFinished()||!rightVideoStreamThread.isFinished()){
        // wait for thread to finish.
    }
    qDebug() << "Both threads are finished.";
}
