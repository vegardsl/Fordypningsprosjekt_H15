/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RobotVision/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[457];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 25), // "startSingleCamCalibration"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "notifyCaptureClicked"
QT_MOC_LITERAL(4, 59, 24), // "notifyEndSamplingClicked"
QT_MOC_LITERAL(5, 84, 37), // "on_actionToggle_Left_Camera_t..."
QT_MOC_LITERAL(6, 122, 38), // "on_actionToggle_Right_Camera_..."
QT_MOC_LITERAL(7, 161, 41), // "on_actionCalibrate_Right_Came..."
QT_MOC_LITERAL(8, 203, 40), // "on_actionCalibrate_Left_Camer..."
QT_MOC_LITERAL(9, 244, 18), // "on_capture_clicked"
QT_MOC_LITERAL(10, 263, 22), // "on_endSampling_clicked"
QT_MOC_LITERAL(11, 286, 42), // "on_actionCalibrate_Stereo_Cam..."
QT_MOC_LITERAL(12, 329, 33), // "on_actionRectify_Images_trigg..."
QT_MOC_LITERAL(13, 363, 42), // "on_actionToggle_Depth_Percept..."
QT_MOC_LITERAL(14, 406, 20), // "recieveStreamedFrame"
QT_MOC_LITERAL(15, 427, 7), // "cv::Mat"
QT_MOC_LITERAL(16, 435, 9), // "newNumber"
QT_MOC_LITERAL(17, 445, 4), // "name"
QT_MOC_LITERAL(18, 450, 6) // "number"

    },
    "MainWindow\0startSingleCamCalibration\0"
    "\0notifyCaptureClicked\0notifyEndSamplingClicked\0"
    "on_actionToggle_Left_Camera_triggered\0"
    "on_actionToggle_Right_Camera_triggered\0"
    "on_actionCalibrate_Right_Camera_triggered\0"
    "on_actionCalibrate_Left_Camera_triggered\0"
    "on_capture_clicked\0on_endSampling_clicked\0"
    "on_actionCalibrate_Stereo_Camera_triggered\0"
    "on_actionRectify_Images_triggered\0"
    "on_actionToggle_Depth_Perception_triggered\0"
    "recieveStreamedFrame\0cv::Mat\0newNumber\0"
    "name\0number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    3,   96,    2, 0x0a /* Public */,
      16,    2,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   17,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSingleCamCalibration(); break;
        case 1: _t->notifyCaptureClicked(); break;
        case 2: _t->notifyEndSamplingClicked(); break;
        case 3: _t->on_actionToggle_Left_Camera_triggered(); break;
        case 4: _t->on_actionToggle_Right_Camera_triggered(); break;
        case 5: _t->on_actionCalibrate_Right_Camera_triggered(); break;
        case 6: _t->on_actionCalibrate_Left_Camera_triggered(); break;
        case 7: _t->on_capture_clicked(); break;
        case 8: _t->on_endSampling_clicked(); break;
        case 9: _t->on_actionCalibrate_Stereo_Camera_triggered(); break;
        case 10: _t->on_actionRectify_Images_triggered(); break;
        case 11: _t->on_actionToggle_Depth_Perception_triggered(); break;
        case 12: _t->recieveStreamedFrame((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->newNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startSingleCamCalibration)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::notifyCaptureClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::notifyEndSamplingClicked)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startSingleCamCalibration()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MainWindow::notifyCaptureClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::notifyEndSamplingClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
