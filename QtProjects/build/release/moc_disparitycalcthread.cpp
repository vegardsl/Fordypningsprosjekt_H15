/****************************************************************************
** Meta object code from reading C++ file 'disparitycalcthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../disparitycalcthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'disparitycalcthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DisparityCalcThread_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisparityCalcThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisparityCalcThread_t qt_meta_stringdata_DisparityCalcThread = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DisparityCalcThread"
QT_MOC_LITERAL(1, 20, 21), // "newFrameForProcessing"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 51, 5), // "frame"
QT_MOC_LITERAL(5, 57, 11), // "std::string"
QT_MOC_LITERAL(6, 69, 9) // "frameSide"

    },
    "DisparityCalcThread\0newFrameForProcessing\0"
    "\0cv::Mat\0frame\0std::string\0frameSide"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisparityCalcThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void DisparityCalcThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisparityCalcThread *_t = static_cast<DisparityCalcThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newFrameForProcessing((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject DisparityCalcThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_DisparityCalcThread.data,
      qt_meta_data_DisparityCalcThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DisparityCalcThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisparityCalcThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DisparityCalcThread.stringdata0))
        return static_cast<void*>(const_cast< DisparityCalcThread*>(this));
    return QThread::qt_metacast(_clname);
}

int DisparityCalcThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
