/****************************************************************************
** Meta object code from reading C++ file 'SettingsHandler.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/SettingsHandler.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingsHandler.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSettingsHandlerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSSettingsHandlerENDCLASS = QtMocHelpers::stringData(
    "SettingsHandler",
    "canInterfaceNameChanged",
    "",
    "logUpdateFrequencyChanged",
    "saveClicked",
    "canInterfaceName",
    "logUpdateFrequency",
    "startCanSimulatorClicked",
    "stopCanSimulatorClicked",
    "handleSaveClicked",
    "handleStartCanSimulatorClicked",
    "handleStopCanSimulatorClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSSettingsHandlerENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[16];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[26];
    char stringdata4[12];
    char stringdata5[17];
    char stringdata6[19];
    char stringdata7[25];
    char stringdata8[24];
    char stringdata9[18];
    char stringdata10[31];
    char stringdata11[30];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSSettingsHandlerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSSettingsHandlerENDCLASS_t qt_meta_stringdata_CLASSSettingsHandlerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "SettingsHandler"
        QT_MOC_LITERAL(16, 23),  // "canInterfaceNameChanged"
        QT_MOC_LITERAL(40, 0),  // ""
        QT_MOC_LITERAL(41, 25),  // "logUpdateFrequencyChanged"
        QT_MOC_LITERAL(67, 11),  // "saveClicked"
        QT_MOC_LITERAL(79, 16),  // "canInterfaceName"
        QT_MOC_LITERAL(96, 18),  // "logUpdateFrequency"
        QT_MOC_LITERAL(115, 24),  // "startCanSimulatorClicked"
        QT_MOC_LITERAL(140, 23),  // "stopCanSimulatorClicked"
        QT_MOC_LITERAL(164, 17),  // "handleSaveClicked"
        QT_MOC_LITERAL(182, 30),  // "handleStartCanSimulatorClicked"
        QT_MOC_LITERAL(213, 29)   // "handleStopCanSimulatorClicked"
    },
    "SettingsHandler",
    "canInterfaceNameChanged",
    "",
    "logUpdateFrequencyChanged",
    "saveClicked",
    "canInterfaceName",
    "logUpdateFrequency",
    "startCanSimulatorClicked",
    "stopCanSimulatorClicked",
    "handleSaveClicked",
    "handleStartCanSimulatorClicked",
    "handleStopCanSimulatorClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSettingsHandlerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       2,   78, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    3 /* Public */,
       3,    0,   63,    2, 0x06,    4 /* Public */,
       4,    2,   64,    2, 0x06,    5 /* Public */,
       7,    0,   69,    2, 0x06,    8 /* Public */,
       8,    0,   70,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,   71,    2, 0x0a,   10 /* Public */,
      10,    0,   76,    2, 0x0a,   13 /* Public */,
      11,    0,   77,    2, 0x0a,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       5, QMetaType::QString, 0x00015103, uint(0), 0,
       6, QMetaType::QString, 0x00015103, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject SettingsHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSettingsHandlerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSettingsHandlerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSettingsHandlerENDCLASS_t,
        // property 'canInterfaceName'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'logUpdateFrequency'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SettingsHandler, std::true_type>,
        // method 'canInterfaceNameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'logUpdateFrequencyChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'startCanSimulatorClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopCanSimulatorClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleSaveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleStartCanSimulatorClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleStopCanSimulatorClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SettingsHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->canInterfaceNameChanged(); break;
        case 1: _t->logUpdateFrequencyChanged(); break;
        case 2: _t->saveClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->startCanSimulatorClicked(); break;
        case 4: _t->stopCanSimulatorClicked(); break;
        case 5: _t->handleSaveClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->handleStartCanSimulatorClicked(); break;
        case 7: _t->handleStopCanSimulatorClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsHandler::*)();
            if (_t _q_method = &SettingsHandler::canInterfaceNameChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsHandler::*)();
            if (_t _q_method = &SettingsHandler::logUpdateFrequencyChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsHandler::*)(const QString & , const QString & );
            if (_t _q_method = &SettingsHandler::saveClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsHandler::*)();
            if (_t _q_method = &SettingsHandler::startCanSimulatorClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SettingsHandler::*)();
            if (_t _q_method = &SettingsHandler::stopCanSimulatorClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SettingsHandler *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->canInterfaceName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->logUpdateFrequency(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SettingsHandler *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setCanInterfaceName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setLogUpdateFrequency(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *SettingsHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSettingsHandlerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SettingsHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SettingsHandler::canInterfaceNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsHandler::logUpdateFrequencyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SettingsHandler::saveClicked(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingsHandler::startCanSimulatorClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SettingsHandler::stopCanSimulatorClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
