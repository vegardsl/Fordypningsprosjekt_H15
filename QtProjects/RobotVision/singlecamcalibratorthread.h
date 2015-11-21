#ifndef SINGLECAMCALIBRATORTHREAD_H
#define SINGLECAMCALIBRATORTHREAD_H

#include <QtCore>
#include <QDebug>
#include <QThread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class SingleCamCalibratorThread : public QObject
{
    Q_OBJECT

public:
    explicit SingleCamCalibratorThread(QObject *parent = 0);
    ~SingleCamCalibratorThread();

    void start(QString _selectedCamera,
               QDir _appDirPath,
               double _squareSideLength,
               int _width_internalCorners,
               int _height_internalCorners);

private:
    bool mStop;
    bool flag_capture_set = false;

    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;

    int side_int, origin_int;
    std::string side_string;

    QString selectedCamera;
    QDir appDirPath;                    //path of folder containing chessboard images
    QDir sampleFilePath;
    std::vector<cv::Mat> images;        //chessboard images
    cv::Mat cameraMatrix, distCoeffs;   //camera matrix and distortion coefficients
    bool show_chess_corners;            //visualize the extracted chessboard corners?
    double squareSideLength;            //side length of a chessboard square in mm
    int width_internalCorners, height_internalCorners;  //number of internal corners of the chessboard along width and height
    bool chessBoardDetected = false;

    std::vector<std::vector<cv::Point2f> > image_points;    //2D image points
    std::vector<std::vector<cv::Point3f> > object_points;   //3D object points

    cv::Mat cameraFeed;
    //VideoStreamThread mVideoStreamThread;

    int initSingleCamCalibrator(QString selectedCamera,
                                QDir appDirPath,
                                double _squareSideLength,
                                int _width_internalCorners,
                                int _height_internalCorners);   //constructor, reads in the images
    void calibrate();                                           //function to calibrate the camera
    cv::Mat get_cameraMatrix();                                 //access the camera matrix
    cv::Mat get_distCoeffs();                                   //access the distortion coefficients
    void calc_image_points(bool);                               //calculate internal corners of the chessboard image
    void generateCalibrationSamples(QDir sampleFilePath, QString cameraSelection);

signals:
    void on_number(QString name, int number);
    void frameReady(cv::Mat frame, int frameSide, int origin);

public slots:
    void stop();
    void handleCaptureCommand();
    void recieveFrame(cv::Mat &frame, int side);

};

#endif // SINGLECAMCALIBRATORTHREAD_H
