/****************************************************************************
** Meta object code from reading C++ file 'QBlockDiagramNodeSlot.h'
**
** Created: Mon 17. Feb 22:23:57 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/QBlockDiagramNodeSlot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBlockDiagramNodeSlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QBlockDiagramNodeSlot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   23,   22,   22, 0x05,
      60,   49,   22,   22, 0x05,
     100,   49,   22,   22, 0x05,
     160,  152,   22,   22, 0x05,
     194,  152,   22,   22, 0x05,
     231,  152,   22,   22, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QBlockDiagramNodeSlot[] = {
    "QBlockDiagramNodeSlot\0\0text\0"
    "textChanged(QString)\0a_pLinkEnd\0"
    "linkEndConnected(QBlockDiagramLinkEnd*)\0"
    "linkEndAboutToBeDisconnected(QBlockDiagramLinkEnd*)\0"
    "a_pSlot\0connected(QBlockDiagramNodeSlot*)\0"
    "disconnected(QBlockDiagramNodeSlot*)\0"
    "aboutToBeDisconnected(QBlockDiagramNodeSlot*)\0"
};

void QBlockDiagramNodeSlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QBlockDiagramNodeSlot *_t = static_cast<QBlockDiagramNodeSlot *>(_o);
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->linkEndConnected((*reinterpret_cast< QBlockDiagramLinkEnd*(*)>(_a[1]))); break;
        case 2: _t->linkEndAboutToBeDisconnected((*reinterpret_cast< QBlockDiagramLinkEnd*(*)>(_a[1]))); break;
        case 3: _t->connected((*reinterpret_cast< QBlockDiagramNodeSlot*(*)>(_a[1]))); break;
        case 4: _t->disconnected((*reinterpret_cast< QBlockDiagramNodeSlot*(*)>(_a[1]))); break;
        case 5: _t->aboutToBeDisconnected((*reinterpret_cast< QBlockDiagramNodeSlot*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QBlockDiagramNodeSlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QBlockDiagramNodeSlot::staticMetaObject = {
    { &QBlockDiagramConnector::staticMetaObject, qt_meta_stringdata_QBlockDiagramNodeSlot,
      qt_meta_data_QBlockDiagramNodeSlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QBlockDiagramNodeSlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QBlockDiagramNodeSlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QBlockDiagramNodeSlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QBlockDiagramNodeSlot))
        return static_cast<void*>(const_cast< QBlockDiagramNodeSlot*>(this));
    return QBlockDiagramConnector::qt_metacast(_clname);
}

int QBlockDiagramNodeSlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QBlockDiagramConnector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QBlockDiagramNodeSlot::textChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QBlockDiagramNodeSlot::linkEndConnected(QBlockDiagramLinkEnd * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QBlockDiagramNodeSlot::linkEndAboutToBeDisconnected(QBlockDiagramLinkEnd * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QBlockDiagramNodeSlot::connected(QBlockDiagramNodeSlot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QBlockDiagramNodeSlot::disconnected(QBlockDiagramNodeSlot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QBlockDiagramNodeSlot::aboutToBeDisconnected(QBlockDiagramNodeSlot * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
