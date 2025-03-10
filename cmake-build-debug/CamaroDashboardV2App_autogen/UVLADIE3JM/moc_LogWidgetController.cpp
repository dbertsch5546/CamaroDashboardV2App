/****************************************************************************
** Meta object code from reading C++ file 'LogWidgetController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/LogWidgetController.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LogWidgetController.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS = QtMocHelpers::stringData(
    "LogWidgetController",
    "logTextChanged",
    "",
    "xValueChanged",
    "yValueChanged",
    "widthChanged",
    "heightChanged",
    "fontSizeChanged",
    "fontColorChanged",
    "updateTimeout",
    "logText",
    "xValue",
    "yValue",
    "width",
    "height",
    "fontSize",
    "fontColor"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS_t {
    uint offsetsAndSizes[34];
    char stringdata0[20];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[14];
    char stringdata5[13];
    char stringdata6[14];
    char stringdata7[16];
    char stringdata8[17];
    char stringdata9[14];
    char stringdata10[8];
    char stringdata11[7];
    char stringdata12[7];
    char stringdata13[6];
    char stringdata14[7];
    char stringdata15[9];
    char stringdata16[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS_t qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 19),  // "LogWidgetController"
        QT_MOC_LITERAL(20, 14),  // "logTextChanged"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 13),  // "xValueChanged"
        QT_MOC_LITERAL(50, 13),  // "yValueChanged"
        QT_MOC_LITERAL(64, 12),  // "widthChanged"
        QT_MOC_LITERAL(77, 13),  // "heightChanged"
        QT_MOC_LITERAL(91, 15),  // "fontSizeChanged"
        QT_MOC_LITERAL(107, 16),  // "fontColorChanged"
        QT_MOC_LITERAL(124, 13),  // "updateTimeout"
        QT_MOC_LITERAL(138, 7),  // "logText"
        QT_MOC_LITERAL(146, 6),  // "xValue"
        QT_MOC_LITERAL(153, 6),  // "yValue"
        QT_MOC_LITERAL(160, 5),  // "width"
        QT_MOC_LITERAL(166, 6),  // "height"
        QT_MOC_LITERAL(173, 8),  // "fontSize"
        QT_MOC_LITERAL(182, 9)   // "fontColor"
    },
    "LogWidgetController",
    "logTextChanged",
    "",
    "xValueChanged",
    "yValueChanged",
    "widthChanged",
    "heightChanged",
    "fontSizeChanged",
    "fontColorChanged",
    "updateTimeout",
    "logText",
    "xValue",
    "yValue",
    "width",
    "height",
    "fontSize",
    "fontColor"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSLogWidgetControllerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       7,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    8 /* Public */,
       3,    0,   63,    2, 0x06,    9 /* Public */,
       4,    0,   64,    2, 0x06,   10 /* Public */,
       5,    0,   65,    2, 0x06,   11 /* Public */,
       6,    0,   66,    2, 0x06,   12 /* Public */,
       7,    0,   67,    2, 0x06,   13 /* Public */,
       8,    0,   68,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   69,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00015103, uint(0), 0,
      11, QMetaType::Int, 0x00015103, uint(1), 0,
      12, QMetaType::Int, 0x00015103, uint(2), 0,
      13, QMetaType::Int, 0x00015103, uint(3), 0,
      14, QMetaType::Int, 0x00015103, uint(4), 0,
      15, QMetaType::Int, 0x00015103, uint(5), 0,
      16, QMetaType::QString, 0x00015103, uint(6), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject LogWidgetController::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSLogWidgetControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS_t,
        // property 'logText'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'xValue'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'yValue'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'width'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'height'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'fontSize'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'fontColor'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<LogWidgetController, std::true_type>,
        // method 'logTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'xValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'yValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'widthChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'heightChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fontSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fontColorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTimeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void LogWidgetController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LogWidgetController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->logTextChanged(); break;
        case 1: _t->xValueChanged(); break;
        case 2: _t->yValueChanged(); break;
        case 3: _t->widthChanged(); break;
        case 4: _t->heightChanged(); break;
        case 5: _t->fontSizeChanged(); break;
        case 6: _t->fontColorChanged(); break;
        case 7: _t->updateTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::logTextChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::xValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::yValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::widthChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::heightChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::fontSizeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LogWidgetController::*)();
            if (_t _q_method = &LogWidgetController::fontColorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LogWidgetController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->logText(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->xValue(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->yValue(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->width(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->height(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->fontSize(); break;
        case 6: *reinterpret_cast< QString*>(_v) = _t->fontColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LogWidgetController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLogText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setXValue(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setYValue(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setHeight(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setFontSize(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setFontColor(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *LogWidgetController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogWidgetController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSLogWidgetControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int LogWidgetController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
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
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void LogWidgetController::logTextChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LogWidgetController::xValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LogWidgetController::yValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LogWidgetController::widthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void LogWidgetController::heightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void LogWidgetController::fontSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void LogWidgetController::fontColorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
