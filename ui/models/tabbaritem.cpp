#include "tabbaritem.h"
TabBarItem::TabBarItem(QObject *parent) :
    QObject(parent) {

}

void TabBarItem::setName(const QString &name) {
    if (_name != name) {
        _name = name;
        emit nameChanged();
    }
}

void TabBarItem::setIcon(const QString &icon) {
    if (_icon != icon) {
        _icon = icon;
        emit iconChanged();
    }
}

void TabBarItem::setCounter(int counter) {
    if (_counter != counter) {
        _counter = counter;
        emit counterChanged();
    }
}
