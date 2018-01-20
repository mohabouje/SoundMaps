#include "abstractmodelmanager.h"

#include <QSharedData>
class AbstractModelManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(AbstractModelManagerPrivate)
    Q_DECLARE_PUBLIC(AbstractModelManager)
public:
    AbstractModelManagerPrivate(AbstractModelManager* parent) :
        q_ptr(parent),
        drawerModel(new DrawerModel(parent)),
        tabBarModel(new TabBarModel(parent)),
        beaconListModel(new BeaconListModel(parent))
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

    ~AbstractModelManagerPrivate(){}

    AbstractModelManager* const q_ptr;
    DrawerModel*                drawerModel{nullptr};
    TabBarModel*                tabBarModel{nullptr};
    BeaconListModel*            beaconListModel{nullptr};
};

AbstractModelManager::AbstractModelManager(QObject *parent) :
    QObject(parent),
    d_ptr(new AbstractModelManagerPrivate(this))
{
    qmlRegisterType<TabBarModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "DrawerModel");
    qmlRegisterType<BeaconListModel>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "BeaconListModel");
}

QObject *AbstractModelManager::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(AbstractModelManager);
}

AbstractModelManager::~AbstractModelManager()
{
    delete d_ptr;
}

void AbstractModelManager::init() {
    Q_D(AbstractModelManager);
    d->init();
}

DrawerModel *AbstractModelManager::drawerModel() const {
    Q_D(const AbstractModelManager);
    return d->drawerModel;
}

TabBarModel *AbstractModelManager::tabBarModel() const {
    Q_D(const AbstractModelManager);
    return d->tabBarModel;
}

void AbstractModelManager::setDrawerModel(DrawerModel * tmp) {
    Q_D(AbstractModelManager);
    if (tmp != d->drawerModel) {
        d->drawerModel = tmp;
        emit drawerModelChanged(d->drawerModel);
    }
}

void AbstractModelManager::setTabBarModel(TabBarModel * tmp) {
    Q_D(AbstractModelManager);
    if (tmp != d->tabBarModel) {
        d->tabBarModel = tmp;
        emit tabBarModelChanged(d->tabBarModel);
    }
}

BeaconListModel *AbstractModelManager::beaconListModel() const {
    Q_D(const AbstractModelManager);
    return d->beaconListModel;
}


void AbstractModelManager::setBeaconListModel(BeaconListModel *tmp) {
    Q_D(AbstractModelManager);
    if (tmp != d->beaconListModel) {
        d->beaconListModel = tmp;
        emit beaconListModelChanged(d->beaconListModel);
    }
}

