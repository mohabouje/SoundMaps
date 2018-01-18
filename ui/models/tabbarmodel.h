#ifndef TABBARMODEL_H
#define TABBARMODEL_H

#include "sm_config.h"
#include "tabbaritem.h"
#include <QAbstractListModel>

class TabBarModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit TabBarModel(QObject* parent = Q_NULLPTR);
public slots:
    Q_INVOKABLE void appendTab(TabBarItem* item);
    Q_INVOKABLE void appendTab(const QString& name, const QString& icon, int counter = 0);
protected:
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    enum TabBarRoles { NameRole = Qt::UserRole + 1, IconRole, CounterRole };
    QList<TabBarItem*>   _tabBarItems;
};
#endif // TABBARMODEL_H
