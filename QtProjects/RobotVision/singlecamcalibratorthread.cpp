#include "singlecamcalibratorthread.h"
#include "videostreamthread.h"

#define SUCCESS 20
#define FAILED 21

using namespace cv;
using namespace std;

const std::string videoStreamAddress[] = { "http://admin:admin@192.168.0.100:80/video.mjpg",
                                           "http://admin:admin@192.168.0.102:80/video.mjpg" };

SingleCamCalibratorThread::SingleCamCalibratorThread(QObject *parent) : QObject(parent)
{

}
SingleCamCalibratorThread::~SingleCamCalibratorThread()
{

}

void SingleCamCalibratorThread::generateCalibrationSamples(QDir sampleFilePath, QString selectedCamera)
{
    qDebug() << "Selected camera is: "+selectedCamera;
    VideoCapture capture;

    Mat gray;

    cout << "Opening video stream." << endl;

    capture.open(videoStreamAddress[1]);
    if (!capture.isOpened())
    {
        std::cout << "Error when opening video stream: " << "http://admin:admin@192.168.0.100:80/video.mjpg" << std::endl;
        std::cout << "Press any key to quit. " << std::endl;
        getchar();
        //return -1;
    }
    cout << "Video stream successfully opened. Please wait a few seconds... " << std::endl;

    vector<Point3f> ob_p;
    for(int i = 0; i < height_internalCorners; i++) {
        for(int j = 0; j < width_internalCorners; j++) {
            ob_p.push_back(Point3f(j * squareSideLength, i * squareSideLength, 0.f));
        }
    }

    //namedWindow("Chessboard corners");

    vector<Point2f> corners;

    int numberOfSamples = 0;

    cout << "Press 'c' to capture ..." << endl;
    char choice = 'z';
    Mat im_show;
    int count = 0;

    int emptyCount = 0;

    while(1)
    {
        capture.read(cameraFeed);
        if(cameraFeed.empty()){
            //cout << "Waiting for video stream. Stand by." << endl;
            if(emptyCount < 10)
            {
                emptyCount++;
                continue;
            }

            else if(!capture.isOpened())
            {
                qDebug() << "Capture is not opened!";
            }
            else
            {
                qDebug() << "Mat is empty!";
            }
        }


        //cvtColor(cameraFeed, gray, CV_BGR2GRAY);

        //emit frameReady(cameraFeed, side_int, RIGHT_CALIB);
        //qDebug() << "Check 1 Chessboard!";
        //qDebug() << width_internalCorners << height_internalCorners << squareSideLength;

        chessBoardDetected = false;
        chessBoardDetected = findChessboardCorners(cameraFeed, Size(width_internalCorners, height_internalCorners), corners,
        CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);//CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        //qDebug() << "Check 2 Chessboard!";
        if(chessBoardDetected){
            im_show = cameraFeed.clone();
            drawChessboardCorners(im_show, Size(width_internalCorners, height_internalCorners), corners, chessBoardDetected);

            putText(im_show,"Press 'Capture Image' to make a sample image.",Point(0,50),2,1,Scalar(0,0,255),2);
            if(flag_capture_set)
            {
                emit frameReady(~im_show,side_int,origin_int);
                qDebug() << "Capturing!";

                vector<int> compression_params;
                compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
                compression_params.push_back(9);

                QString fileName = "/"+selectedCamera;
                fileName.append(QString::number(count));
                fileName.append(".png");

                QString pathString = sampleFilePath.path();
                pathString.append(fileName);

                Mat gray;
                cvtColor(cameraFeed, gray, CV_BGR2GRAY);

                imwrite(pathString.toLocal8Bit().constData(), gray,compression_params);
                count++;
                flag_capture_set = false;
            }
            else
            {
                //qDebug() << "Show plain";
                emit frameReady(im_show,side_int,origin_int);
            }
        }
        else
        {
            //qDebug() << "No Chessboard!";
            emit frameReady(cameraFeed, side_int, origin_int);
        }
        QThread::currentThread()->msleep(30);
        //qDebug() << "loop iter done";
    }
    //qDebug() << "out of loop";
}

