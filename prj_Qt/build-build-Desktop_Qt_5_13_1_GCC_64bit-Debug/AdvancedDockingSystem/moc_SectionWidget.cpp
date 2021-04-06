/****************************************************************************
** Meta object code from reading C++ file 'SectionWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../examples/not working/Qt-Advanced-Docking-System-master/AdvancedDockingSystem/include/ads/SectionWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SectionWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ads__SectionWidget_t {
    const uint offsetsAndSize[16];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_ads__SectionWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_ads__SectionWidget_t qt_meta_stringdata_ads__SectionWidget = {
    {
QT_MOC_LITERAL(0, 18), // "ads::SectionWidget"
QT_MOC_LITERAL(19, 15), // "setCurrentIndex"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 5), // "index"
QT_MOC_LITERAL(42, 21), // "onSectionTitleClicked"
QT_MOC_LITERAL(64, 20), // "onCloseButtonClicked"
QT_MOC_LITERAL(85, 25), // "onTabsMenuActionTriggered"
QT_MOC_LITERAL(111, 14) // "updateTabsMenu"

    },
    "ads::SectionWidget\0setCurrentIndex\0\0"
    "index\0onSectionTitleClicked\0"
    "onCloseButtonClicked\0onTabsMenuActionTriggered\0"
    "updateTabsMenu"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ads__SectionWidget[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x0a,    0 /* Public */,
       4,    0,   47,    2, 0x08,    2 /* Private */,
       5,    0,   48,    2, 0x08,    3 /* Private */,
       6,    1,   49,    2, 0x08,    4 /* Private */,
       7,    0,   52,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void ads::SectionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SectionWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setCurrentIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onSectionTitleClicked(); break;
        case 2: _t->onCloseButtonClicked(); break;
        case 3: _t->onTabsMenuActionTriggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->updateTabsMenu(); break;
        default: ;
        }
    }
}

const QMetaObject ads::SectionWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_ads__SectionWidget.offsetsAndSize,
    qt_meta_data_ads__SectionWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ads__SectionWidget_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ads::SectionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ads::SectionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ads__SectionWidget.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int ads::SectionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
