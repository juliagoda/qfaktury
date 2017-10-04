/****************************************************************************
** Meta object code from reading C++ file 'Invoice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Invoice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Invoice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Invoice_t {
    QByteArrayData data[26];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Invoice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Invoice_t qt_meta_stringdata_Invoice = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Invoice"
QT_MOC_LITERAL(1, 8, 8), // "addGoods"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 14), // "discountChange"
QT_MOC_LITERAL(4, 33, 12), // "backBtnClick"
QT_MOC_LITERAL(5, 46, 7), // "canQuit"
QT_MOC_LITERAL(6, 54, 11), // "saveInvoice"
QT_MOC_LITERAL(7, 66, 11), // "makeInvoice"
QT_MOC_LITERAL(8, 78, 14), // "payTextChanged"
QT_MOC_LITERAL(9, 93, 7), // "someStr"
QT_MOC_LITERAL(10, 101, 19), // "discountConstChange"
QT_MOC_LITERAL(11, 121, 11), // "getCustomer"
QT_MOC_LITERAL(12, 133, 8), // "delGoods"
QT_MOC_LITERAL(13, 142, 9), // "editGoods"
QT_MOC_LITERAL(14, 152, 14), // "tableActivated"
QT_MOC_LITERAL(15, 167, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(16, 185, 4), // "item"
QT_MOC_LITERAL(17, 190, 11), // "textChanged"
QT_MOC_LITERAL(18, 202, 11), // "dateChanged"
QT_MOC_LITERAL(19, 214, 8), // "someDate"
QT_MOC_LITERAL(20, 223, 9), // "printSlot"
QT_MOC_LITERAL(21, 233, 9), // "QPrinter*"
QT_MOC_LITERAL(22, 243, 10), // "buyerClick"
QT_MOC_LITERAL(23, 254, 12), // "tellFinished"
QT_MOC_LITERAL(24, 267, 13), // "httpReadyRead"
QT_MOC_LITERAL(25, 281, 15) // "rateDateChanged"

    },
    "Invoice\0addGoods\0\0discountChange\0"
    "backBtnClick\0canQuit\0saveInvoice\0"
    "makeInvoice\0payTextChanged\0someStr\0"
    "discountConstChange\0getCustomer\0"
    "delGoods\0editGoods\0tableActivated\0"
    "QTableWidgetItem*\0item\0textChanged\0"
    "dateChanged\0someDate\0printSlot\0QPrinter*\0"
    "buyerClick\0tellFinished\0httpReadyRead\0"
    "rateDateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Invoice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x0a /* Public */,
       3,    0,  110,    2, 0x0a /* Public */,
       4,    0,  111,    2, 0x0a /* Public */,
       5,    0,  112,    2, 0x0a /* Public */,
       6,    0,  113,    2, 0x0a /* Public */,
       7,    0,  114,    2, 0x0a /* Public */,
       8,    1,  115,    2, 0x0a /* Public */,
      10,    0,  118,    2, 0x0a /* Public */,
      11,    0,  119,    2, 0x0a /* Public */,
      12,    0,  120,    2, 0x0a /* Public */,
      13,    0,  121,    2, 0x0a /* Public */,
      14,    1,  122,    2, 0x0a /* Public */,
      17,    1,  125,    2, 0x0a /* Public */,
      18,    1,  128,    2, 0x0a /* Public */,
      20,    1,  131,    2, 0x0a /* Public */,
      22,    0,  134,    2, 0x0a /* Public */,
      23,    0,  135,    2, 0x0a /* Public */,
      24,    0,  136,    2, 0x0a /* Public */,
      25,    1,  137,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QDate,   19,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void Invoice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Invoice *_t = static_cast<Invoice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addGoods(); break;
        case 1: _t->discountChange(); break;
        case 2: _t->backBtnClick(); break;
        case 3: _t->canQuit(); break;
        case 4: { bool _r = _t->saveInvoice();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->makeInvoice(); break;
        case 6: _t->payTextChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->discountConstChange(); break;
        case 8: _t->getCustomer(); break;
        case 9: _t->delGoods(); break;
        case 10: _t->editGoods(); break;
        case 11: _t->tableActivated((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 12: _t->textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->dateChanged((*reinterpret_cast< QDate(*)>(_a[1]))); break;
        case 14: _t->printSlot((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 15: _t->buyerClick(); break;
        case 16: _t->tellFinished(); break;
        case 17: _t->httpReadyRead(); break;
        case 18: _t->rateDateChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Invoice::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Invoice.data,
      qt_meta_data_Invoice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Invoice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Invoice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Invoice.stringdata0))
        return static_cast<void*>(const_cast< Invoice*>(this));
    if (!strcmp(_clname, "Ui::Invoice"))
        return static_cast< Ui::Invoice*>(const_cast< Invoice*>(this));
    return QDialog::qt_metacast(_clname);
}

int Invoice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
