/****************************************************************************
** Meta object code from reading C++ file 'proxymodel.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../zipcodes1/proxymodel.hpp"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proxymodel.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_ProxyModel_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[15];
    char stringdata5[18];
    char stringdata6[15];
    char stringdata7[10];
    char stringdata8[7];
    char stringdata9[9];
    char stringdata10[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ProxyModel_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_ProxyModel_t qt_meta_stringdata_ProxyModel = {
    {
        QT_MOC_LITERAL(0, 10),  // "ProxyModel"
        QT_MOC_LITERAL(11, 12),  // "clearFilters"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 17),  // "setMinimumZipcode"
        QT_MOC_LITERAL(43, 14),  // "minimumZipcode"
        QT_MOC_LITERAL(58, 17),  // "setMaximumZipcode"
        QT_MOC_LITERAL(76, 14),  // "maximumZipcode"
        QT_MOC_LITERAL(91, 9),  // "setCounty"
        QT_MOC_LITERAL(101, 6),  // "county"
        QT_MOC_LITERAL(108, 8),  // "setState"
        QT_MOC_LITERAL(117, 5)   // "state"
    },
    "ProxyModel",
    "clearFilters",
    "",
    "setMinimumZipcode",
    "minimumZipcode",
    "setMaximumZipcode",
    "maximumZipcode",
    "setCounty",
    "county",
    "setState",
    "state"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_ProxyModel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    1,   45,    2, 0x0a,    2 /* Public */,
       5,    1,   48,    2, 0x0a,    4 /* Public */,
       7,    1,   51,    2, 0x0a,    6 /* Public */,
       9,    1,   54,    2, 0x0a,    8 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

Q_CONSTINIT const QMetaObject ProxyModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QSortFilterProxyModel::staticMetaObject>(),
    qt_meta_stringdata_ProxyModel.offsetsAndSizes,
    qt_meta_data_ProxyModel,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_ProxyModel_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ProxyModel, std::true_type>,
        // method 'clearFilters'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setMinimumZipcode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setMaximumZipcode'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'setCounty'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'setState'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void ProxyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProxyModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clearFilters(); break;
        case 1: _t->setMinimumZipcode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->setMaximumZipcode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->setCounty((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->setState((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *ProxyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProxyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProxyModel.stringdata0))
        return static_cast<void*>(this);
    return QSortFilterProxyModel::qt_metacast(_clname);
}

int ProxyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSortFilterProxyModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
