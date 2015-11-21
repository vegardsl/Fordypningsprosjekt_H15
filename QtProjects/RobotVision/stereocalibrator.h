#ifndef STEREOCALIBRATOR_H
#define STEREOCALIBRATOR_H

#include <QtCore>
#include <QDebug>
#include <QThread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "videostreamthread.h"

class StereoCalibrator : public QObject
{
    Q_OBJECT

public:
    explicit StereoCalibrator(QObject *parent = 0);
    ~StereoCalibrator();

    void start(QDir _appDirPath,
               float _squareSideLength,
               int _width_internalCorners,
               int _height_internalCorners);

private:
    QString l_path, r_path; //path for folders containing left and right checkerboard images
    QDir appDir;

    bool flag_capture_set = false;
    bool chessBoardDetected = false;
    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;

    std::vector<cv::Mat> l_images, r_images; //left and right checkerboard images
    cv::Mat l_cameraMatrix, l_distCoeffs, r_cameraMatrix, r_distCoeffs; //Mats for holding individual camera calibration information
    bool show_chess_corners; //visualize checkerboard corner detections?
    float side_length; //side length of checkerboard squares
    int width, height; //number of internal corners in checkerboard along width and height
    std::vector<std::vector<cv::Point2f> > l_image_points, r_image_points; //left and right image points
    std::vector<std::vector<cv::Point3f> > object_points; //object points (grid)
    cv::Mat R, T, E, F; //stereo calibration information

    void initStereoCameraCalibration(QDir, QString, QString, float, int, int);//constructor
    bool calibrate(); //function to calibrate stereo camera
    void calc_image_points(bool); //function to calculae image points by detecting checkerboard corners
    void getStoredSamples(QString side);
    void pushBackSample(std::string file, QString side);
    void generateCalibrationStereoSamples(QDir l_dir, QDir r_dir);

    VideoStreamThread leftVideoStreamThread, rightVideoStreamThread;
    cv::Mat leftCameraFeed, rightCameraFeed, l_imshow, r_imshow, l_gray, r_gray;

signals:
    void frameReady(cv::Mat frame, int frameSide, int origin);

public slots:
    void handleCaptureCommand();

};

#endif // STEREOCALIBRATOR_H
