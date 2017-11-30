#include "componentsmanager.h"

#include <QSharedData>
class ComponentsManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(ComponentsManagerPrivate)
    Q_DECLARE_PUBLIC(ComponentsManager)
public:
    ComponentsManagerPrivate(ComponentsManager* parent) :
        q_ptr(parent),
        drawerModel(new DrawerModel(parent)),
        tabBarModel(new TabBarModel(parent)),
        beaconListModel(new BeaconListModel(parent)),
        arraySeries(new ArraySeries(parent)),
        circularSeries(new CircularSeries(parent))
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

    ComponentsManager* const q_ptr;
    ComponentsManager::RefreshRate rs{ComponentsManager::Low};
    DrawerModel*                drawerModel{nullptr};
    TabBarModel*                tabBarModel{nullptr};
    BeaconListModel*            beaconListModel{nullptr};
    ArraySeries*                arraySeries{nullptr};
    CircularSeries*             circularSeries{nullptr};
};

ComponentsManager::ComponentsManager(QObject *parent) :
    QObject(parent),
    d_ptr(new ComponentsManagerPrivate(this))
{
    qmlRegisterType<TabBarModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "DrawerModel");
    qmlRegisterType<BeaconListModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "BeaconListModel");
    qmlRegisterType<ArraySeries>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ArraySeries");
    qmlRegisterType<CircularSeries>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "CircularSeries");
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

DrawerModel *ComponentsManager::drawerModel() const {
    Q_D(const ComponentsManager);
    return d->drawerModel;
}

TabBarModel *ComponentsManager::tabBarModel() const {
    Q_D(const ComponentsManager);
    return d->tabBarModel;
}

void ComponentsManager::setDrawerModel(DrawerModel * tmp) {
    Q_D(ComponentsManager);
    if (tmp != d->drawerModel) {
        d->drawerModel = tmp;
        emit drawerModelChanged(d->drawerModel);
    }
}

void ComponentsManager::setTabBarModel(TabBarModel * tmp) {
    Q_D(ComponentsManager);
    if (tmp != d->tabBarModel) {
        d->tabBarModel = tmp;
        emit tabBarModelChanged(d->tabBarModel);
    }
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

ArraySeries *ComponentsManager::arraySeries() const {
    Q_D(const ComponentsManager);
    return d->arraySeries;
}

CircularSeries *ComponentsManager::circularSeries() const {
    Q_D(const ComponentsManager);
    return d->circularSeries;
}

void ComponentsManager::setBeaconListModel(BeaconListModel *tmp) {
    Q_D(ComponentsManager);
    if (tmp != d->beaconListModel) {
        d->beaconListModel = tmp;
        emit beaconListModelChanged(d->beaconListModel);
    }
}

