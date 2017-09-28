/****************************************************************************
** Meta object code from reading C++ file 'BuyersList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/BuyersList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BuyersList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BuyersList_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BuyersList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BuyersList_t qt_meta_stringdata_BuyersList = {
    {
QT_MOC_LITERAL(0, 0, 10), // "BuyersList"
QT_MOC_LITERAL(1, 11, 9), // "readBuyer"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "doAccept"
QT_MOC_LITERAL(4, 31, 16), // "comboBox1Changed"
QT_MOC_LITERAL(5, 48, 13), // "updateDetails"
QT_MOC_LITERAL(6, 62, 16) // "QListWidgetItem*"

    },
    "BuyersList\0readBuyer\0\0doAccept\0"
    "comboBox1Changed\0updateDetails\0"
    "QListWidgetItem*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BuyersList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void BuyersList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BuyersList *_t = static_cast<BuyersList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readBuyer(); break;
        case 1: _t->doAccept(); break;
        case 2: _t->comboBox1Changed(); break;
        case 3: _t->updateDetails((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BuyersList::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BuyersList.data,
      qt_meta_data_BuyersList,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BuyersList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BuyersList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BuyersList.stringdata0))
        return static_cast<void*>(const_cast< BuyersList*>(this));
    if (!strcmp(_clname, "Ui::BuyersList"))
        return static_cast< Ui::BuyersList*>(const_cast< BuyersList*>(this));
    return QDialog::qt_metacast(_clname);
}

int BuyersList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
