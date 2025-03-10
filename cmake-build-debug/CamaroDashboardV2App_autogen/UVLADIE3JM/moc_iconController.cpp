/****************************************************************************
** Meta object code from reading C++ file 'iconController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/iconController.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iconController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSiconControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSiconControllerENDCLASS = QtMocHelpers::stringData(
    "iconController",
    "leftTurnVisibilityChanged",
    "",
    "rightTurnVisibilityChanged",
    "headlightVisibilityChanged",
    "highBeamVisibilityChanged",
    "isLeftTurnVisible",
    "isRightTurnVisible",
    "isHeadlightVisible",
    "isHighBeamVisible"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSiconControllerENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[15];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[27];
    char stringdata5[26];
    char stringdata6[18];
    char stringdata7[19];
    char stringdata8[19];
    char stringdata9[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSiconControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSiconControllerENDCLASS_t qt_meta_stringdata_CLASSiconControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "iconController"
        QT_MOC_LITERAL(15, 25),  // "leftTurnVisibilityChanged"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 26),  // "rightTurnVisibilityChanged"
        QT_MOC_LITERAL(69, 26),  // "headlightVisibilityChanged"
        QT_MOC_LITERAL(96, 25),  // "highBeamVisibilityChanged"
        QT_MOC_LITERAL(122, 17),  // "isLeftTurnVisible"
        QT_MOC_LITERAL(140, 18),  // "isRightTurnVisible"
        QT_MOC_LITERAL(159, 18),  // "isHeadlightVisible"
        QT_MOC_LITERAL(178, 17)   // "isHighBeamVisible"
    },
    "iconController",
    "leftTurnVisibilityChanged",
    "",
    "rightTurnVisibilityChanged",
    "headlightVisibilityChanged",
    "highBeamVisibilityChanged",
    "isLeftTurnVisible",
    "isRightTurnVisible",
    "isHeadlightVisible",
    "isHighBeamVisible"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSiconControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    5 /* Public */,
       3,    0,   39,    2, 0x06,    6 /* Public */,
       4,    0,   40,    2, 0x06,    7 /* Public */,
       5,    0,   41,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::Bool, 0x00015003, uint(0), 0,
       7, QMetaType::Bool, 0x00015003, uint(1), 0,
       8, QMetaType::Bool, 0x00015003, uint(2), 0,
       9, QMetaType::Bool, 0x00015003, uint(3), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject iconController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSiconControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSiconControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSiconControllerENDCLASS_t,
        // property 'isLeftTurnVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'isRightTurnVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'isHeadlightVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'isHighBeamVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<iconController, std::true_type>,
        // method 'leftTurnVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rightTurnVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'headlightVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'highBeamVisibilityChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void iconController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<iconController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->leftTurnVisibilityChanged(); break;
        case 1: _t->rightTurnVisibilityChanged(); break;
        case 2: _t->headlightVisibilityChanged(); break;
        case 3: _t->highBeamVisibilityChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (iconController::*)();
            if (_t _q_method = &iconController::leftTurnVisibilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (iconController::*)();
            if (_t _q_method = &iconController::rightTurnVisibilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (iconController::*)();
            if (_t _q_method = &iconController::headlightVisibilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (iconController::*)();
            if (_t _q_method = &iconController::highBeamVisibilityChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<iconController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isLeftTurnVisible(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isRightTurnVisible(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isHeadlightVisible(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->isHighBeamVisible(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<iconController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLeftTurnVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setRightTurnVisible(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setHeadlightVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setHighBeamVisible(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *iconController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *iconController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSiconControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int iconController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void iconController::leftTurnVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void iconController::rightTurnVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void iconController::headlightVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void iconController::highBeamVisibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
