#ifndef TABBARITEM_H
#define TABBARITEM_H

#include <QObject>
class TabBarItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(int counter READ counter WRITE setCounter NOTIFY counterChanged)
public:
    explicit TabBarItem(QObject* parent = Q_NULLPTR);
    TabBarItem(const QString &name, const QString &icon, int counter, QObject *parent);
    inline QString name() const { return _name; }
    inline QString icon() const { return _icon; }
    inline int counter() const {  return _counter; }
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
#endif // TABBARITEM_H
