#include "drawermodel.h"

void DrawerItem::setName(const QString &name) {
    _name = name;
}

void DrawerItem::setIcon(const QString &icon) {
    _icon = icon;
}

void DrawerItem::setCounter(int counter) {
    _counter = counter;
}

DrawerModel::DrawerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void DrawerModel::appendTab(const QString &name, const QString &icon, int counter) {
    DrawerItem* item = new DrawerItem(this);
    item->setName(name);
    item->setIcon(icon);
    item->setCounter(counter);
    _drawerItems.append(item);
}


int DrawerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return _drawerItems.size();
}

QHash<int, QByteArray> DrawerModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[CounterRole] = "counter";
    return roles;
}

QVariant DrawerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    DrawerItem* item = _drawerItems.at(row);
    switch (role) {
    case NameRole:
        return QVariant::fromValue<QString>(item->name());
    case IconRole:
        return QVariant::fromValue<QString>(item->icon());
    case CounterRole:
        return QVariant::fromValue<int>(item->counter());
    default:
        return QVariant();
    }
}