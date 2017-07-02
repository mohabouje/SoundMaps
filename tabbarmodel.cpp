#include "tabbarmodel.h"
void TabBarItem::setName(const QString &name) {
    if (_name != name) {
        _name = name;
    }
}

void TabBarItem::setIcon(const QString &icon) {
    if (_icon != icon) {
        _icon = icon;
    }
}

void TabBarItem::setCounter(int counter) {
    if (_counter != counter) {
        _counter = counter;
    }
}

TabBarModel::TabBarModel(QObject *parent) : QAbstractListModel(parent) {
    appendTab("Time", "qrc:/icon/chart-areaspline.svg");
    appendTab("Freq", "qrc:/icon/chart-bar.svg");
    appendTab("Locator", "qrc:/icon/map-marker-radius.svg");
    appendTab("Settings", "qrc:/icon/settings.svg", 6);
}

QHash<int, QByteArray> TabBarModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconRole] = "icon";
    roles[CounterRole] = "counter";
    return roles;
}

int TabBarModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _tabBarItems.size();
}

QVariant TabBarModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    TabBarItem item = _tabBarItems.at(row);
    switch (role) {
    case NameRole:
        return QVariant::fromValue<QString>(item.name());
    case IconRole:
        return QVariant::fromValue<QString>(item.icon());
    case CounterRole:
        return QVariant::fromValue<int>(item.counter());
    default:
        return QVariant();
    }
}

void TabBarModel::appendTab(const TabBarItem &item) {
    _tabBarItems.append(item);
}

void TabBarModel::appendTab(const QString &name, const QString &icon, int counter) {
    TabBarItem item;
    item.setName(name);
    item.setIcon(icon);
    item.setCounter(counter);
    _tabBarItems.append(item);
}
