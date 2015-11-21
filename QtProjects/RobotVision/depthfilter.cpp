#include "depthfilter.h"

using namespace cv;
using namespace std;

DepthFilter::DepthFilter()
{

}

DepthFilter::~DepthFilter()
{

}

void DepthFilter::initDepthFilter(int _lowerDispThres, int _upperDispThres)
{
    lowerDispThresh = _lowerDispThres;
    upperDispThresh = _upperDispThres;
}

void DepthFilter::morphOps(Mat &image)
{

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(5,5));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_ELLIPSE,Size(21,21));

    erode(image,image,erodeElement);
    //erode(image,image,erodeElement);


    //dilate(image,image,dilateElement);
    //dilate(image,image,dilateElement);
    //dilate(image,image,dilateElement);
    //dilate(image,image,dilateElement);

    //qDebug() << "Done morphOps";
}

void DepthFilter::filterAndMaskImage(Mat imgDisparityGray, int lowerThreshold, int upperThreshold, Mat &imgThreshold)
{
    inRange(imgDisparityGray,lowerThreshold,upperThreshold,imgThreshold);
    morphOps(imgThreshold);

    //cvtColor(imgThreshold, imgThreshold, CV_GRAY2BGR);
    //bitwise_and(imgOriginal, imgThreshold, imgMasked);
}

void DepthFilter::extractObstacles(Mat imgInput, Mat _imgDisparity, Mat _pointcloud, Mat &imgResult)
{
    int x = 0, y = 0;
    Mat imgMasked;
    imgOriginal = imgInput;
    pointcloud = _pointcloud;
    imgDisparity = _imgDisparity;

    //cvtColor(imgDisparity,imgDisparityGray,CV_BGR2GRAY);
    //imshow("Disparity", imgDisparity);
    for(int i = 0; i < 110; i+=10)
    {
        filterAndMaskImage(imgDisparity, 130-i, 140-i, imgMasked);
        trackFilteredObject(x,y,imgMasked);
        //qDebug() << "Next layer";
        //displayImage(imgOriginal);
        //waitKey();
    }
    //imshow("tracking", imgOriginal);
    //qDebug() << "Next image";
}

void DepthFilter::trackFilteredObject(int &x, int &y, Mat threshold)
{
    Mat temp, temp32SC1;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    std::vector<std::vector<cv::Point> > contours;//vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    temp.convertTo(temp32SC1, CV_32SC1);
    //imshow("temp",temp);
    //waitKey();

    //QString ty = matType2str(temp.type());
    //qDebug() << "Matrix type: " + ty;

    //imshow("Thresh", threshold);
    //waitKey();

    findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE

    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0)
    {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        //if(numObjects < MAX_NUM_OBJECTS)
        //{
            objectFound = false;

            /// Approximate contours to polygons + get bounding rects and circles
            vector<vector<Point> > contours_poly( contours.size() );
            vector<Rect> boundRect( contours.size() );
            vector<Point2f>center( contours.size() );
            vector<float>radius( contours.size() );

            for( int i = 0; i < contours.size(); i++ )
            { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
                 boundRect[i] = boundingRect( Mat(contours_poly[i]) );
            }

            for (int index = 0; index >= 0; index = hierarchy[index][0])
            {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                //qDebug() << "Detected area = " + QString::number(area);
                //qDebug() << "MAX_OBJECT_AREA = " + QString::number(MAX_OBJECT_AREA);
                //qDebug() << "refArea = " + QString::number(refArea);
                //qDebug() << "MIN_OBJECT_AREA = " + QString::number(MIN_OBJECT_AREA);
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA)// && area>refArea)
                {
                    //qDebug() << "Obstruction detected";

                    Scalar color = Scalar(255,128,0);
                    //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
                    rectangle( imgOriginal, boundRect[index].tl(), boundRect[index].br(), color, 2, 8, 0 );
                    //cv::Rect roi(boundRect[index]);
                    //cv::Mat crop(imgDisparity, roi);
                    //cv::Mat crop(pointcloud, roi);
                    //imshow("crop",crop);
                    //waitKey();

                      // Calculate ROI mean.
                    //cv::Mat mask(cv::Mat::zeros(crop.rows, crop.cols, CV_8UC1)); //the mask with the size of cropped image
                    Mat mask = Mat::zeros(imgDisparity.size(), CV_8UC1);
                    //imshow("mask",mask);
                    //waitKey();

                    //Illustrate the contours of detected objects.
                    drawContours(mask,contours,index,255,CV_FILLED);
                    //drawContours(imgDisparity,contours,index,255);
                    //imshow("mask",mask);
                    //imshow("disparity",pointcloud);
                    auto mean(cv::sum(cv::mean(imgDisparity, mask)));


                    //mean(imgDisparity,mask);
                    //imshow("mask", mask);

                    // Position the text inside the bounding rectangle;
                    Point textPos = boundRect[index].tl();
                    textPos.x += 20;
                    textPos.y += 20;

                    putText(imgOriginal, to_string(mean[0]),textPos,2,1,Scalar(0,255,0),2);
                    //cout << "Depth: " << mean[0] << " mm" << endl;


                    waitKey();

                    x = moment.m10/area;
                    y = moment.m01/area;

                    objectFound = true;
                    //refArea = area;
                }
                else
                {
                    //objectFound = false;
                }
            }
            //let user know you found an object
        //}//else putText(imgOriginal,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
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
