#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H
#include "config.h"

#include <QObject>
#include <QQmlEngine>

class TabBarModel;
class DrawerModel;
class BeaconListModel;
class ComponentsManagerPrivate;
class ComponentsManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(DrawerModel* drawerModel READ drawerModel WRITE setDrawerModel NOTIFY drawerModelChanged)
    Q_PROPERTY(TabBarModel* tabBarModel READ tabBarModel WRITE setTabBarModel NOTIFY tabBarModelChanged)
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
    Q_PROPERTY(BeaconListModel* beaconListModel READ beaconListModel WRITE setBeaconListModel NOTIFY beaconListModelChanged)
public:
    explicit ComponentsManager(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    enum RefreshRate { Low = 100, Medium = 50, Hight = 20};
    Q_ENUM(RefreshRate)

    virtual ~ComponentsManager();
    DrawerModel*    drawerModel();
    TabBarModel*    tabBarModel();
    RefreshRate refreshRate() const;
    BeaconListModel *beaconListModel() const;

signals:
    void drawerModelChanged(DrawerModel*);
    void tabBarModelChanged(TabBarModel*);
    void beaconListModelChanged(BeaconListModel*);
    void refreshRateChanged(RefreshRate);
public slots:
    void setDrawerModel(DrawerModel*);
    void setTabBarModel(TabBarModel*);
    void setRefreshRate(RefreshRate);
    void setBeaconListModel(BeaconListModel*);
private:
    Q_DECLARE_PRIVATE(ComponentsManager)
    Q_DISABLE_COPY(ComponentsManager)
    SM_DECL_SINGLETON(ComponentsManager)
    ComponentsManagerPrivate*   d_ptr;
};

#endif // COMPONENTSMANAGER_H
