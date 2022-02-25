/****************************************************************************
** Meta object code from reading C++ file 'aux_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../press_v4/aux_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aux_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_aux_thread_t {
    QByteArrayData data[33];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_aux_thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_aux_thread_t qt_meta_stringdata_aux_thread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "aux_thread"
QT_MOC_LITERAL(1, 11, 13), // "cohen_coon_kp"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "cohen_coon_ki"
QT_MOC_LITERAL(4, 40, 13), // "cohen_coon_kd"
QT_MOC_LITERAL(5, 54, 17), // "let_step_response"
QT_MOC_LITERAL(6, 72, 15), // "read_parameters"
QT_MOC_LITERAL(7, 88, 27), // "IIR_Filter_double_pace_rate"
QT_MOC_LITERAL(8, 116, 7), // "double*"
QT_MOC_LITERAL(9, 124, 10), // "raw_signal"
QT_MOC_LITERAL(10, 135, 22), // "IIR_Filter_double_load"
QT_MOC_LITERAL(11, 158, 6), // "float*"
QT_MOC_LITERAL(12, 165, 16), // "discrete_PID_dac"
QT_MOC_LITERAL(13, 182, 15), // "read_data_order"
QT_MOC_LITERAL(14, 198, 2), // "u8"
QT_MOC_LITERAL(15, 201, 10), // "base_array"
QT_MOC_LITERAL(16, 212, 11), // "const char*"
QT_MOC_LITERAL(17, 224, 5), // "array"
QT_MOC_LITERAL(18, 230, 11), // "first_index"
QT_MOC_LITERAL(19, 242, 10), // "last_index"
QT_MOC_LITERAL(20, 253, 15), // "send_data_order"
QT_MOC_LITERAL(21, 269, 5), // "char*"
QT_MOC_LITERAL(22, 275, 7), // "crc_chk"
QT_MOC_LITERAL(23, 283, 3), // "u32"
QT_MOC_LITERAL(24, 287, 3), // "u8*"
QT_MOC_LITERAL(25, 291, 4), // "data"
QT_MOC_LITERAL(26, 296, 6), // "length"
QT_MOC_LITERAL(27, 303, 17), // "serial_port_setup"
QT_MOC_LITERAL(28, 321, 21), // "fuzpid_thread_handler"
QT_MOC_LITERAL(29, 343, 11), // "always_send"
QT_MOC_LITERAL(30, 355, 3), // "EOL"
QT_MOC_LITERAL(31, 359, 1), // "i"
QT_MOC_LITERAL(32, 361, 13) // "step_response"

    },
    "aux_thread\0cohen_coon_kp\0\0cohen_coon_ki\0"
    "cohen_coon_kd\0let_step_response\0"
    "read_parameters\0IIR_Filter_double_pace_rate\0"
    "double*\0raw_signal\0IIR_Filter_double_load\0"
    "float*\0discrete_PID_dac\0read_data_order\0"
    "u8\0base_array\0const char*\0array\0"
    "first_index\0last_index\0send_data_order\0"
    "char*\0crc_chk\0u32\0u8*\0data\0length\0"
    "serial_port_setup\0fuzpid_thread_handler\0"
    "always_send\0EOL\0i\0step_response"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_aux_thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       3,    1,   97,    2, 0x06 /* Public */,
       4,    1,  100,    2, 0x06 /* Public */,
       5,    0,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  104,    2, 0x0a /* Public */,
       7,    1,  105,    2, 0x0a /* Public */,
      10,    1,  108,    2, 0x0a /* Public */,
      12,    0,  111,    2, 0x0a /* Public */,
      13,    4,  112,    2, 0x08 /* Private */,
      20,    4,  121,    2, 0x08 /* Private */,
      22,    2,  130,    2, 0x08 /* Private */,
      27,    0,  135,    2, 0x08 /* Private */,
      28,    0,  136,    2, 0x08 /* Private */,
      29,    0,  137,    2, 0x08 /* Private */,
      30,    2,  138,    2, 0x08 /* Private */,
      32,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Double, 0x80000000 | 8,    9,
    QMetaType::Float, 0x80000000 | 11,    9,
    QMetaType::Double,
    0x80000000 | 14, QMetaType::QByteArray, 0x80000000 | 16, 0x80000000 | 14, 0x80000000 | 14,   15,   17,   18,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 16, 0x80000000 | 14, 0x80000000 | 14,   15,   17,   18,   19,
    0x80000000 | 23, 0x80000000 | 24, 0x80000000 | 14,   25,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 14,   15,   31,
    QMetaType::Void,

       0        // eod
};

void aux_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        aux_thread *_t = static_cast<aux_thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cohen_coon_kp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->cohen_coon_ki((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->cohen_coon_kd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->let_step_response(); break;
        case 4: _t->read_parameters(); break;
        case 5: { double _r = _t->IIR_Filter_double_pace_rate((*reinterpret_cast< double*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { float _r = _t->IIR_Filter_double_load((*reinterpret_cast< float*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 7: { double _r = _t->discrete_PID_dac();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 8: { u8 _r = _t->read_data_order((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< u8(*)>(_a[3])),(*reinterpret_cast< u8(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< u8*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->send_data_order((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< u8(*)>(_a[3])),(*reinterpret_cast< u8(*)>(_a[4]))); break;
        case 10: { u32 _r = _t->crc_chk((*reinterpret_cast< u8*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< u32*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->serial_port_setup(); break;
        case 12: _t->fuzpid_thread_handler(); break;
        case 13: _t->always_send(); break;
        case 14: _t->EOL((*reinterpret_cast< char*(*)>(_a[1])),(*reinterpret_cast< u8(*)>(_a[2]))); break;
        case 15: _t->step_response(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (aux_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&aux_thread::cohen_coon_kp)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (aux_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&aux_thread::cohen_coon_ki)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (aux_thread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&aux_thread::cohen_coon_kd)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (aux_thread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&aux_thread::let_step_response)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject aux_thread::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_aux_thread.data,
      qt_meta_data_aux_thread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *aux_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *aux_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_aux_thread.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int aux_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void aux_thread::cohen_coon_kp(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void aux_thread::cohen_coon_ki(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void aux_thread::cohen_coon_kd(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void aux_thread::let_step_response()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
