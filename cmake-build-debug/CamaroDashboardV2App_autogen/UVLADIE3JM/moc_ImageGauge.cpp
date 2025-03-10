/****************************************************************************
** Meta object code from reading C++ file 'ImageGauge.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ImageGauge.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageGauge.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSImageGaugeENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSImageGaugeENDCLASS = QtMocHelpers::stringData(
    "ImageGauge",
    "imagePrefixChanged",
    "",
    "minValueChanged",
    "maxValueChanged",
    "numImagesChanged",
    "valueChanged",
    "xValueChanged",
    "yValueChanged",
    "sourceStringChanged",
    "imagePrefix",
    "numImages",
    "value",
    "xValue",
    "yValue",
    "sourceString"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSImageGaugeENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[11];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[16];
    char stringdata5[17];
    char stringdata6[13];
    char stringdata7[14];
    char stringdata8[14];
    char stringdata9[20];
    char stringdata10[12];
    char stringdata11[10];
    char stringdata12[6];
    char stringdata13[7];
    char stringdata14[7];
    char stringdata15[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSImageGaugeENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSImageGaugeENDCLASS_t qt_meta_stringdata_CLASSImageGaugeENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "ImageGauge"
        QT_MOC_LITERAL(11, 18),  // "imagePrefixChanged"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 15),  // "minValueChanged"
        QT_MOC_LITERAL(47, 15),  // "maxValueChanged"
        QT_MOC_LITERAL(63, 16),  // "numImagesChanged"
        QT_MOC_LITERAL(80, 12),  // "valueChanged"
        QT_MOC_LITERAL(93, 13),  // "xValueChanged"
        QT_MOC_LITERAL(107, 13),  // "yValueChanged"
        QT_MOC_LITERAL(121, 19),  // "sourceStringChanged"
        QT_MOC_LITERAL(141, 11),  // "imagePrefix"
        QT_MOC_LITERAL(153, 9),  // "numImages"
        QT_MOC_LITERAL(163, 5),  // "value"
        QT_MOC_LITERAL(169, 6),  // "xValue"
        QT_MOC_LITERAL(176, 6),  // "yValue"
        QT_MOC_LITERAL(183, 12)   // "sourceString"
    },
    "ImageGauge",
    "imagePrefixChanged",
    "",
    "minValueChanged",
    "maxValueChanged",
    "numImagesChanged",
    "valueChanged",
    "xValueChanged",
    "yValueChanged",
    "sourceStringChanged",
    "imagePrefix",
    "numImages",
    "value",
    "xValue",
    "yValue",
    "sourceString"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSImageGaugeENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       6,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    7 /* Public */,
       3,    0,   63,    2, 0x06,    8 /* Public */,
       4,    0,   64,    2, 0x06,    9 /* Public */,
       5,    0,   65,    2, 0x06,   10 /* Public */,
       6,    0,   66,    2, 0x06,   11 /* Public */,
       7,    0,   67,    2, 0x06,   12 /* Public */,
       8,    0,   68,    2, 0x06,   13 /* Public */,
       9,    0,   69,    2, 0x06,   14 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00015103, uint(0), 0,
      11, QMetaType::Int, 0x00015103, uint(3), 0,
      12, QMetaType::Int, 0x00015103, uint(4), 0,
      13, QMetaType::Int, 0x00015103, uint(5), 0,
      14, QMetaType::Int, 0x00015103, uint(6), 0,
      15, QMetaType::QString, 0x00015103, uint(7), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject ImageGauge::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSImageGaugeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSImageGaugeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSImageGaugeENDCLASS_t,
        // property 'imagePrefix'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'numImages'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'value'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'xValue'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'yValue'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'sourceString'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ImageGauge, std::true_type>,
        // method 'imagePrefixChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'minValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'maxValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'numImagesChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'xValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'yValueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sourceStringChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ImageGauge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageGauge *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->imagePrefixChanged(); break;
        case 1: _t->minValueChanged(); break;
        case 2: _t->maxValueChanged(); break;
        case 3: _t->numImagesChanged(); break;
        case 4: _t->valueChanged(); break;
        case 5: _t->xValueChanged(); break;
        case 6: _t->yValueChanged(); break;
        case 7: _t->sourceStringChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::imagePrefixChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::minValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::maxValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::numImagesChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::valueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::xValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::yValueChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ImageGauge::*)();
            if (_t _q_method = &ImageGauge::sourceStringChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ImageGauge *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->imagePrefix(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->numImages(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->value(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->xValue(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->yValue(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->sourceString(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ImageGauge *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setImagePrefix(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setNumImages(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setValue(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setXValue(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setYValue(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setSourceString(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_a;
}

const QMetaObject *ImageGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSImageGaugeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int ImageGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ImageGauge::imagePrefixChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ImageGauge::minValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ImageGauge::maxValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ImageGauge::numImagesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ImageGauge::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ImageGauge::xValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ImageGauge::yValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ImageGauge::sourceStringChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
