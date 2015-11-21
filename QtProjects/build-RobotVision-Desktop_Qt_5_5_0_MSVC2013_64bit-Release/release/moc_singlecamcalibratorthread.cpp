/****************************************************************************
** Meta object code from reading C++ file 'singlecamcalibratorthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RobotVision/singlecamcalibratorthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'singlecamcalibratorthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SingleCamCalibratorThread_t {
    QByteArrayData data[15];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleCamCalibratorThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleCamCalibratorThread_t qt_meta_stringdata_SingleCamCalibratorThread = {
    {
QT_MOC_LITERAL(0, 0, 25), // "SingleCamCalibratorThread"
QT_MOC_LITERAL(1, 26, 9), // "on_number"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "name"
QT_MOC_LITERAL(4, 42, 6), // "number"
QT_MOC_LITERAL(5, 49, 10), // "frameReady"
QT_MOC_LITERAL(6, 60, 7), // "cv::Mat"
QT_MOC_LITERAL(7, 68, 5), // "frame"
QT_MOC_LITERAL(8, 74, 9), // "frameSide"
QT_MOC_LITERAL(9, 84, 6), // "origin"
QT_MOC_LITERAL(10, 91, 4), // "stop"
QT_MOC_LITERAL(11, 96, 20), // "handleCaptureCommand"
QT_MOC_LITERAL(12, 117, 12), // "recieveFrame"
QT_MOC_LITERAL(13, 130, 8), // "cv::Mat&"
QT_MOC_LITERAL(14, 139, 4) // "side"

    },
    "SingleCamCalibratorThread\0on_number\0"
    "\0name\0number\0frameReady\0cv::Mat\0frame\0"
    "frameSide\0origin\0stop\0handleCaptureCommand\0"
    "recieveFrame\0cv::Mat&\0side"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleCamCalibratorThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    3,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   51,    2, 0x0a /* Public */,
      11,    0,   52,    2, 0x0a /* Public */,
      12,    2,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    7,   14,

       0        // eod
};

void SingleCamCalibratorThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SingleCamCalibratorThread *_t = static_cast<SingleCamCalibratorThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_number((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->frameReady((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->stop(); break;
        case 3: _t->handleCaptureCommand(); break;
        case 4: _t->recieveFrame((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SingleCamCalibratorThread::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SingleCamCalibratorThread::on_number)) {
                *result = 0;
            }
        }
        {
            typedef void (SingleCamCalibratorThread::*_t)(cv::Mat , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SingleCamCalibratorThread::frameReady)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SingleCamCalibratorThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SingleCamCalibratorThread.data,
      qt_meta_data_SingleCamCalibratorThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SingleCamCalibratorThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleCamCalibratorThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SingleCamCalibratorThread.stringdata0))
        return static_cast<void*>(const_cast< SingleCamCalibratorThread*>(this));
    return QObject::qt_metacast(_clname);
}

int SingleCamCalibratorThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SingleCamCalibratorThread::on_number(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SingleCamCalibratorThread::frameReady(cv::Mat _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
