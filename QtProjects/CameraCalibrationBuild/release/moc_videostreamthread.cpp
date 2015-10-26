/****************************************************************************
** Meta object code from reading C++ file 'videostreamthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CameraCalibration/videostreamthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videostreamthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoStreamThread_t {
    QByteArrayData data[7];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoStreamThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoStreamThread_t qt_meta_stringdata_VideoStreamThread = {
    {
QT_MOC_LITERAL(0, 0, 17), // "VideoStreamThread"
QT_MOC_LITERAL(1, 18, 10), // "frameReady"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 38, 5), // "frame"
QT_MOC_LITERAL(5, 44, 11), // "std::string"
QT_MOC_LITERAL(6, 56, 9) // "frameSide"

    },
    "VideoStreamThread\0frameReady\0\0cv::Mat\0"
    "frame\0std::string\0frameSide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoStreamThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void VideoStreamThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoStreamThread *_t = static_cast<VideoStreamThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameReady((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoStreamThread::*_t)(cv::Mat , std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoStreamThread::frameReady)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject VideoStreamThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VideoStreamThread.data,
      qt_meta_data_VideoStreamThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoStreamThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoStreamThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoStreamThread.stringdata0))
        return static_cast<void*>(const_cast< VideoStreamThread*>(this));
    return QThread::qt_metacast(_clname);
}

int VideoStreamThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VideoStreamThread::frameReady(cv::Mat _t1, std::string _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
