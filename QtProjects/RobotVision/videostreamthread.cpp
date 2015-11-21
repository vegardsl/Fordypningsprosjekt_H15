#include "videostreamthread.h"

using namespace cv;
using namespace std;

VideoStreamThread::VideoStreamThread(QObject *parent) : QThread(parent)
{

}

Mat VideoStreamThread::getCameraFeed(){
    //if(!exportedFeed.empty())
    return cameraFeed;
    //else return cameraFeed;
}

void VideoStreamThread::setRun(bool _continueRunning)
{
    continueRunning = _continueRunning;
}

void VideoStreamThread::beginVideoStream(string _address, int _cameraSide){
   videoStreamAddress = _address;
   cameraSide = _cameraSide;
   if(cameraSide == LEFT)
   {
       windowName = "Left";
   }
   else if(cameraSide == RIGHT)
   {
       windowName = "Right";
   }
   else
   {
       //TODO: Handle wrong input;

       return;
   }

   start();
}


void VideoStreamThread::run()
{
    VideoCapture capture;

    cout << "Opening video stream." << endl;

    capture.open(videoStreamAddress);
    if (!capture.isOpened())
    {
        std::cout << "Error when opening video stream: " << "http://admin:admin@192.168.0.100:80/video.mjpg" << std::endl;
        std::cout << "Press any key to quit. " << std::endl;
        getchar();
        //return -1;
    }
    cout << "Video stream successfully opened. Please wait a few seconds... " << std::endl;

    while (continueRunning){
        capture.read(cameraFeed);
        emit frameReady(cameraFeed, cameraSide, VIDEO_STREAM);
        //imshow(windowName, cameraFeed);
        waitKey(30);
    }
    capture.release();
}

