#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QFileDialog>
#include<QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked() {
    cv::Mat img;                // input image

    QString strFileName = QFileDialog::getOpenFileName();       // bring up open file dialog

       if(strFileName == "") {                                     // if file was not chosen
           //ui->lblChosenFile->setText("file not chosen");          // update label
           return;                                                 // and exit function
       }

    img = cv::imread(strFileName.toStdString());                    // open image

    if (img.empty()) {                                              // if unable to open image
        //ui->lblChosenFile->setText("error: image not read from file");      // update lable with error message
        return;                                                             // and exit function
    }

    QImage qImg = convertOpenCVMatToQtQImage(img);             // convert from OpenCV Mat to Qt QImage

    ui->imgLabel->setPixmap(QPixmap::fromImage(qImg));       // show image on form label
    imshow("Image", img);
}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) {                   // if grayscale image
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    } else if(mat.channels() == 3) {            // if 3 channel color image
        cv::cvtColor(mat, mat, CV_BGR2RGB);     // invert BGR to RGB
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // declare and return a QImage
    } else {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}
