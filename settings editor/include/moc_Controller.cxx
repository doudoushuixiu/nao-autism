/****************************************************************************
** Meta object code from reading C++ file 'Controller.h'
**
** Created: Fri Aug 9 10:57:03 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Controller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controller[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,
      50,   11,   11,   11, 0x0a,
      68,   12,   11,   11, 0x0a,
     110,   99,   11,   11, 0x0a,
     160,   99,   11,   11, 0x0a,
     212,   99,   11,   11, 0x0a,
     277,  264,   11,   11, 0x0a,
     335,  264,   11,   11, 0x0a,
     395,  264,   11,   11, 0x0a,
     459,  455,   11,   11, 0x0a,
     500,  455,   11,   11, 0x0a,
     543,  455,   11,   11, 0x0a,
     591,  586,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0location\0onOpenRequested(std::string)\0"
    "onSaveRequested()\0onSaveAsRequested(std::string)\0"
    "key,phrase\0onGeneralPhraseCreated(std::string&,std::string&)\0"
    "onGuessGamePhraseCreated(std::string&,std::string&)\0"
    "onMimicGamePhraseCreated(std::string&,std::string&)\0"
    "key,behavior\0"
    "onGeneralPhraseBehaviorCreated(std::string&,std::string&)\0"
    "onGuessGamePhraseBehaviorCreated(std::string&,std::string&)\0"
    "onMimicGamePhraseBehaviorCreated(std::string&,std::string&)\0"
    "key\0onRequestGeneralPhraseGroup(std::string)\0"
    "onRequestGuessGamePhraseGroup(std::string)\0"
    "onRequestMimicGamePhraseGroup(std::string)\0"
    "name\0onRequestGameBehaviors(std::string)\0"
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Controller *_t = static_cast<Controller *>(_o);
        switch (_id) {
        case 0: _t->onOpenRequested((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 1: _t->onSaveRequested(); break;
        case 2: _t->onSaveAsRequested((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 3: _t->onGeneralPhraseCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 4: _t->onGuessGamePhraseCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 5: _t->onMimicGamePhraseCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 6: _t->onGeneralPhraseBehaviorCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 7: _t->onGuessGamePhraseBehaviorCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 8: _t->onMimicGamePhraseBehaviorCreated((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 9: _t->onRequestGeneralPhraseGroup((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 10: _t->onRequestGuessGamePhraseGroup((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 11: _t->onRequestMimicGamePhraseGroup((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 12: _t->onRequestGameBehaviors((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Controller::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Controller::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controller,
      qt_meta_data_Controller, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controller::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controller))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE