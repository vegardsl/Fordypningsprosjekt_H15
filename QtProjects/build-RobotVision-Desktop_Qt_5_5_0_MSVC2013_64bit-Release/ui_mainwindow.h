/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStereo_Calibration;
    QAction *actionToggle_Left_Camera;
    QAction *actionToggle_Right_Camera;
    QAction *actionCalibrate_Left_Camera;
    QAction *actionCalibrate_Right_Camera;
    QAction *actionCalibrate_Stereo_Camera;
    QAction *actionRectify_Images;
    QAction *actionToggle_Depth_Perception;
    QAction *actionShow_Alignment;
    QWidget *centralWidget;
    QFrame *frame;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QLabel *leftLabel;
    QFrame *frame_3;
    QLabel *rightLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *capture;
    QPushButton *endSampling;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuVideo;
    QMenu *menuLive_Stream;
    QMenu *menuCalibration;
    QMenu *menuCamera_Calibration;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1400, 700);
        MainWindow->setMinimumSize(QSize(1400, 700));
        MainWindow->setMaximumSize(QSize(16777215, 703));
        actionStereo_Calibration = new QAction(MainWindow);
        actionStereo_Calibration->setObjectName(QStringLiteral("actionStereo_Calibration"));
        actionToggle_Left_Camera = new QAction(MainWindow);
        actionToggle_Left_Camera->setObjectName(QStringLiteral("actionToggle_Left_Camera"));
        actionToggle_Right_Camera = new QAction(MainWindow);
        actionToggle_Right_Camera->setObjectName(QStringLiteral("actionToggle_Right_Camera"));
        actionCalibrate_Left_Camera = new QAction(MainWindow);
        actionCalibrate_Left_Camera->setObjectName(QStringLiteral("actionCalibrate_Left_Camera"));
        actionCalibrate_Right_Camera = new QAction(MainWindow);
        actionCalibrate_Right_Camera->setObjectName(QStringLiteral("actionCalibrate_Right_Camera"));
        actionCalibrate_Stereo_Camera = new QAction(MainWindow);
        actionCalibrate_Stereo_Camera->setObjectName(QStringLiteral("actionCalibrate_Stereo_Camera"));
        actionRectify_Images = new QAction(MainWindow);
        actionRectify_Images->setObjectName(QStringLiteral("actionRectify_Images"));
        actionToggle_Depth_Perception = new QAction(MainWindow);
        actionToggle_Depth_Perception->setObjectName(QStringLiteral("actionToggle_Depth_Perception"));
        actionShow_Alignment = new QAction(MainWindow);
        actionShow_Alignment->setObjectName(QStringLiteral("actionShow_Alignment"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(1400, 650));
        centralWidget->setMaximumSize(QSize(1400, 650));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 1371, 621));
        frame->setAutoFillBackground(false);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 1341, 531));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(650, 370));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        leftLabel = new QLabel(frame_2);
        leftLabel->setObjectName(QStringLiteral("leftLabel"));
        leftLabel->setGeometry(QRect(10, 10, 640, 512));
        leftLabel->setMinimumSize(QSize(640, 512));

        horizontalLayout->addWidget(frame_2);

        frame_3 = new QFrame(layoutWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(650, 370));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Raised);
        rightLabel = new QLabel(frame_3);
        rightLabel->setObjectName(QStringLiteral("rightLabel"));
        rightLabel->setGeometry(QRect(10, 10, 640, 512));
        rightLabel->setMinimumSize(QSize(640, 512));

        horizontalLayout->addWidget(frame_3);

        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 590, 188, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        capture = new QPushButton(layoutWidget1);
        capture->setObjectName(QStringLiteral("capture"));

        horizontalLayout_2->addWidget(capture);

        endSampling = new QPushButton(layoutWidget1);
        endSampling->setObjectName(QStringLiteral("endSampling"));

        horizontalLayout_2->addWidget(endSampling);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuVideo = new QMenu(menuBar);
        menuVideo->setObjectName(QStringLiteral("menuVideo"));
        menuLive_Stream = new QMenu(menuVideo);
        menuLive_Stream->setObjectName(QStringLiteral("menuLive_Stream"));
        menuCalibration = new QMenu(menuBar);
        menuCalibration->setObjectName(QStringLiteral("menuCalibration"));
        menuCamera_Calibration = new QMenu(menuCalibration);
        menuCamera_Calibration->setObjectName(QStringLiteral("menuCamera_Calibration"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuVideo->menuAction());
        menuBar->addAction(menuCalibration->menuAction());
        menuVideo->addAction(menuLive_Stream->menuAction());
        menuVideo->addAction(actionToggle_Depth_Perception);
        menuLive_Stream->addAction(actionToggle_Left_Camera);
        menuLive_Stream->addAction(actionToggle_Right_Camera);
        menuCalibration->addAction(menuCamera_Calibration->menuAction());
        menuCalibration->addAction(actionShow_Alignment);
        menuCamera_Calibration->addAction(actionCalibrate_Left_Camera);
        menuCamera_Calibration->addAction(actionCalibrate_Right_Camera);
        menuCamera_Calibration->addAction(actionCalibrate_Stereo_Camera);
        menuCamera_Calibration->addAction(actionRectify_Images);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionStereo_Calibration->setText(QApplication::translate("MainWindow", "Stereo Calibration", 0));
        actionToggle_Left_Camera->setText(QApplication::translate("MainWindow", "Toggle Left Camera on/off", 0));
        actionToggle_Right_Camera->setText(QApplication::translate("MainWindow", "Toggle Right Camera on/off", 0));
        actionCalibrate_Left_Camera->setText(QApplication::translate("MainWindow", "Calibrate Left Camera", 0));
        actionCalibrate_Right_Camera->setText(QApplication::translate("MainWindow", "Calibrate Right Camera", 0));
        actionCalibrate_Stereo_Camera->setText(QApplication::translate("MainWindow", "Calibrate Stereo Camera", 0));
        actionRectify_Images->setText(QApplication::translate("MainWindow", "Rectify Images", 0));
        actionToggle_Depth_Perception->setText(QApplication::translate("MainWindow", "Toggle Depth Perception", 0));
        actionShow_Alignment->setText(QApplication::translate("MainWindow", "Show Alignment", 0));
        leftLabel->setText(QString());
        rightLabel->setText(QString());
        capture->setText(QApplication::translate("MainWindow", "Capture Image", 0));
        endSampling->setText(QApplication::translate("MainWindow", "End Sampling Mode", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuVideo->setTitle(QApplication::translate("MainWindow", "Video", 0));
        menuLive_Stream->setTitle(QApplication::translate("MainWindow", "Live Stream", 0));
        menuCalibration->setTitle(QApplication::translate("MainWindow", "Calibration", 0));
        menuCamera_Calibration->setTitle(QApplication::translate("MainWindow", "Camera Calibration", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
