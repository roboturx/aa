/****************************************************************************
** Meta object code from reading C++ file 'mkn.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../aa/mchn/mkn.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mkn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hC_MKN_t {
    const uint offsetsAndSize[6];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_hC_MKN_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_hC_MKN_t qt_meta_stringdata_hC_MKN = {
    {
QT_MOC_LITERAL(0, 6), // "hC_MKN"
QT_MOC_LITERAL(7, 6), // "sgnMkn"
QT_MOC_LITERAL(14, 0) // ""

    },
    "hC_MKN\0sgnMkn\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hC_MKN[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   20,    2, 0x06,    0 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    2,    2,

       0        // eod
};

void hC_MKN::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hC_MKN *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sgnMkn((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hC_MKN::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hC_MKN::sgnMkn)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject hC_MKN::staticMetaObject = { {
    QMetaObject::SuperData::link<hC_tBcreator::staticMetaObject>(),
    qt_meta_stringdata_hC_MKN.offsetsAndSize,
    qt_meta_data_hC_MKN,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_hC_MKN_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QByteArray, std::false_type>



>,
    nullptr
} };


const QMetaObject *hC_MKN::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hC_MKN::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hC_MKN.stringdata0))
        return static_cast<void*>(this);
    return hC_tBcreator::qt_metacast(_clname);
}

int hC_MKN::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = hC_tBcreator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void hC_MKN::sgnMkn(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
