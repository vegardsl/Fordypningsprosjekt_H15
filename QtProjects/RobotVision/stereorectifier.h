#ifndef STEREORECTIFIER_H
#define STEREORECTIFIER_H

#include <QtCore>
#include <QDebug>
#include <QThread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "videostreamthread.h"

class StereoRectifier : public QObject
{
    Q_OBJECT

public:
    explicit StereoRectifier(QObject *parent = 0);
    ~StereoRectifier();

    void start(QString _appPath);

    void show_rectified(cv::Size); //function to show live rectified feed from stereo camera

private:

    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;

    cv::Mat map_l1, map_l2, map_r1, map_r2; //pixel maps for rectification
    QString dataPath;

    VideoStreamThread leftVideoStreamThread, rightVideoStreamThread;
    cv::Mat leftCameraFeed, rightCameraFeed, leftCameraFeed_rect, rightCameraFeed_rect;

    bool rectify(QString, cv::Size);

signals:
    void frameReady(cv::Mat frame, int frameSide, int origin);

public slots:
};

#endif // STEREORECTIFIER_H
