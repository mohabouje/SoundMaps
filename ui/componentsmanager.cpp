#include "componentsmanager.h"
#include "models/tabbarmodel.h"
#include "models/drawermodel.h"
#include "chart/circularbufferseries.h"

#include <QSharedData>
#include <QQmlEngine>

#include <ui/models/beaconlistmodel.h>

class ComponentsManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(ComponentsManagerPrivate)
    Q_DECLARE_PUBLIC(ComponentsManager)
public:
    ComponentsManagerPrivate(ComponentsManager* parent) :
        q_ptr(parent),
        drawerModel(new DrawerModel(parent)),
        tabBarModel(new TabBarModel(parent)),
        beaconListModel(new BeaconListModel(parent))
    {

        drawerModel->appendTab("Data Base", "qrc:/icon/database.svg");
        drawerModel->appendTab("Help", "qrc:/icon/help-circle.svg");
        drawerModel->appendTab("About", "qrc:/icon/contact-mail.svg");


        tabBarModel->appendTab("Time", "qrc:/icon/chart-areaspline.svg");
        tabBarModel->appendTab("Freq", "qrc:/icon/chart-bar.svg");
        tabBarModel->appendTab("Locator", "qrc:/icon/map-marker-radius.svg");
        tabBarModel->appendTab("Beacons", "qrc:/icon/access-point.svg", 1);


    }
    ~ComponentsManagerPrivate(){}

    void setDrawerModel(DrawerModel* tmp) {
        Q_Q(ComponentsManager);
        if (tmp != drawerModel) {
            drawerModel = tmp;
            emit q->drawerModelChanged(drawerModel);
        }
    }

    void setTabBarModel(TabBarModel* tmp) {
        Q_Q(ComponentsManager);
        if (tmp != tabBarModel) {
            tabBarModel = tmp;
            emit q->tabBarModelChanged(tabBarModel);
        }
    }

    ComponentsManager* const q_ptr;
    ComponentsManager::RefreshRate rs{ComponentsManager::Low};
    DrawerModel*             drawerModel{nullptr};
    TabBarModel*             tabBarModel{nullptr};
    BeaconListModel* beaconListModel{nullptr};
};

ComponentsManager::ComponentsManager(QObject *parent) :
    QObject(parent),
    d_ptr(new ComponentsManagerPrivate(this))
{
    qmlRegisterType<TabBarModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "DrawerModel");
    qmlRegisterType<BeaconListModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "BeaconListModel");
    qmlRegisterType<CircularBufferSeries>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "CircularBufferSeries");
}

QObject *ComponentsManager::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(ComponentsManager);
}

ComponentsManager::~ComponentsManager()
{
    delete d_ptr;
}

DrawerModel *ComponentsManager::drawerModel() {
    Q_D(ComponentsManager);
    return d->drawerModel;
}

TabBarModel *ComponentsManager::tabBarModel() {
    Q_D(ComponentsManager);
    return d->tabBarModel;
}

void ComponentsManager::setDrawerModel(DrawerModel * drawerModel) {
    Q_D(ComponentsManager);
    d->setDrawerModel(drawerModel);
}

void ComponentsManager::setTabBarModel(TabBarModel * tabBarModel) {
    Q_D(ComponentsManager);
    d->setTabBarModel(tabBarModel);
}

ComponentsManager::RefreshRate ComponentsManager::refreshRate() const {
    Q_D(const ComponentsManager);
    return d->rs;
}

void ComponentsManager::setRefreshRate(ComponentsManager::RefreshRate refresh) {
    Q_D(ComponentsManager);
    if (refresh != d->rs) {
        d->rs = refresh;
        emit refreshRateChanged(d->rs);
    }
}

BeaconListModel *ComponentsManager::beaconListModel() const {
    Q_D(const ComponentsManager);
    return d->beaconListModel;
}

void ComponentsManager::setBeaconListModel(BeaconListModel *tmp) {
    Q_D(ComponentsManager);
    if (tmp != d->beaconListModel) {
        d->beaconListModel = tmp;
        emit beaconListModelChanged(d->beaconListModel);
    }
}