int SingleCamCalibratorThread::initSingleCamCalibrator(QString _selectedCamera,// Change to QString!
                                                  QDir _appDirPath,
                                                  double _squareSideLength,
                                                  int _width_internalCorners,
                                                  int _height_internalCorners)
{
    selectedCamera = _selectedCamera;
    squareSideLength = _squareSideLength;
    width_internalCorners = _width_internalCorners;
    height_internalCorners = _height_internalCorners;
    appDirPath = _appDirPath;
    qDebug() << "Selected camera is: "+selectedCamera;
    const string videoStreamAddress[] = { "http://admin:admin@192.168.0.100:80/video.mjpg", "http://admin:admin@192.168.0.102:80/video.mjpg" };

    // Read images
    QString path = appDirPath.absolutePath();
    if(selectedCamera.contains("left")){
        qDebug() << "Left compare";
        side_int = LEFT;
        origin_int = LEFT_CALIB;
        path.append("/samples/single/left/");
        sampleFilePath.setPath(path);

    }else if(selectedCamera.contains("right")){
        qDebug() << "Right compare";
        side_int = RIGHT;
        origin_int = RIGHT_CALIB;
        path.append("/samples/single/right/");
        sampleFilePath.setPath(path);

    }else{
        qDebug() << "SingleCamCalibrator::initSingleCamCalibrator(): Unvalid camera selection.";
        return FAILED;
    }

    qDebug() << sampleFilePath.absolutePath();

    if(sampleFilePath.count()<3){ // Testing if there are sample images for calibration.
      generateCalibrationSamples(sampleFilePath, selectedCamera);
    }
    if(sampleFilePath.count()<3){ // Testing if samples were really generated.
        return FAILED;
    }

    /*
     * Samples for calibration are available.
     * Now, they will be read into the vector 'images'.
     */
    QString fileName;
    QDirIterator directory_iterator(sampleFilePath, QDirIterator::Subdirectories);
    Mat tempMat;

    while(directory_iterator.hasNext()){
        //qDebug() << directory_iterator.next();

        fileName = sampleFilePath.filePath(directory_iterator.next());
        string file = fileName.toUtf8();

        tempMat = imread(file);
        if(!tempMat.empty()&& tempMat.data)
        {
            images.push_back(imread(file.c_str()));
            cout << file << endl;
        }
    }
    return SUCCESS;
}

void SingleCamCalibratorThread::calc_image_points(bool show) {
    // Calculate the object points in the object co-ordinate system (origin at top left corner)
    vector<Point3f> ob_p;
    for(int i = 0; i < height_internalCorners; i++) {
        for(int j = 0; j < width_internalCorners; j++) {
            ob_p.push_back(Point3f(j * squareSideLength, i * squareSideLength, 0.f));
        }
    }

    //if(show) namedWindow("Chessboard corners");
    for(int i = 0; i < images.size(); i++) {
        Mat im = images[i];
        vector<Point2f> corners;
        //find corners in the chessboard image
        qDebug() << "Looking for chessboard corners";
        bool pattern_found = false;
        try
        {
            pattern_found = findChessboardCorners(im, Size(width_internalCorners, height_internalCorners), corners,
            CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
        }
        catch(Exception& e)
        {
            const char* err_msg = e.what();
            cout << "'findChessboardCorners': Exception caught: " << err_msg << endl;
        }

        if(pattern_found) {
            qDebug() << "Found pattern!";

            object_points.push_back(ob_p);
            Mat gray;
            cvtColor(im, gray, CV_BGR2GRAY);
            //cornerSubPix(gray, im_p, Size(6, 9), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS +
            //CV_TERMCRIT_ITER, 30, 0.1));

            qDebug() << "Break!";
            try
            {
                image_points.push_back(corners);
            }
            catch(Exception& e)
            {
                const char* err_msg = e.what();
                cout << "'image_points.push_back(corners);': Exception caught: " << err_msg << endl;
            }

            if(show) {

                Mat im_show = im.clone();
                try
                {
                    drawChessboardCorners(im_show, Size(width_internalCorners, height_internalCorners), corners, pattern_found);
                    //imshow("Chessboard corners", im_show);
                    emit(frameReady(im_show,side_int,origin_int));
                }
                catch(Exception& e)
                {
                    const char* err_msg = e.what();
                    cout << "'drawChessboardCorners': Exception caught: " << err_msg << endl;
                }

                //while(char(waitKey(1)) != ' ') {}
                //waitKey();
            }
        }
        //if a valid pattern was not found, delete the entry from vector of images
        else images.erase(images.begin() + i);
    }
}
void SingleCamCalibratorThread::calibrate() {
    vector<Mat> rvecs, tvecs;
    float rms_error = calibrateCamera(object_points, image_points, images[0].size(), cameraMatrix,
    distCoeffs, rvecs, tvecs);
    cout << "RMS reprojection error " << rms_error << endl;
}

Mat SingleCamCalibratorThread::get_cameraMatrix() {
    return cameraMatrix;
}

Mat SingleCamCalibratorThread::get_distCoeffs() {
    return distCoeffs;
}

void SingleCamCalibratorThread::start(QString _selectedCamera,
                                      QDir _appDirPath,
                                      double _squareSideLength,
                                      int _width_internalCorners,
                                      int _height_internalCorners)
{
    mStop = false;

    initSingleCamCalibrator(_selectedCamera,_appDirPath, _squareSideLength, _width_internalCorners, _height_internalCorners);
    calc_image_points(true);
    calibrate();
    string filename = "samples/single/" + selectedCamera.toStdString() + "/" + string("cam_calib.xml");
    FileStorage fs(filename, FileStorage::WRITE);
    fs << "cameraMatrix" << get_cameraMatrix();
    fs << "distCoeffs" << get_distCoeffs();
    fs.release();
}

void SingleCamCalibratorThread::recieveFrame(cv::Mat &frame, int side)
{
    cameraFeed = frame;
}

void SingleCamCalibratorThread::stop()
{
    mStop = true;
}

void SingleCamCalibratorThread::handleCaptureCommand()
{
    qDebug() << "Recieved Capture command";
    if(chessBoardDetected)
    {
        qDebug() << "Setting flag.";
        flag_capture_set = true;
    }
}
