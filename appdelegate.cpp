#include "appdelegate.h"
#include "config.h"

#include <qportaudio/qportaudiomanager.h>
#include <components/componentsmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent),
        componentsManager(new ComponentsManager(parent)),
        audioManager(new QPortAudioManager(parent))
    {


    }
    ~AppDelegatePrivate() {}

    AppDelegate* const  q_ptr;
    ComponentsManager* componentsManager;
    QPortAudioManager*  audioManager;
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");
    qmlRegisterType<QPortAudioManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "QPortAudioManager");
}

AppDelegate::~AppDelegate()
{
    delete d_ptr;
    if (instance != nullptr) {
        delete instance;
    }
}


ComponentsManager *AppDelegate::componentsManager() const {
    Q_D(const AppDelegate);
    return d->componentsManager;
}

void AppDelegate::setComponentsManager(ComponentsManager * tmp) {
    Q_D(AppDelegate);
    if (tmp != d->componentsManager) {
        d->componentsManager = tmp;
        emit componentsManagerChanged(tmp);
    }}

QPortAudioManager *AppDelegate::audioManager() const {
    Q_D(const AppDelegate);
    return d->audioManager;
}

void AppDelegate::setAudioManager(QPortAudioManager *value) {
    Q_D(AppDelegate);
    if (value != d->audioManager) {
        d->audioManager = value;
        emit audioManagerChanged(value);
    }
}

AppDelegate* AppDelegate::instance = nullptr;
QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    if (instance == nullptr) {
        instance = new AppDelegate();
    }
    return instance;
}

