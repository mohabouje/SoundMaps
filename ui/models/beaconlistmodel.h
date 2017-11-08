#ifndef BEACONLISTMODEL_H
#define BEACONLISTMODEL_H

#include <QAbstractItemModel>
class QEnvironement;
class BeaconListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BeaconListModel(QObject *parent = nullptr);
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    enum BeaconListRoles { IdRole = Qt::UserRole + 1, UuidRole, NameRole, SnrRole, StateRole, PositionRole };
    QEnvironement* environement;
};

#endif // BEACONLISTMODEL_H
