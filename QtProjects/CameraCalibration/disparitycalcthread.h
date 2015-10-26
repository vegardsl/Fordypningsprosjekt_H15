#ifndef DISPARITYCALCTHREAD_H
#define DISPARITYCALCTHREAD_H

#include <QtCore>
#include <QDebug>

#include <cstdint>
#include <iomanip>

#include "stdio.h"
#include "stdlib.h"


#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/cuda.hpp>
#include <C:\OpenCV\sources\modules\cudastereo\include\opencv2\cudastereo.hpp>

#include "videostreamthread.h"

//using namespace cv;
//using namespace std;
//using namespace pcl;

class DisparityCalcThread : public QThread
{
    Q_OBJECT

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

    cv::Mat Q;

    int bothFramesArrived = false;

    cv::Ptr<cv::StereoSGBM> sgbm;
    cv::Ptr<cv::StereoBM> bm;

    //QSemaphore leftFrameArrived;
    //QSemaphore rightFrameArrived;

    VideoStreamThread videoRight, videoLeft;

    /* --- CUDA declarations --- */
    cv::cuda::GpuMat l_disp, r_disp, gpu_disp;


    /* --- Tuning trackbars --- */
    const std::string trackbarWindowName = "Trackbars";
    char TrackbarName[50];
    void createTrackbars();
    //void on_trackbar( int, void* );
    //void on_prefilterCap( int, void* );
    //void on_blockSize( int, void* );
    //void on_textureThreashold( int, void* );
    //void on_uniquenessRatio( int, void* );
    //void on_speckleWindowSize( int, void* );
    //void on_speckleRange( int, void* );
    //void on_disp12MaxDiff( int, void* );
    //void on_P1( int, void* );
    //void on_P2( int, void* );

    //int min_disp = 0;
    int numDisparities = 16*10; //Must be divisible by 16.
    int SADWindowSize = 5; // Must be odd.

    int minDisparity = 0;
    int numDisparity = 80;
    int prefilterCap = 11;
    int blockSize = 7; // Set size of blocks to match
    int textureThreshold = 10;
    int uniquenessRatio = 15;
    int speckleWindowSize = 19;
    int speckleRange = 8;
    int disp12MaxDiff = 5;
    int P1 = 12 * 3 * SADWindowSize * SADWindowSize;
    int P2 = 36 * 3 * SADWindowSize * SADWindowSize;

    const int TRACKBAR_MAX = 256;
    int TRACKBAR_MIN = 0;
    int TOT_DISP_MIN = -64;


public:
    DisparityCalcThread(QObject *parent = 0);

    void beginDisparityCalcThread(QString, cv::Size);

    //void set_minDisp(int minDisp) { stereo.minDisparity = minDisp; }
    //void set_numDisp(int numDisp) { stereo.numberOfDisparities = numDisp; }
    void show_disparity(cv::Size); // show live disparity by processing stereo camera feed

    void _setPrefilterCap(int _prefilterCap){sgbm -> setPreFilterCap(_prefilterCap);}
    void _setBlockSize(int _blockSize){sgbm -> setBlockSize(_blockSize);}
    void _setUniquenessRatio(int _uniquenessRatio){sgbm -> setUniquenessRatio(_uniquenessRatio);}
    void _setSpeckleWindowSize(int _speckleWindowSize){sgbm -> setSpeckleWindowSize(_speckleWindowSize);}
    void _setSpeckleRange(int _speckleRange){sgbm -> setBlockSize(_speckleRange);}
    void _setDisp12MaxDiff(int _disp12MaxDiff){sgbm -> setDisp12MaxDiff(_disp12MaxDiff);}
    void _setP1(int _P1){sgbm -> setP1(_P1);}
    void _setP2(int _P2){sgbm -> setP2(_P2);}

protected:

    void run() Q_DECL_OVERRIDE;

signals:

public slots:
    void newFrameForProcessing(cv::Mat frame, std::string frameSide);
};

#endif // DISPARITYCALCTHREAD_H
