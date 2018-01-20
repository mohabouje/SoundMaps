#ifndef DRAWERITEM_H
#define DRAWERITEM_H

#include <QObject>
class DrawerItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
public:
    explicit DrawerItem(QObject* parent = Q_NULLPTR);
    DrawerItem(const QString& name, const QString& icon, int counter, QObject* parent = Q_NULLPTR);
    inline QString name() const { return _name; }
    inline QString icon() const { return _icon; }
    inline int counter() const { return _counter; }
public slots:
    void setName(const QString& name);
    void setIcon(const QString& icon);
    void setCounter(int counter);
signals:
    void nameChanged(QString);
    void iconChanged(QString);
    void counterChanged(int);

private:
    QString _name;
    QString _icon;
    int _counter;
};

#endif // DRAWERITEM_H
