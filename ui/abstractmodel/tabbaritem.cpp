#include "tabbaritem.h"
TabBarItem::TabBarItem(QObject *parent) :
    QObject(parent) {

}

TabBarItem::TabBarItem(const QString &name, const QString &icon, int counter, QObject *parent) :
    QObject(parent),
    _name(name),
    _icon(icon),
    _counter(counter)
{

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
