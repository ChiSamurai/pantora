/****************************************************************************
** Meta object code from reading C++ file 'displaywidget.h'
**
** Created: Thu Sep 26 22:19:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widgets/ScanEditWidget/displaywidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'displaywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DisplayWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      28,   14,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      67,   65,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   14,   14,   14, 0x0a,
     100,   14,   14,   14, 0x08,
     112,   14,   14,   14, 0x08,
     126,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DisplayWidget[] = {
    "DisplayWidget\0\0clearMenus()\0"
    "mainModusChanged(int)\0textureSaved()\0"
    "t\0updated(Textur*)\0updateActions()\0"
    "saveImage()\0exportImage()\0print()\0"
};

void DisplayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DisplayWidget *_t = static_cast<DisplayWidget *>(_o);
        switch (_id) {
        case 0: _t->clearMenus(); break;
        case 1: _t->mainModusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->textureSaved(); break;
        case 3: _t->updated((*reinterpret_cast< Textur*(*)>(_a[1]))); break;
        case 4: _t->updateActions(); break;
        case 5: _t->saveImage(); break;
        case 6: _t->exportImage(); break;
        case 7: _t->print(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DisplayWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DisplayWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DisplayWidget,
      qt_meta_data_DisplayWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DisplayWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DisplayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DisplayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayWidget))
        return static_cast<void*>(const_cast< DisplayWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int DisplayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DisplayWidget::clearMenus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DisplayWidget::mainModusChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DisplayWidget::textureSaved()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DisplayWidget::updated(Textur * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
