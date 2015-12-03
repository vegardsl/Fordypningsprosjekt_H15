#ifndef DISPARITYCALCTHREAD_H
#define DISPARITYCALCTHREAD_H

#include <QtCore>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/utility.hpp>

#include "videostreamthread.h"
#include "depthfilter.h"

class DisparityCalcThread : public QObject
{
    Q_OBJECT

public:
    explicit DisparityCalcThread(QObject *parent = 0);
    ~DisparityCalcThread();

    void start(QString appPath);

    //void set_minDisp(int minDisp) { stereo.minDisparity = minDisp; }
    //void set_numDisp(int numDisp) { stereo.numberOfDisparities = numDisp; }
    //void show_disparity(cv::Size); // show live disparity by processing stereo camera feed

    //void _setPrefilterCap(int _prefilterCap){sgbm -> setPreFilterCap(_prefilterCap);}

private:
    cv::Mat map_l1, map_l2, map_r1, map_r2; // rectification pixel maps
    //StereoSGBM stereo; // stereo matching object for disparity computation
    int min_disp, num_disp; // parameters of StereoSGBM

    cv::Mat leftFrame, rightFrame, leftGray, rightGray, framel_rect, framer_rect;
    cv::Mat disp16S, disp8U, disp32F;
    cv::Mat edge;
    cv::Mat tmp, dst, dst1, dst2, dst3, dst4, dst_avg;
    //-- Extreme values of disparity image.
    double minVal, maxVal;

    cv::Mat Q, pointcloud;

    int bothFramesArrived = false;

    cv::Ptr<cv::StereoSGBM> sgbm;
    cv::Ptr<cv::StereoBM> bm;

    //QSemaphore leftFrameArrived;
    //QSemaphore rightFrameArrived;

    VideoStreamThread videoRight, videoLeft;
    DepthFilter depthFilter;

    /* --- CUDA declarations --- */
    //cv::cuda::GpuMat l_disp, r_disp, gpu_disp;

    /* --- Tuning trackbars --- */
    const std::string trackbarWindowName = "Trackbars";
    char TrackbarName[50];
    void createTrackbars();
    //void on_trackbar( int, void* );
    //void on_prefilterCap( int, void* );
    void on_blockSize( int, void* );
    void on_textureThreashold( int, void* );
    void on_uniquenessRatio( int, void* );
    void on_speckleWindowSize( int, void* );
    void on_speckleRange( int, void* );
    void on_disp12MaxDiff( int, void* );
    void on_P1( int, void* );
    void on_P2( int, void* );

    //int min_disp = 0;
    int numDisparities = 16*10; //Must be divisible by 16.
    int SADWindowSize = 5; // Must be odd.

    int minDisparity = 0;
    int prefilterCap = 31;
    int blockSize = 5;
    int textureThreashold = 31;
    int uniquenessRatio = 15;
    int speckleWindowSize = 15;
    int speckleRange = 15;
    int disp12MaxDiff = 5;
    int P1 = 16 * 3 * SADWindowSize * SADWindowSize;
    int P2 = 32 * 3 * SADWindowSize * SADWindowSize;

    const int LEFT = 0;
    const int RIGHT = 1;
    const int VIDEO_STREAM = 2;
    const int LEFT_CALIB = 3;
    const int RIGHT_CALIB = 4;
    const int STEREO_CALIB = 5;
    const int CAM_RECIFY = 6;
    const int DISPARITY = 7;

    void initDisparityCalcThread(QString, cv::Size);
    void disparityLoop();
    QString matType2str(int type);
    //cv::VideoWriter writer;
    std::string filename = "C:\stereoTest_casual.avi";

signals:
    void frameReady(cv::Mat frame, int frameSide, int origin);

public slots:

};

#endif // DISPARITYCALCTHREAD_H
