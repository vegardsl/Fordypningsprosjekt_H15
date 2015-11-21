#ifndef VIDEOSTREAMTHREAD_H
#define VIDEOSTREAMTHREAD_H

#include <QtCore>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoStreamThread: public QThread
{
    Q_OBJECT

public:
    VideoStreamThread(QObject *parent = 0);
    void beginVideoStream(std::string _address, int _cameraSide);
    void setRun(bool _continueRunning);
    cv::Mat getCameraFeed();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    std::string videoStreamAddress;
    std::string windowName;
    int cameraSide;
    bool continueRunning = true;
    cv::Mat cameraFeed;

    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;


signals:
    void frameReady(cv::Mat frame, int frameSide, int origin);

public slots:
};

#endif // VIDEOSTREAMTHREAD_H
