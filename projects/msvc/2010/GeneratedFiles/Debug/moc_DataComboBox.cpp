/****************************************************************************
** Meta object code from reading C++ file 'DataComboBox.h'
**
** Created: Fri 20. Feb 12:36:39 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phantom/qt/qt.h"
#include "..\..\..\..\..\phantom\qt\DataComboBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataComboBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_phantom__qt__DataComboBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      34,   27,   26,   26, 0x05,
      62,   27,   26,   26, 0x05,

 // slots: signature, parameters, type, tag, flags
     102,   96,   26,   26, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_phantom__qt__DataComboBox[] = {
    "phantom::qt::DataComboBox\0\0a_Data\0"
    "dataSelected(phantom::data)\0"
    "dataSelectedCasted(phantom::data)\0"
    "index\0currentDataIndexChanged(int)\0"
};

void phantom::qt::DataComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataComboBox *_t = static_cast<DataComboBox *>(_o);
        switch (_id) {
        case 0: _t->dataSelected((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 1: _t->dataSelectedCasted((*reinterpret_cast< const phantom::data(*)>(_a[1]))); break;
        case 2: _t->currentDataIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData phantom::qt::DataComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject phantom::qt::DataComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_phantom__qt__DataComboBox,
      qt_meta_data_phantom__qt__DataComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &phantom::qt::DataComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *phantom::qt::DataComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *phantom::qt::DataComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_phantom__qt__DataComboBox))
        return static_cast<void*>(const_cast< DataComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int phantom::qt::DataComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void phantom::qt::DataComboBox::dataSelected(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void phantom::qt::DataComboBox::dataSelectedCasted(const phantom::data & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
