#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtConcurrent>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "videostreamthread.h"
#include "singlecamcalibratorthread.h"
#include "stereocalibrator.h"
#include "stereorectifier.h"
#include "disparitycalcthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void startSingleCamCalibration();

    void notifyCaptureClicked();
    void notifyEndSamplingClicked();

private slots:
    void on_actionToggle_Left_Camera_triggered();

    void on_actionToggle_Right_Camera_triggered();

    void on_actionCalibrate_Right_Camera_triggered();

    void on_actionCalibrate_Left_Camera_triggered();

    void on_capture_clicked();

    void on_endSampling_clicked();

    void on_actionCalibrate_Stereo_Camera_triggered();

    void on_actionRectify_Images_triggered();

    void on_actionToggle_Depth_Perception_triggered();

public slots:
    void recieveStreamedFrame(cv::Mat, int, int);

    void newNumber(QString name, int number);

private:
    Ui::MainWindow *ui;

// ---- Private Functions -----------------------------------------------------
    void displayImage(cv::Mat image, int selectedLabel);
    QImage convertOpenCVMatToQtQImage(cv::Mat mat);
    void initSignalsAndSlots();

// ---- Private Variables -----------------------------------------------------
    QDir dir;
    QString appPath;
    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;
    // Calibration chessboard parameters
    float chessSquareSideLength = 26.f;
    int chessSquaresWide = 9;
    int chessSquaresHigh = 6;

    int leftMode, rightMode;
    const int MODE_LEFT_STREAM = 8;
    const int MODE_RIGHT_STREAM = 9;
    const int MODE_LEFT_CALIB = 10;
    const int MODE_RIGHT_CALIB = 11;

    VideoStreamThread leftStreamThread, rightStreamThread;
    SingleCamCalibratorThread l_singleCamCalibrator, r_singleCamCalibrator;
    StereoCalibrator stereoCalibrator;
    StereoRectifier stereoRectifier;
    DisparityCalcThread disparityCalcThread;

 };

#endif // MAINWINDOW_H
