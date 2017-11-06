#include "tabbarmodel.h"
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

TabBarModel::TabBarModel(QObject *parent) : QAbstractListModel(parent) {
    appendTab("Time", "qrc:/icon/chart-areaspline.svg");
    appendTab("Freq", "qrc:/icon/chart-bar.svg");
    appendTab("Locator", "qrc:/icon/map-marker-radius.svg");
    appendTab("Beacons", "qrc:/icon/access-point.svg", 1);
}

int TabBarModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _tabBarItems.size();
}

QHash<int, QByteArray> TabBarModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[CounterRole] = "counter";
    return roles;
}

QVariant TabBarModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    TabBarItem* item = _tabBarItems.at(row);
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

void TabBarModel::appendTab(const QString &name, const QString &icon, int counter) {
    TabBarItem* item = new TabBarItem(this);
    item->setName(name);
    item->setIcon(icon);
    item->setCounter(counter);
    _tabBarItems.append(item);
}
