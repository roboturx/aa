/****************************************************************************
** Meta object code from reading C++ file 'mkn_modeli.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../mchn/mkn_modeli.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mkn_modeli.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hC_MKMODL_t {
    const uint offsetsAndSize[8];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_hC_MKMODL_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_hC_MKMODL_t qt_meta_stringdata_hC_MKMODL = {
    {
QT_MOC_LITERAL(0, 9), // "hC_MKMODL"
QT_MOC_LITERAL(10, 9), // "sgnmkModl"
QT_MOC_LITERAL(20, 0), // ""
QT_MOC_LITERAL(21, 8) // "QString*"

    },
    "hC_MKMODL\0sgnmkModl\0\0QString*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hC_MKMODL[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void hC_MKMODL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hC_MKMODL *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sgnmkModl((*reinterpret_cast< QString*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hC_MKMODL::*)(QString * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hC_MKMODL::sgnmkModl)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject hC_MKMODL::staticMetaObject = { {
    QMetaObject::SuperData::link<hC_tBcreator::staticMetaObject>(),
    qt_meta_stringdata_hC_MKMODL.offsetsAndSize,
    qt_meta_data_hC_MKMODL,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_hC_MKMODL_t
, QtPrivate::TypeAndForceComplete<hC_MKMODL, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString *, std::false_type>



>,
    nullptr
} };


const QMetaObject *hC_MKMODL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hC_MKMODL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hC_MKMODL.stringdata0))
        return static_cast<void*>(this);
    return hC_tBcreator::qt_metacast(_clname);
}

int hC_MKMODL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void hC_MKMODL::sgnmkModl(QString * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
