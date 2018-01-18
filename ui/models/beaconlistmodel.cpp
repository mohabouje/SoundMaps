#include "beaconlistmodel.h"
#include "lps/qenvironement.h"
BeaconListModel::BeaconListModel(QObject *parent) :
    QAbstractListModel (parent)
{
}

void BeaconListModel::setEnvironement(QEnvironement *environement) {
    BeaconListModel::environement = environement;
}

QHash<int, QByteArray> BeaconListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[UuidRole] = "uuid";
    roles[NameRole] = "name";
    roles[SnrRole] = "snr";
    roles[StateRole] = "state";
    roles[PositionRole] = "position";
    return roles;
}

int BeaconListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return environement->beaconsCount();
}

QVariant BeaconListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    QBeacon_ptr beacon = environement->beaconAt(row);
    switch (role) {
    case IdRole:
        return QVariant::fromValue<quint32>(beacon->id());
    case UuidRole:
        return QVariant::fromValue<QUuid>(beacon->uuid());
    case NameRole:
        return QVariant::fromValue<QString>(beacon->name());
    case SnrRole:
        return beacon->snr();
    case StateRole:
        return beacon->state();
    case PositionRole:
        return QVariant::fromValue<QVector3D>(beacon->position());
    default:
        return QVariant();
    }


}


