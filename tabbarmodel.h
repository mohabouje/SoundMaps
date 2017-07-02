#ifndef TABBARMODEL_H
#define TABBARMODEL_H

#include "config.h"
#include <QAbstractListModel>
class TabBarItem  {
public:
    inline QString name() const { return _name; }
    inline QString icon() const { return _icon; }
    inline int counter() const {  return _counter; }
    void setName(const QString &name);
    void setIcon(const QString &icon);
    void setCounter(int counter);
private:
    QString _name;
    QString _icon;
    int     _counter;
};


class TabBarModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit TabBarModel(QObject* parent = nullptr);
    Q_INVOKABLE void appendTab(const TabBarItem& item);
    Q_INVOKABLE void appendTab(const QString& name, const QString& icon, int counter = 0);
    enum TabBarRoles { NameRole = Qt::UserRole + 1, IconRole, CounterRole };
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
private:
    QList<TabBarItem>   _tabBarItems;
};
#endif // TABBARMODEL_H
