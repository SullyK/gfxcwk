/****************************************************************************
** Meta object code from reading C++ file 'CourseworkWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../CourseworkWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CourseworkWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CourseworkWidget_t {
    QByteArrayData data[12];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CourseworkWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CourseworkWidget_t qt_meta_stringdata_CourseworkWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CourseworkWidget"
QT_MOC_LITERAL(1, 17, 11), // "updateAngle"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "rotateAround"
QT_MOC_LITERAL(4, 43, 10), // "moveUpDown"
QT_MOC_LITERAL(5, 54, 6), // "zoomIn"
QT_MOC_LITERAL(6, 61, 12), // "panLeftRight"
QT_MOC_LITERAL(7, 74, 9), // "speedStop"
QT_MOC_LITERAL(8, 84, 8), // "speedOne"
QT_MOC_LITERAL(9, 93, 8), // "speedTwo"
QT_MOC_LITERAL(10, 102, 10), // "speedThree"
QT_MOC_LITERAL(11, 113, 15) // "disableLighting"

    },
    "CourseworkWidget\0updateAngle\0\0"
    "rotateAround\0moveUpDown\0zoomIn\0"
    "panLeftRight\0speedStop\0speedOne\0"
    "speedTwo\0speedThree\0disableLighting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CourseworkWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x0a /* Public */,
       1,    0,   72,    2, 0x0a /* Public */,
       3,    1,   73,    2, 0x0a /* Public */,
       4,    1,   76,    2, 0x0a /* Public */,
       5,    1,   79,    2, 0x0a /* Public */,
       6,    1,   82,    2, 0x0a /* Public */,
       7,    0,   85,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    0,   88,    2, 0x0a /* Public */,
      11,    0,   89,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CourseworkWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CourseworkWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateAngle(); break;
        case 2: _t->rotateAround((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->moveUpDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->panLeftRight((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->speedStop(); break;
        case 7: _t->speedOne(); break;
        case 8: _t->speedTwo(); break;
        case 9: _t->speedThree(); break;
        case 10: _t->disableLighting(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CourseworkWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QGLWidget::staticMetaObject>(),
    qt_meta_stringdata_CourseworkWidget.data,
    qt_meta_data_CourseworkWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CourseworkWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CourseworkWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CourseworkWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int CourseworkWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
