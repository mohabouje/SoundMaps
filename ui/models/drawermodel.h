#ifndef DRAWERMODEL_H
#define DRAWERMODEL_H

#include "draweritem.h"
#include <QAbstractItemModel>
class DrawerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DrawerModel(QObject *parent = nullptr); 
public slots:
    void append(DrawerItem* item);
    void append(const QString& name, const QString& icon, int counter = 0);
protected:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
    enum TabBarRoles { NameRole = Qt::UserRole + 1, IconRole, CounterRole };
    QList<DrawerItem*>  _drawerItems;
};

#endif // DRAWERMODEL_H
