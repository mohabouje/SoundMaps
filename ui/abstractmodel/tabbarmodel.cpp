#include "tabbarmodel.h"


TabBarModel::TabBarModel(QObject *parent) : QAbstractListModel(parent) {
}

void TabBarModel::append(TabBarItem * item) {
    sm::append(_tabBarItems, item);

}
void TabBarModel::append(const QString &name, const QString &icon, int counter) {
    sm::append(_tabBarItems, new TabBarItem(name, icon, counter, this));
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


