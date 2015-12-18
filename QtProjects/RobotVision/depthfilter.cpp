#include "depthfilter.h"

using namespace cv;
using namespace std;

DepthFilter::DepthFilter()
{
    initFloorPlaneFilter();
}

DepthFilter::~DepthFilter()
{

}

void DepthFilter::initFloorPlaneFilter()
{
    Mat imgMasked, imgInvThresh;
    double cameraHeight = 55;
    double verticalAngleArray[] = {1.375 , 4.125 , 6.875 , 9.625 ,
                                   12.375 , 15.125 , 17.875 , 20.625};
    double horizontalAngleArray[] = {24.75, 19.25, 13.72, 8.25, 2.75, 2.75 , 8.25 , 13.75 , 19.25 , 24.75};

    double verticalAngle, horizontalAngle;
    double floorDistance;


    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            verticalAngle = verticalAngleArray[j];
            horizontalAngle = horizontalAngleArray[ i ];
            //qDebug() << "index: " + QString::number((int)qFabs(i-5));
            //qDebug() << "verticalAngle: " + QString::number( qDegreesToRadians(verticalAngle) );
            //qDebug() << "horizontalAngle: " + QString::number( qDegreesToRadians(horizontalAngle) );
            floorDistance = ( cameraHeight/qSin(qDegreesToRadians(verticalAngle)) )/qCos(qDegreesToRadians(horizontalAngle));
            floorDisparity[i][j] = dist2disp(floorDistance);
            //qDebug() << "Distance: " + QString::number(floorDisparity[i][j]);
        }
    }

    qDebug() << "done";
}

void DepthFilter::floorPlaneFilter(Mat &imgDisparity)
{
    Rect roi;
    roi.height = 64;
    roi.width = 128;

    Scalar color = Scalar(255,128,0);

    Mat imgInvThresh, imgMasked;
    imshow("disp",imgDisparity);
    waitKey();
    for(int i = 0; i < 10; i++)
    {
        for(int j = 2; j < 8; j++)
        {
            //roi.tl() = Point(128*i,64*j);
            roi.x = 128*i;
            roi.y = 64*j+512;

            //qDebug() << "Top left of ROI: " << QString::number(roi.tl().x ) << " " << QString::number(roi.tl().y );

            Mat crop(imgDisparity, roi);

            rectangle( imgDisparity, roi.tl(), roi.br(), color, 2, 8, 0 );

            threshold(crop, imgInvThresh, floorDisparity[i][j]-1, floorDisparity[i][j]+1, CV_THRESH_BINARY_INV);

            bitwise_and(crop, imgInvThresh, imgMasked);

            imgMasked.copyTo(imgDisparity(roi));

            imshow("disp",imgDisparity);
            waitKey(200);
        }
    }

}

void DepthFilter::initDepthFilter(int _lowerDispThres, int _upperDispThres)
{
    lowerDispThresh = _lowerDispThres;
    upperDispThresh = _upperDispThres;
}

double DepthFilter::disp2dist(double disparity)
{
    double a = 7275;
    double b = -1.016;
    double distance = a*qPow(disparity, b);

    return distance;
}

double DepthFilter::dist2disp(double distance)
{
    double a = 7275;
    double b = -1.016;
    double disparity = qPow( (distance/a), (1/b) );

    return disparity;
}

void DepthFilter::morphOps(Mat &image)
{
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(5,5));
    Mat dilateElement = getStructuringElement( MORPH_ELLIPSE,Size(21,21));

    erode(image,image,erodeElement);
}

void DepthFilter::filterAndMaskImage(Mat imgDisparityGray, int lowerThreshold, int upperThreshold, Mat &imgThreshold)
{
    //floorPlaneFilter(imgDisparityGray);
    inRange(imgDisparityGray,lowerThreshold,upperThreshold,imgThreshold);
    morphOps(imgThreshold);
    imshow("imgThreshold",imgThreshold);
    waitKey();
    //cvtColor(imgThreshold, imgThreshold, CV_GRAY2BGR);
    //bitwise_and(imgOriginal, imgThreshold, imgMasked);
}

void DepthFilter::extractObstacles(Mat imgInput, Mat _imgDisparity, Mat _pointcloud, Mat &imgResult)
{
    int x = 0, y = 0;
    Mat imgMasked;
    imgOriginal = imgInput;
    //pointcloud = _pointcloud;
    imgDisparity = _imgDisparity;

    for(int i = 0; i < 130; i+=10)
    {
        filterAndMaskImage(imgDisparity, 150-i, 160-i, imgMasked);
        detectObstructions(x,y,imgMasked);
    }
}

void DepthFilter::detectObstructions(int &x, int &y, Mat threshold)
{
    Mat temp, temp32SC1;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    std::vector<std::vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    temp.convertTo(temp32SC1, CV_32SC1);

    findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE

    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0)
    {
        int numObjects = hierarchy.size();

        objectFound = false;

        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );

        for( int i = 0; i < contours.size(); i++ )
        { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
             boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        }

        for (int index = 0; index >= 0; index = hierarchy[index][0])
        {

            Moments moment = moments((cv::Mat)contours[index]);
            double area = moment.m00;

            if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA)// && area>refArea)
            {
                Scalar color = Scalar(255,128,0);
                rectangle( imgOriginal, boundRect[index].tl(), boundRect[index].br(), color, 2, 8, 0 );

                // Calculate ROI mean.
                Mat mask = Mat::zeros(imgDisparity.size(), CV_8UC1); // Initialize a mask Mat

                drawContours(mask,contours,index,255,CV_FILLED); //  Give the mask the shape of the detected contour
                auto mean(cv::sum(cv::mean(imgDisparity, mask))); // Calc mean of disp values within mask

                // Position the text near the bounding rectangle;
                Point textPos = boundRect[index].tl();
                textPos.x += 20;
                textPos.y += 20;

                double distance = disp2dist(mean[0]);
                //Write distance on image
                putText(imgOriginal, to_string((int)distance)+" cm",textPos,2,1,Scalar(0,255,0),2);
                cout << "Depth: " << mean[0] << " mm" << endl;

                x = moment.m10/area;
                y = moment.m01/area;

                objectFound = true;
            }
            else
            {
                //objectFound = false;
            }
        }
    }
}

void DepthFilter::getResult(Mat &result)
{
    imgOriginal.copyTo(result);
}

/**
 * @brief DepthFilter::matType2str
 * @param type
 * @return qt_r
 *
 * This function is for debugging or other tests. Returns the Mat type.
 */
QString DepthFilter::matType2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  QString qt_r = QString::fromUtf8(r.c_str());

  return qt_r;
}
