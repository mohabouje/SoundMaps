#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H

#include <QObject>
class TabBarModel;
class DrawerModel;
class ComponentsManagerPrivate;
class ComponentsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DrawerModel* drawerModel READ drawerModel WRITE setDrawerModel NOTIFY drawerModelChanged)
    Q_PROPERTY(TabBarModel* tabBarModel READ tabBarModel WRITE setTabBarModel NOTIFY tabBarModelChanged)
public:
    explicit ComponentsManager(QObject *parent = nullptr);
    DrawerModel*    drawerModel();
    TabBarModel*    tabBarModel();
signals:
    void drawerModelChanged(DrawerModel*);
    void tabBarModelChanged(TabBarModel*);
public slots:
    void setDrawerModel(DrawerModel*);
    void setTabBarModel(TabBarModel*);
private:
    Q_DECLARE_PRIVATE(ComponentsManager)
    Q_DISABLE_COPY(ComponentsManager)
    ComponentsManagerPrivate*   d_ptr;
};

#endif // COMPONENTSMANAGER_H
