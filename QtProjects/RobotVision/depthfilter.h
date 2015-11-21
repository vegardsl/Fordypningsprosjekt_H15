#ifndef DEPTHFILTER_H
#define DEPTHFILTER_H

#include<QtCore>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class DepthFilter : public QObject
{
    Q_OBJECT

public:
    explicit DepthFilter();
    ~DepthFilter();

    void initDepthFilter(int _lowerDispThresh, int _upperDispThreshpper);

    void extractObstacles(cv::Mat imgOriginal,
                          cv::Mat imgDisparity,
                          cv::Mat pointcloud,
                          cv::Mat &imgResult);

    void getResult(cv::Mat &result);

private:
    void morphOps(cv::Mat &image);
    void filterAndMaskImage(cv::Mat imgDisparityGray,
                            int lowerThreshold,
                            int upperThreshold,
                            cv::Mat &imgMasked);
    void drawObject(int x, int y,cv::Mat &frame);
    void trackFilteredObject(int &x, int &y, cv::Mat threshold);

    QString matType2str(int type); //For debugging or testing. Returns Mat type.

    int lowerDispThresh;
    int upperDispThresh;
    cv::Mat imgResult, imgOriginal, pointcloud, pointcloud_roi, z_roi, imgDisparity;
    //cv::Mat imgOriginal, imgDisparity, imgDisparityGray, imgThreshold;

    const int MAX_NUM_OBJECTS = 50;

    const int FRAME_WIDTH = 1280;
    const int FRAME_HEIGHT = 1024;

    const int MIN_OBJECT_AREA = 150*100;
    const int MAX_OBJECT_AREA = (FRAME_HEIGHT/2)*(FRAME_WIDTH/2);
signals:

public slots:
};

#endif // DEPTHFILTER_H