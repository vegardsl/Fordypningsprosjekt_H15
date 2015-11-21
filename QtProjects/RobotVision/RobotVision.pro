#-------------------------------------------------
#
# Project created by QtCreator 2015-11-15T13:07:53
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RobotVision
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videostreamthread.cpp \
    singlecamcalibratorthread.cpp \
    stereocalibrator.cpp \
    stereorectifier.cpp \
    disparitycalcthread.cpp \
    depthfilter.cpp

HEADERS  += mainwindow.h \
    videostreamthread.h \
    singlecamcalibratorthread.h \
    stereocalibrator.h \
    stereorectifier.h \
    disparitycalcthread.h \
    depthfilter.h

FORMS    += mainwindow.ui

INCLUDEPATH +=  C:\\OpenCV\\build\\install\\include \
                C:\\OpenCV\\build\\install\\include\\opencv \
                C:\\OpenCV\\build\\install\\include \\opencv2

CONFIG(release,debug|release)
{
    LIBS += -LC:\\OpenCV\\build\\lib\\Release \
            -lopencv_calib3d300 \
            -lopencv_core300 \
            -lopencv_features2d300 \
            -lopencv_flann300 \
            -lopencv_hal300 \
            -lopencv_highgui300 \
            -lopencv_imgcodecs300 \
            -lopencv_imgproc300 \
            -lopencv_ml300 \
            -lopencv_objdetect300 \
            -lopencv_photo300 \
            -lopencv_shape300 \
            -lopencv_stitching300 \
            -lopencv_superres300 \
            -lopencv_ts300 \
            -lopencv_video300 \
            -lopencv_videoio300 \
            -lopencv_videostab300 \
            -lopencv_xfeatures2d300 \
            -lopencv_xobjdetect300 \
            -lopencv_stereo300
}

CONFIG(debug,debug|release)
{
    LIBS += -LC:\\OpenCV\\build\\lib\\Debug \
            -lopencv_calib3d300d \
            -lopencv_core300d \
            -lopencv_features2d300d \
            -lopencv_flann300d \
            -lopencv_hal300d \
            -lopencv_highgui300d \
            -lopencv_imgcodecs300d \
            -lopencv_imgproc300d \
            -lopencv_ml300d \
            -lopencv_objdetect300d \
            -lopencv_photo300d \
            -lopencv_shape300d \
            -lopencv_stitching300d \
            -lopencv_superres300d \
            -lopencv_ts300d \
            -lopencv_video300d \
            -lopencv_videoio300d \
            -lopencv_videostab300d \
            -lopencv_xfeatures2d300d \
            -lopencv_xobjdetect300d \
            -lopencv_stereo300d
}
