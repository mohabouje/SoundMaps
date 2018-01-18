#include "draweritem.h"

DrawerItem::DrawerItem(QObject *parent) :
    QObject(parent) {

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
