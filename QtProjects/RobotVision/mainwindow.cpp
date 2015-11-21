#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
using namespace std;

const std::string videoStreamAddress[] = { "http://admin:admin@192.168.0.100:80/video.mjpg",
                                           "http://admin:admin@192.168.0.102:80/video.mjpg" };

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initSignalsAndSlots();

    dir.mkpath("samples/single/left/");
    dir.mkpath("samples/single/right/");
    dir.mkpath("samples/stereo/left/");
    dir.mkpath("samples/stereo/right/");
    qDebug() << dir.absolutePath();
    appPath = dir.absolutePath();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSignalsAndSlots()
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<int>("int");


    QObject::connect(&leftStreamThread, &VideoStreamThread::frameReady,
                     this, &MainWindow::recieveStreamedFrame
                     );

    QObject::connect(&rightStreamThread, &VideoStreamThread::frameReady,
                     this, &MainWindow::recieveStreamedFrame
                     );
}

void MainWindow::recieveStreamedFrame(Mat frame, int side, int origin)
{
    //qDebug() << "Frame received at slot.";
    if(side == LEFT)
    {
        if(origin == leftMode)
        {
            displayImage(frame, LEFT);
        }
    }
    else if(side == RIGHT)
    {
        if(origin == rightMode)
        {
            displayImage(frame, RIGHT);
        }
    }
}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) // if grayscale image
    {
        return QImage((uchar*)mat.data,
                      mat.cols,
                      mat.rows,
                      mat.step,
                      QImage::Format_Indexed8
                      );      // declare and return a QImage
    }
    else if(mat.channels() == 3) // if 3 channel color image
    {
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data,
                      mat.cols,
                      mat.rows,
                      mat.step,
                      QImage::Format_RGB888
                      );       // declare and return a QImage
    }
    else
    {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage(); // return a blank QImage if the above did not work
}

void MainWindow::displayImage(Mat image, int selectedLabel)
{
    if(image.empty())
    {
        //TODO: Handle error in 'image' input.
        qDebug() << "Image to be displayed is empty.";
        return;
    }

    /*
    QDateTime timestamp(QDateTime::currentDateTime());
    QString dateQString = timestamp.toString();
    string dateString = dateQString.toLocal8Bit().constData();
    putText(image,dateString,Point(0,50),2,1,Scalar(0,0,255),2);
    */
    Mat tmp, dst;
    tmp = image;
    dst = tmp;
    pyrDown(tmp,dst,Size(tmp.cols/2, tmp.rows/2) );

    QImage qImage = convertOpenCVMatToQtQImage(dst);

    if(selectedLabel == LEFT)
    {
        ui->leftLabel->setPixmap(QPixmap::fromImage(qImage));   // show image on label
    }
    else if(selectedLabel == RIGHT)
    {
        ui->rightLabel->setPixmap(QPixmap::fromImage(qImage));   // show image on label
    }
    else
    {
        //TODO: Handle error in 'selectedLabel' input.
        return;
    }
}

// ---- User Action Event Handlers --------------------------------------------
void MainWindow::on_actionToggle_Left_Camera_triggered()
{
    leftMode = VIDEO_STREAM;
    leftStreamThread.beginVideoStream(videoStreamAddress[LEFT],LEFT);
}

void MainWindow::on_actionToggle_Right_Camera_triggered()
{
    rightMode = VIDEO_STREAM;
    rightStreamThread.beginVideoStream(videoStreamAddress[RIGHT],RIGHT);
}

void MainWindow::on_actionCalibrate_Right_Camera_triggered()
{
    qDebug() << "Calib Right Triggered";
    rightMode = RIGHT_CALIB;

    connect(&r_singleCamCalibrator, &SingleCamCalibratorThread::on_number,
            this, &MainWindow::newNumber);

    connect(this, &MainWindow::notifyCaptureClicked,&r_singleCamCalibrator,&SingleCamCalibratorThread::handleCaptureCommand);

    connect(&r_singleCamCalibrator, &SingleCamCalibratorThread::frameReady,this, &MainWindow::recieveStreamedFrame);

    QFuture<void> test = QtConcurrent::run(&this->r_singleCamCalibrator,
                                           &SingleCamCalibratorThread::start,
                                           QString("right"),
                                           QDir(dir),
                                           int(chessSquareSideLength),
                                           int(chessSquaresWide),
                                           int(chessSquaresHigh));
}

void MainWindow::on_actionCalibrate_Left_Camera_triggered()
{
    leftMode = LEFT_CALIB;

    connect(&l_singleCamCalibrator, &SingleCamCalibratorThread::on_number,
            this, &MainWindow::newNumber);

    connect(this, &MainWindow::notifyCaptureClicked,&l_singleCamCalibrator,&SingleCamCalibratorThread::handleCaptureCommand);

    connect(&l_singleCamCalibrator, &SingleCamCalibratorThread::frameReady,this, &MainWindow::recieveStreamedFrame);

    QFuture<void> test = QtConcurrent::run(&this->l_singleCamCalibrator,
                                           &SingleCamCalibratorThread::start,
                                           QString("left"),
                                           QDir(dir),
                                           int(chessSquareSideLength),
                                           int(chessSquaresWide),
                                           int(chessSquaresHigh));
}

void MainWindow::newNumber(QString name, int number)
{
    qDebug() << "From dialog: " << name << " " << number;
}


void MainWindow::on_capture_clicked()
{
    emit notifyCaptureClicked();
    qDebug() << "Capture Clicked";
}

void MainWindow::on_endSampling_clicked()
{
    emit notifyEndSamplingClicked();
    qDebug() << "end sampling";
}

void MainWindow::on_actionCalibrate_Stereo_Camera_triggered()
{
    leftMode = STEREO_CALIB;
    rightMode = STEREO_CALIB;

    qDebug() << "Stereo calibration";

    connect(this, &MainWindow::notifyCaptureClicked,&stereoCalibrator,&StereoCalibrator::handleCaptureCommand);

    connect(&stereoCalibrator, &StereoCalibrator::frameReady,this, &MainWindow::recieveStreamedFrame);

    QFuture<void> test = QtConcurrent::run(&this->stereoCalibrator,
                                           &StereoCalibrator::start,
                                           QDir(dir),
                                           int(chessSquareSideLength),
                                           int(chessSquaresWide),
                                           int(chessSquaresHigh));
}

void MainWindow::on_actionRectify_Images_triggered()
{
    leftMode = STEREO_CALIB;
    rightMode = STEREO_CALIB;

    connect(&stereoRectifier, &StereoRectifier::frameReady,this, &MainWindow::recieveStreamedFrame);

    QFuture<void> test = QtConcurrent::run(&this->stereoRectifier,
                                           &StereoRectifier::start,
                                           QString(appPath));
}

void MainWindow::on_actionToggle_Depth_Perception_triggered()
{
    leftMode = DISPARITY;
    rightMode = DISPARITY;

    connect(&disparityCalcThread, &DisparityCalcThread::frameReady,this, &MainWindow::recieveStreamedFrame);

    QFuture<void> test = QtConcurrent::run(&this->disparityCalcThread,
                                           &DisparityCalcThread::start,
                                           QString(appPath));
}
