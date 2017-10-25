#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H

#include <QObject>
class TabBarModel;
class DrawerModel;
class ComponentsManagerPrivate;
class ComponentsManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(DrawerModel* drawerModel READ drawerModel WRITE setDrawerModel NOTIFY drawerModelChanged)
    Q_PROPERTY(TabBarModel* tabBarModel READ tabBarModel WRITE setTabBarModel NOTIFY tabBarModelChanged)
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
public:
    explicit ComponentsManager(QObject *parent = nullptr);
    enum RefreshRate { Low = 100, Medium = 50, Hight = 20};
    Q_ENUM(RefreshRate)

    virtual ~ComponentsManager();
    DrawerModel*    drawerModel();
    TabBarModel*    tabBarModel();
    RefreshRate refreshRate() const;
signals:
    void drawerModelChanged(DrawerModel*);
    void tabBarModelChanged(TabBarModel*);
    void refreshRateChanged(RefreshRate);
public slots:
    void setDrawerModel(DrawerModel*);
    void setTabBarModel(TabBarModel*);
    void setRefreshRate(RefreshRate);
private:
    Q_DECLARE_PRIVATE(ComponentsManager)
    Q_DISABLE_COPY(ComponentsManager)
    ComponentsManagerPrivate*   d_ptr;
};

#endif // COMPONENTSMANAGER_H
