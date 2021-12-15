/****************************************************************************
** Meta object code from reading C++ file 'mlzm.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../mlzm/mlzm.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mlzm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hC_MLZM_t {
    const uint offsetsAndSize[22];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_hC_MLZM_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_hC_MLZM_t qt_meta_stringdata_hC_MLZM = {
    {
QT_MOC_LITERAL(0, 7), // "hC_MLZM"
QT_MOC_LITERAL(8, 10), // "sgnMalzeme"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 4), // "int*"
QT_MOC_LITERAL(25, 6), // "sgnKod"
QT_MOC_LITERAL(32, 8), // "QString*"
QT_MOC_LITERAL(41, 9), // "sgnBarkod"
QT_MOC_LITERAL(51, 8), // "sgnBirim"
QT_MOC_LITERAL(60, 14), // "slt_Mlzm_hesap"
QT_MOC_LITERAL(75, 11), // "QModelIndex"
QT_MOC_LITERAL(87, 5) // "Index"

    },
    "hC_MLZM\0sgnMalzeme\0\0int*\0sgnKod\0"
    "QString*\0sgnBarkod\0sgnBirim\0slt_Mlzm_hesap\0"
    "QModelIndex\0Index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hC_MLZM[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,   35,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5,    4,    6,    1,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void hC_MLZM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hC_MLZM *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sgnMalzeme((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< QString*(*)>(_a[2])),(*reinterpret_cast< QString*(*)>(_a[3])),(*reinterpret_cast< QString*(*)>(_a[4]))); break;
        case 1: _t->slt_Mlzm_hesap((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hC_MLZM::*)(int * , QString * , QString * , QString * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hC_MLZM::sgnMalzeme)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject hC_MLZM::staticMetaObject = { {
    QMetaObject::SuperData::link<hC_tBcreator::staticMetaObject>(),
    qt_meta_stringdata_hC_MLZM.offsetsAndSize,
    qt_meta_data_hC_MLZM,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_hC_MLZM_t
, QtPrivate::TypeAndForceComplete<hC_MLZM, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int *, std::false_type>, QtPrivate::TypeAndForceComplete<QString *, std::false_type>, QtPrivate::TypeAndForceComplete<QString *, std::false_type>, QtPrivate::TypeAndForceComplete<QString *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QModelIndex, std::false_type>


>,
    nullptr
} };


const QMetaObject *hC_MLZM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hC_MLZM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hC_MLZM.stringdata0))
        return static_cast<void*>(this);
    return hC_tBcreator::qt_metacast(_clname);
}

int hC_MLZM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = hC_tBcreator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void hC_MLZM::sgnMalzeme(int * _t1, QString * _t2, QString * _t3, QString * _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
