/****************************************************************************
** Meta object code from reading C++ file 'createframedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../university_git/pr1-2019-8303/Grishin_Konstantin_cw/source/createframedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createframedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CreateFrameDialog_t {
    QByteArrayData data[11];
    char stringdata0[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateFrameDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateFrameDialog_t qt_meta_stringdata_CreateFrameDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CreateFrameDialog"
QT_MOC_LITERAL(1, 18, 16), // "on_apply_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 17), // "on_reject_clicked"
QT_MOC_LITERAL(4, 54, 19), // "on_branches_clicked"
QT_MOC_LITERAL(5, 74, 27), // "on_angle_value_valueChanged"
QT_MOC_LITERAL(6, 102, 5), // "value"
QT_MOC_LITERAL(7, 108, 21), // "on_line_frame_clicked"
QT_MOC_LITERAL(8, 130, 29), // "on_density_value_valueChanged"
QT_MOC_LITERAL(9, 160, 21), // "on_kelt_cross_clicked"
QT_MOC_LITERAL(10, 182, 28) // "on_radius_value_valueChanged"

    },
    "CreateFrameDialog\0on_apply_clicked\0\0"
    "on_reject_clicked\0on_branches_clicked\0"
    "on_angle_value_valueChanged\0value\0"
    "on_line_frame_clicked\0"
    "on_density_value_valueChanged\0"
    "on_kelt_cross_clicked\0"
    "on_radius_value_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateFrameDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    1,   61,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void CreateFrameDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateFrameDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_apply_clicked(); break;
        case 1: _t->on_reject_clicked(); break;
        case 2: _t->on_branches_clicked(); break;
        case 3: _t->on_angle_value_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_line_frame_clicked(); break;
        case 5: _t->on_density_value_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_kelt_cross_clicked(); break;
        case 7: _t->on_radius_value_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CreateFrameDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_CreateFrameDialog.data,
    qt_meta_data_CreateFrameDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CreateFrameDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateFrameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CreateFrameDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int CreateFrameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
