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
        circularSeries(new CircularSeries(parent)),
        spectrogramSeries(new SpectrogramSeries(parent))
    {
    }

    void init() {
        sm::append(drawerModel, "Data Base", "qrc:/icon/database.svg");
        sm::append(drawerModel, "Help", "qrc:/icon/help-circle.svg");
        sm::append(drawerModel, "About", "qrc:/icon/contact-mail.svg");


        sm::append(tabBarModel, "Time", "qrc:/icon/chart-areaspline.svg");
        sm::append(tabBarModel, "Freq", "qrc:/icon/chart-bar.svg");
        sm::append(tabBarModel, "Locator", "qrc:/icon/map-marker-radius.svg");
        sm::append(tabBarModel, "Beacons", "qrc:/icon/access-point.svg", 1);
    }

    ~ComponentsManagerPrivate(){}

    ComponentsManager* const q_ptr;
    ComponentsManager::RefreshRate rs{ComponentsManager::Low};
    DrawerModel*                drawerModel{nullptr};
    TabBarModel*                tabBarModel{nullptr};
    BeaconListModel*            beaconListModel{nullptr};
    CircularSeries*             circularSeries{nullptr};
    SpectrogramSeries*          spectrogramSeries{nullptr};
};

ComponentsManager::ComponentsManager(QObject *parent) :
    QObject(parent),
    d_ptr(new ComponentsManagerPrivate(this))
{
    qmlRegisterType<TabBarModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "DrawerModel");
    qmlRegisterType<BeaconListModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "BeaconListModel");
    qmlRegisterType<CircularSeries>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "CircularSeries");
    qmlRegisterType<SpectrogramSeries>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "SpectrogramSeries");
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

void ComponentsManager::init() {
    Q_D(ComponentsManager);
    d->init();
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

SpectrogramSeries *ComponentsManager::spectrogramSeries() const {
    Q_D(const ComponentsManager);
    return d->spectrogramSeries;
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

