#ifndef AbstractModelManager_H
#define AbstractModelManager_H
#include "sm_config.h"
#include "tabbarmodel.h"
#include "drawermodel.h"
#include "beaconlistmodel.h"
#include <QObject>
#include <QQmlEngine>

class AbstractModelManagerPrivate;
class AbstractModelManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(DrawerModel* drawerModel READ drawerModel WRITE setDrawerModel NOTIFY drawerModelChanged)
    Q_PROPERTY(TabBarModel* tabBarModel READ tabBarModel WRITE setTabBarModel NOTIFY tabBarModelChanged)
    Q_PROPERTY(BeaconListModel* beaconListModel READ beaconListModel WRITE setBeaconListModel NOTIFY beaconListModelChanged)
public:
    explicit AbstractModelManager(QObject *parent = nullptr);
    virtual ~AbstractModelManager();
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);

    DrawerModel*    drawerModel() const;
    TabBarModel*    tabBarModel() const;
    BeaconListModel *beaconListModel() const;

signals:
    void drawerModelChanged(DrawerModel*);
    void tabBarModelChanged(TabBarModel*);
    void beaconListModelChanged(BeaconListModel*);
public slots:
    void init();
    void setDrawerModel(DrawerModel*);
    void setTabBarModel(TabBarModel*);
    void setBeaconListModel(BeaconListModel*);
private:
    Q_DECLARE_PRIVATE(AbstractModelManager)
    Q_DISABLE_COPY(AbstractModelManager)
    SM_DECL_SINGLETON(AbstractModelManager)
    SM_DECL_PIMPL(AbstractModelManager)
};

#endif // AbstractModelManager_H
