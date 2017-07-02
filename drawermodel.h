#ifndef DRAWERMODEL_H
#define DRAWERMODEL_H

#include <QAbstractItemModel>

class DrawerItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
public:
    explicit DrawerItem(QObject* parent = Q_NULLPTR) : QObject(parent) {}
    inline QString name() const { return _name; }
    inline QString icon() const { return _icon; }
    inline int counter() const { return _counter; }
    void setName(const QString &name);
    void setIcon(const QString &icon);
    void setCounter(int counter);
signals:
    void nameChanged();
    void iconChanged();
    void counterChanged();
private:
    QString _name;
    QString _icon;
    int     _counter;
};

class DrawerModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DrawerModel(QObject *parent = nullptr);
    enum TabBarRoles { NameRole = Qt::UserRole + 1, IconRole, CounterRole };
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
private:
    QList<DrawerItem*>  _drawerItems;
};

#endif // DRAWERMODEL_H
