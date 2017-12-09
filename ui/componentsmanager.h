#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H
#include "sm_config.h"
#include "models/tabbarmodel.h"
#include "models/drawermodel.h"
#include "models/beaconlistmodel.h"
#include "chart/circularseries.h"
#include "chart/spectrogramseries.h"
#include <QObject>
#include <QQmlEngine>

class ComponentsManagerPrivate;
class ComponentsManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(DrawerModel* drawerModel READ drawerModel WRITE setDrawerModel NOTIFY drawerModelChanged)
    Q_PROPERTY(TabBarModel* tabBarModel READ tabBarModel WRITE setTabBarModel NOTIFY tabBarModelChanged)
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
    Q_PROPERTY(BeaconListModel* beaconListModel READ beaconListModel WRITE setBeaconListModel NOTIFY beaconListModelChanged)
    Q_PROPERTY(CircularSeries* circularSeries READ circularSeries NOTIFY circularSeriesChanged)
    Q_PROPERTY(SpectrogramSeries* spectrogramSeries READ spectrogramSeries NOTIFY spectrogramSeriesChanged)
public:
    explicit ComponentsManager(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    enum RefreshRate { Low = 100, Medium = 50, Hight = 20};
    Q_ENUM(RefreshRate)

    virtual ~ComponentsManager();
    DrawerModel*    drawerModel() const;
    TabBarModel*    tabBarModel() const;
    BeaconListModel *beaconListModel() const;

    SpectrogramSeries* spectrogramSeries() const;
    CircularSeries* circularSeries() const;
    RefreshRate refreshRate() const;

signals:
    void drawerModelChanged(DrawerModel*);
    void tabBarModelChanged(TabBarModel*);
    void beaconListModelChanged(BeaconListModel*);
    void refreshRateChanged(RefreshRate);
    void arraySeriesChanged(ArraySeries*);
    void circularSeriesChanged(CircularSeries*);
    void spectrogramSeriesChanged(SpectrogramSeries*);
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
