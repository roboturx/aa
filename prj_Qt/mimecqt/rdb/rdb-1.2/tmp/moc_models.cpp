/****************************************************************************
** Meta object code from reading C++ file 'models.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../demo/models.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'models.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BaseTableModel_t {
    const uint offsetsAndSize[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_BaseTableModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_BaseTableModel_t qt_meta_stringdata_BaseTableModel = {
    {
QT_MOC_LITERAL(0, 14) // "BaseTableModel"

    },
    "BaseTableModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BaseTableModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void BaseTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject BaseTableModel::staticMetaObject = { {
    QMetaObject::SuperData::link<RDB::AbstractTableModel::staticMetaObject>(),
    qt_meta_stringdata_BaseTableModel.offsetsAndSize,
    qt_meta_data_BaseTableModel,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *BaseTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BaseTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BaseTableModel.stringdata0))
        return static_cast<void*>(this);
    return RDB::AbstractTableModel::qt_metacast(_clname);
}

int BaseTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RDB::AbstractTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_CompaniesModel_t {
    const uint offsetsAndSize[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_CompaniesModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_CompaniesModel_t qt_meta_stringdata_CompaniesModel = {
    {
QT_MOC_LITERAL(0, 14) // "CompaniesModel"

    },
    "CompaniesModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CompaniesModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CompaniesModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject CompaniesModel::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseTableModel::staticMetaObject>(),
    qt_meta_stringdata_CompaniesModel.offsetsAndSize,
    qt_meta_data_CompaniesModel,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *CompaniesModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompaniesModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CompaniesModel.stringdata0))
        return static_cast<void*>(this);
    return BaseTableModel::qt_metacast(_clname);
}

int CompaniesModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ProjectsModel_t {
    const uint offsetsAndSize[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ProjectsModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ProjectsModel_t qt_meta_stringdata_ProjectsModel = {
    {
QT_MOC_LITERAL(0, 13) // "ProjectsModel"

    },
    "ProjectsModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProjectsModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ProjectsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject ProjectsModel::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseTableModel::staticMetaObject>(),
    qt_meta_stringdata_ProjectsModel.offsetsAndSize,
    qt_meta_data_ProjectsModel,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *ProjectsModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProjectsModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectsModel.stringdata0))
        return static_cast<void*>(this);
    return BaseTableModel::qt_metacast(_clname);
}

int ProjectsModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PersonsModel_t {
    const uint offsetsAndSize[2];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PersonsModel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PersonsModel_t qt_meta_stringdata_PersonsModel = {
    {
QT_MOC_LITERAL(0, 12) // "PersonsModel"

    },
    "PersonsModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonsModel[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void PersonsModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject PersonsModel::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseTableModel::staticMetaObject>(),
    qt_meta_stringdata_PersonsModel.offsetsAndSize,
    qt_meta_data_PersonsModel,
    qt_static_metacall,
    nullptr,
    nullptr,
    nullptr
} };


const QMetaObject *PersonsModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonsModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonsModel.stringdata0))
        return static_cast<void*>(this);
    return BaseTableModel::qt_metacast(_clname);
}

int PersonsModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseTableModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PersonsFilter_t {
    const uint offsetsAndSize[8];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PersonsFilter_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PersonsFilter_t qt_meta_stringdata_PersonsFilter = {
    {
QT_MOC_LITERAL(0, 13), // "PersonsFilter"
QT_MOC_LITERAL(14, 13), // "setNameFilter"
QT_MOC_LITERAL(28, 0), // ""
QT_MOC_LITERAL(29, 6) // "filter"

    },
    "PersonsFilter\0setNameFilter\0\0filter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonsFilter[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x0a,    0 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void PersonsFilter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PersonsFilter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setNameFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PersonsFilter::staticMetaObject = { {
    QMetaObject::SuperData::link<RDB::AbstractRowFilter::staticMetaObject>(),
    qt_meta_stringdata_PersonsFilter.offsetsAndSize,
    qt_meta_data_PersonsFilter,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PersonsFilter_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>


>,
    nullptr
} };


const QMetaObject *PersonsFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonsFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PersonsFilter.stringdata0))
        return static_cast<void*>(this);
    return RDB::AbstractRowFilter::qt_metacast(_clname);
}

int PersonsFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RDB::AbstractRowFilter::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
