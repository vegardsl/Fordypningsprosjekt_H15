/****************************************************************************
** Meta object code from reading C++ file 'stereocalibrator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RobotVision/stereocalibrator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stereocalibrator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StereoCalibrator_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StereoCalibrator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StereoCalibrator_t qt_meta_stringdata_StereoCalibrator = {
    {
QT_MOC_LITERAL(0, 0, 16), // "StereoCalibrator"
QT_MOC_LITERAL(1, 17, 10), // "frameReady"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 37, 5), // "frame"
QT_MOC_LITERAL(5, 43, 9), // "frameSide"
QT_MOC_LITERAL(6, 53, 6), // "origin"
QT_MOC_LITERAL(7, 60, 20) // "handleCaptureCommand"

    },
    "StereoCalibrator\0frameReady\0\0cv::Mat\0"
    "frame\0frameSide\0origin\0handleCaptureCommand"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StereoCalibrator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,    5,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void StereoCalibrator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StereoCalibrator *_t = static_cast<StereoCalibrator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->handleCaptureCommand(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StereoCalibrator::*_t)(cv::Mat , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StereoCalibrator::frameReady)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject StereoCalibrator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StereoCalibrator.data,
      qt_meta_data_StereoCalibrator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StereoCalibrator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StereoCalibrator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StereoCalibrator.stringdata0))
        return static_cast<void*>(const_cast< StereoCalibrator*>(this));
    return QObject::qt_metacast(_clname);
}

int StereoCalibrator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void StereoCalibrator::frameReady(cv::Mat _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
