#include "draweritem.h"

DrawerItem::DrawerItem(QObject *parent) :
    QObject(parent) {

}

DrawerItem::DrawerItem(const QString &name, const QString &icon, int counter, QObject *parent) :
    QObject(parent),
    _name(name),
    _icon(icon),
    _counter(counter)
{

}

void DrawerItem::setName(const QString &name) {
    if (_name != name) {
        _name = name;
        emit nameChanged(_name);
    }
}

void DrawerItem::setIcon(const QString &icon) {
    if (_icon != icon) {
        _icon = icon;
        emit iconChanged(icon);
    }
}

void DrawerItem::setCounter(int counter) {
    if (_counter != counter) {
        _counter = counter;
        emit counterChanged(counter);
    }
}
