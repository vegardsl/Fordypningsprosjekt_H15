#ifndef SINGLECAMCALIBRATOR_H
#define SINGLECAMCALIBRATOR_H

// Program illustrate single camera calibration
// Author: Samarth Manoj Brahmbhatt, University of Pennsylvania

#include <QtCore>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include <cstdint>
#include <iomanip>

#include "stdio.h"
#include "stdlib.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "videostreamthread.h"

class SingleCamCalibrator : public QObject{

     Q_OBJECT

private:
    QString selectedCamera;
    QDir appDirPath;                                    //path of folder containing chessboard images
    QDir sampleFilePath;
    std::vector<cv::Mat> images;                        //chessboard images
    cv::Mat cameraMatrix, distCoeffs;                   //camera matrix and distortion coefficients
    bool show_chess_corners;                            //visualize the extracted chessboard corners?
    double squareSideLength;                            //side length of a chessboard square in mm
    int width_internalCorners, height_internalCorners;  //number of internal corners of the chessboard along width and height

    std::vector<std::vector<cv::Point2f> > image_points;          //2D image points
    std::vector<std::vector<cv::Point3f> > object_points;         //3D object points


    const int SUCCESS = 20;
    const int FAILED = 21;

    void generateCalibrationSamples(QDir sampleFilePath, QString cameraSelection);
    void initSignalsAndSlots();
    QSemaphore waitForFirstFrame;

    cv::Mat cameraFeed;
    VideoStreamThread mVideoStreamThread;

public:
    SingleCamCalibrator::SingleCamCalibrator();
    int initSingleCamCalibrator(QString selectedCamera,
                                QDir appDirPath,
                                double _squareSideLength,
                                int _width_internalCorners,
                                int _height_internalCorners);   //constructor, reads in the images
    void calibrate();                                           //function to calibrate the camera
    cv::Mat get_cameraMatrix();                                 //access the camera matrix
    cv::Mat get_distCoeffs();                                   //access the distortion coefficients
    void calc_image_points(bool);                               //calculate internal corners of the chessboard image

signals:

public slots:
    //void recieveStreamedFrame(cv::Mat frame, int side);

};

#endif // SINGLECAMCALIBRATOR_H
