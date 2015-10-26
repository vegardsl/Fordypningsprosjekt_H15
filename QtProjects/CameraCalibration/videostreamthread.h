#ifndef VIDEOSTREAMTHREAD_H
#define VIDEOSTREAMTHREAD_H

#include <QtCore>
#include <QDebug>

#include <stdio.h>

#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <opencv\cv.h>
#include <opencv\highgui.h>


class VideoStreamThread : public QThread
{
    Q_OBJECT

public:
    VideoStreamThread(QObject *parent = 0);

    void beginVideoStream(std::string videoStreamAddress, std::string name);
    cv::Mat VideoStreamThread::getCameraFeed();
    void VideoStreamThread::setRun(bool _continueRunning);

    cv::Size boardSize;

    bool continueRunning = true;


protected:
    void run() Q_DECL_OVERRIDE;

signals:
   void frameReady(cv::Mat frame, std::string frameSide);

public slots:

private:
    int modeOfOperation;
    std::string videoStreamAddress;
    std::string windowName;
    cv::VideoCapture capture;
    cv::Mat cameraFeed, exportedFeed;

    std::vector<std::vector<cv::Point2f> > image_points;          //2D image points
    std::vector<std::vector<cv::Point3f> > object_points;         //3D object points

    std::string IMAGE_FOLDER = "C:\\Users\\vegarsl\\Pictures\\StereoSamples\\Calibration\\Data\\left\\";
    std::string DATA_FOLDER = "C:\\Users\\vegarsl\\Pictures\\StereoSamples\\Calibration\\Data\\";

    std::vector<std::vector<cv::Point2f> > imagePoints;

};

#endif // VIDEOSTREAMTHREAD_H
