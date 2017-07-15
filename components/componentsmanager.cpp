#include "componentsmanager.h"
#include "drawermodel.h"
#include "tabbarmodel.h"

#include <QSharedData>
#include <QQmlEngine>

class ComponentsManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(ComponentsManagerPrivate)
    Q_DECLARE_PUBLIC(ComponentsManager)
public:
    ComponentsManagerPrivate(ComponentsManager* parent) :
        q_ptr(parent),
        drawerModel(new DrawerModel(parent)),
        tabBarModel(new TabBarModel(parent))
    {

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
    DrawerModel*             drawerModel;
    TabBarModel*             tabBarModel;
};

ComponentsManager::ComponentsManager(QObject *parent) :
    QObject(parent),
    d_ptr(new ComponentsManagerPrivate(this))
{
    qmlRegisterType<TabBarModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "DrawerModel");
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
