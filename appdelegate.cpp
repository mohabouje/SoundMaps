#include "appdelegate.h"
#include "config.h"

#include <audio/audiorecorder.h>
#include <audio/audiobuffer.h>
#include <audio/qportaudiorecorder.h>
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
        componentsManager(new ComponentsManager(parent)),
        recorder(new QPortAudioRecorder(parent))
    {
        audioDataSource->initialize(recorder->sampleRate(), 100);
        QObject::connect(recorder, &QPortAudioRecorder::sampleRateChanged, [&](double sampleRate) {
            audioDataSource->initialize(sampleRate, audioRecorder->bufferDuration());
        });
        QObject::connect(recorder, &QPortAudioRecorder::onBufferReady, [&](float * _t1, ulong _t2){
            audioDataSource->appendBuffer(_t1, _t2);
        });

    }
    ~AppDelegatePrivate() {}

    void setRecorder(QPortAudioRecorder* tmp) {
        Q_Q(AppDelegate);
        if (tmp != recorder) {
            recorder = tmp;
            emit q->recorderChanged(recorder);
        }
    }

    void setAudioDataSource(AudioDataSource* tmp) {
        Q_Q(AppDelegate);
        if (tmp != audioDataSource) {
            audioDataSource = tmp;
            emit q->audioDataSourceChanged(audioDataSource);
        }
    }

    void setAudioRecorder(AudioRecorder* tmp) {
        Q_Q(AppDelegate);
        if (tmp != audioRecorder) {
            audioRecorder = tmp;
            emit q->audioRecorderChanged(audioRecorder);
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
    QPortAudioRecorder *recorder;
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<AudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioRecorder");
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");
    qmlRegisterType<QPortAudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "QPortAudioRecorder");
    qmlRegisterType<AudioDataSource>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioDataSource");
}

AppDelegate::~AppDelegate()
{
    delete d_ptr;
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

QPortAudioRecorder *AppDelegate::recorder() const {
    Q_D(const AppDelegate);
    return d->recorder;
}

void AppDelegate::setAudioDataSource(AudioDataSource *source) {
    Q_D(AppDelegate);
    d->setAudioDataSource(source);
}

void AppDelegate::setComponentsManager(ComponentsManager * componentsManager) {
    Q_D(AppDelegate);
    d->setComponentsManager(componentsManager);
}

void AppDelegate::setRecorder(QPortAudioRecorder *recorder) {
    Q_D(AppDelegate);
    d->setRecorder(recorder);
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


