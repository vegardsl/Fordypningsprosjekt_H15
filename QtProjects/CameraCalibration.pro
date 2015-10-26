INCLUDEPATH +=  C:\OpenCV\build\include \
                C:\OpenCV\sources\modules\core\include\opencv2\core \
                C:\OpenCV\sources\modules\cudastereo \
                #"C:\Program Files\PCL 1.7.2\include\pcl-1.7" \
                #"C:\Program Files\PCL 1.6.0\3rdParty\Boost\include" \
                #"C:\Program Files\PCL 1.6.0\3rdParty\Eigen\include" \
                #"C:\Program Files\PCL 1.6.0\3rdParty\FLANN\include" \
                #"C:\Program Files\PCL 1.6.0\3rdParty\Qhull\include" \
                #"C:\Program Files\PCL 1.6.0\3rdParty\VTK\include\vtk-5.8" \


CONFIG(release,debug|release)
{
    LIBS += C:\OpenCV\build\x64\vc12\lib\opencv_ts300.lib \
            C:\OpenCV\build\x64\vc12\lib\opencv_world300.lib \
}

CONFIG(debug,debug|release)
{
    LIBS += "C:\OpenCV\build\x64\vc12\lib\opencv_ts300d.lib" \
            "C:\OpenCV\build\x64\vc12\lib\opencv_world300d.lib" \

}

QT += core
QT -= gui

TARGET = CameraCalibration
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    videostreamthread.cpp \
    calibrationapp.cpp \
    singlecamcalibrator.cpp \
    stereocameracalibration.cpp \
    stereoaligner.cpp \
    disparitycalcthread.cpp

HEADERS += \
    videostreamthread.h \
    calibrationapp.h \
    globalparameters.h \
    singlecamcalibrator.h \
    stereocameracalibration.h \
    stereoaligner.h \
    disparitycalcthread.h

