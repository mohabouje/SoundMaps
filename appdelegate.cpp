#include "appdelegate.h"
#include "config.h"

#include <audio/audiorecorder.h>
#include <components/componentsmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent),
        audioRecorder(new AudioRecorder(parent)),
        componentsManager(new ComponentsManager(parent))
    {

    }
    ~AppDelegatePrivate() {}


    void setAudioRecorder(AudioRecorder* tmp) {
        Q_Q(AppDelegate);
        if (tmp != audioRecorder) {
            audioRecorder = tmp;
            q->audioRecorderChanged(audioRecorder);
        }
    }

    void setComponentsManager(ComponentsManager* tmp) {
        Q_Q(AppDelegate);
        if (tmp != componentsManager) {
            componentsManager = tmp;
            emit q->componentsManagerChanged(componentsManager);
        }
    }

    AppDelegate* const  q_ptr;
    AudioRecorder*   audioRecorder;
    ComponentsManager* componentsManager;
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<AudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioRecorder");
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");

}

AudioRecorder *AppDelegate::audioRecorder() const {
    Q_D(const AppDelegate);
    return d->audioRecorder;
}

ComponentsManager *AppDelegate::componentsManager() const {
    Q_D(const AppDelegate);
    return d->componentsManager;
}

void AppDelegate::setComponentsManager(ComponentsManager * componentsManager) {
    Q_D(AppDelegate);
    d->setComponentsManager(componentsManager);
}


QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new AppDelegate();
}

void AppDelegate::setAudioRecorder(AudioRecorder *audioRecorder) {
    Q_D(AppDelegate);
    d->setAudioRecorder(audioRecorder);
}


