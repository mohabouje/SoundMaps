#include "appdelegate.h"
#include "config.h"

#include <audio/audiorecorder.h>
#include <audio/audiobuffer.h>
#include <charts/audiodatasource.h>
#include <components/componentsmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent),
        audioRecorder(new AudioRecorder(parent)),
        audioDataSource(new AudioDataSource(parent)),
        componentsManager(new ComponentsManager(parent))
    {
        audioDataSource->initialize(audioRecorder->sampleRate(), audioRecorder->bufferDuration());
        QObject::connect(audioRecorder, &AudioRecorder::sampleRateChanged, [&](int sampleRate) {
            audioDataSource->initialize(sampleRate, audioRecorder->bufferDuration());
        });
        QObject::connect(audioRecorder, &AudioRecorder::bufferDurationChanged, [&](int duration) {
            audioDataSource->initialize(audioRecorder->sampleRate(), duration);
        });
        QObject::connect(audioRecorder->buffer(), &AudioBuffer::bufferReady, audioDataSource, &AudioDataSource::appendBuffer);

    }
    ~AppDelegatePrivate() {}

    void setAudioDataSource(AudioDataSource* tmp) {
        Q_Q(AppDelegate);
        if (tmp != audioDataSource) {
            audioDataSource = tmp;
            q->audioDataSourceChanged(audioDataSource);
        }
    }

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
    AudioDataSource* audioDataSource;
    ComponentsManager* componentsManager;
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<AudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioRecorder");
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");
    qmlRegisterType<AudioDataSource>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioDataSource");
}

AudioRecorder *AppDelegate::audioRecorder() const {
    Q_D(const AppDelegate);
    return d->audioRecorder;
}

AudioDataSource *AppDelegate::audioDataSource() const {
    Q_D(const AppDelegate);
    return d->audioDataSource;
}

ComponentsManager *AppDelegate::componentsManager() const {
    Q_D(const AppDelegate);
    return d->componentsManager;
}

void AppDelegate::setAudioDataSource(AudioDataSource *source) {
    Q_D(AppDelegate);
    d->setAudioDataSource(source);
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


