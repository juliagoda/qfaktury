/****************************************************************************
** Meta object code from reading C++ file 'GoodsGrossList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/GoodsGrossList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GoodsGrossList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GoodsGrossList_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GoodsGrossList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GoodsGrossList_t qt_meta_stringdata_GoodsGrossList = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GoodsGrossList"
QT_MOC_LITERAL(1, 15, 7), // "calcNet"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "doAccept"
QT_MOC_LITERAL(4, 33, 17) // "getPriceOfCurrent"

    },
    "GoodsGrossList\0calcNet\0\0doAccept\0"
    "getPriceOfCurrent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GoodsGrossList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,

       0        // eod
};

void GoodsGrossList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GoodsGrossList *_t = static_cast<GoodsGrossList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->calcNet(); break;
        case 1: _t->doAccept(); break;
        case 2: { QString _r = _t->getPriceOfCurrent();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject GoodsGrossList::staticMetaObject = {
    { &GoodsList::staticMetaObject, qt_meta_stringdata_GoodsGrossList.data,
      qt_meta_data_GoodsGrossList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GoodsGrossList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GoodsGrossList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GoodsGrossList.stringdata0))
        return static_cast<void*>(const_cast< GoodsGrossList*>(this));
    return GoodsList::qt_metacast(_clname);
}

int GoodsGrossList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GoodsList::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
