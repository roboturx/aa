/****************************************************************************
** Meta object code from reading C++ file 'ContainerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../examples/not working/Qt-Advanced-Docking-System-master/AdvancedDockingSystem/include/ads/ContainerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContainerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ads__ContainerWidget_t {
    const uint offsetsAndSize[22];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ads__ContainerWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ads__ContainerWidget_t qt_meta_stringdata_ads__ContainerWidget = {
    {
QT_MOC_LITERAL(0, 20), // "ads::ContainerWidget"
QT_MOC_LITERAL(21, 18), // "orientationChanged"
QT_MOC_LITERAL(40, 0), // ""
QT_MOC_LITERAL(41, 16), // "activeTabChanged"
QT_MOC_LITERAL(58, 22), // "SectionContent::RefPtr"
QT_MOC_LITERAL(81, 2), // "sc"
QT_MOC_LITERAL(84, 6), // "active"
QT_MOC_LITERAL(91, 31), // "sectionContentVisibilityChanged"
QT_MOC_LITERAL(123, 7), // "visible"
QT_MOC_LITERAL(131, 18), // "onActiveTabChanged"
QT_MOC_LITERAL(150, 38) // "onActionToggleSectionContentV..."

    },
    "ads::ContainerWidget\0orientationChanged\0"
    "\0activeTabChanged\0SectionContent::RefPtr\0"
    "sc\0active\0sectionContentVisibilityChanged\0"
    "visible\0onActiveTabChanged\0"
    "onActionToggleSectionContentVisibility"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ads__ContainerWidget[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    0 /* Public */,
       3,    2,   45,    2, 0x06,    1 /* Public */,
       7,    2,   50,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   55,    2, 0x08,    7 /* Private */,
      10,    1,   56,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Bool,    5,    6,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Bool,    5,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void ads::ContainerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContainerWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->orientationChanged(); break;
        case 1: _t->activeTabChanged((*reinterpret_cast< const SectionContent::RefPtr(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->sectionContentVisibilityChanged((*reinterpret_cast< const SectionContent::RefPtr(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->onActiveTabChanged(); break;
        case 4: _t->onActionToggleSectionContentVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContainerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContainerWidget::orientationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContainerWidget::*)(const SectionContent::RefPtr & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContainerWidget::activeTabChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContainerWidget::*)(const SectionContent::RefPtr & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContainerWidget::sectionContentVisibilityChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ads::ContainerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_ads__ContainerWidget.offsetsAndSize,
    qt_meta_data_ads__ContainerWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ads__ContainerWidget_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const SectionContent::RefPtr &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const SectionContent::RefPtr &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>


>,
    nullptr
} };


const QMetaObject *ads::ContainerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ads::ContainerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ads__ContainerWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ads::ContainerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ads::ContainerWidget::orientationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ads::ContainerWidget::activeTabChanged(const SectionContent::RefPtr & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ads::ContainerWidget::sectionContentVisibilityChanged(const SectionContent::RefPtr & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
