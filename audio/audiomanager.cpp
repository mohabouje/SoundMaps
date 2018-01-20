#include "audiomanager.h"

#include "sm_config.h"

#include <qshareddata.h>
#include <qqml.h>
class AudioManagerPrivate : QSharedData {
    Q_DISABLE_COPY(AudioManagerPrivate)
    Q_DECLARE_PUBLIC(AudioManager)
public:
    AudioManagerPrivate(AudioManager* parent) :
        q_ptr(parent),
        recorder(new AudioRecorder(parent))
    {

    }

    void setRecorder(AudioRecorder* tmp) {
        Q_Q(AudioManager);
        if (tmp != recorder) {
            recorder = tmp;
            emit q->recorderChanged(recorder);
        }
    }

    AudioManager* const q_ptr;
    AudioRecorder *recorder;
};

AudioManager::AudioManager(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioManagerPrivate(this))
{
    qmlRegisterType<AudioRecorder>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR, "AudioRecorder");
    reset();
}

QObject *AudioManager::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(AudioManager);
}

AudioManager::~AudioManager() {
    delete d_ptr;
}

AudioRecorder *AudioManager::recorder() const {
    Q_D(const AudioManager);
    return d->recorder;
}


void AudioManager::reset() {
    Q_D(AudioManager);
    d->recorder->reset();
}

void AudioManager::setRecorder(AudioRecorder *recorder) {
    Q_D(AudioManager);
    d->setRecorder(recorder);
}
