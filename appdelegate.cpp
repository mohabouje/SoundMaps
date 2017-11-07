#include "appdelegate.h"
#include "config.h"

#include <audio/audiomanager.h>
#include <ui/componentsmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent),
        componentsManager(),
        audioManager(new AudioManager(parent))
    {


    }
    ~AppDelegatePrivate() {}

    AppDelegate* const  q_ptr;
    ComponentsManager* componentsManager{qobject_cast<ComponentsManager*>(
                    ComponentsManager::qmlSingleton(nullptr, nullptr))};
    AudioManager*  audioManager{qobject_cast<AudioManager*>(
                    AudioManager::qmlSingleton(nullptr, nullptr))};
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");
    qmlRegisterType<AudioManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioManager");
}

AppDelegate::~AppDelegate()
{
    delete d_ptr;
}



QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(AppDelegate);
}

