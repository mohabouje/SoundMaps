#include "audiomanager.h"

#include "config.h"

#include <qshareddata.h>
#include <qqml.h>
class AudioManagerPrivate : QSharedData {
    Q_DISABLE_COPY(AudioManagerPrivate)
    Q_DECLARE_PUBLIC(AudioManager)
public:
    AudioManagerPrivate(AudioManager* parent) :
        q_ptr(parent),
        circularSeries(new CircularBufferSeries(parent)),
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

    void setAudioSeries(CircularBufferSeries* tmp) {
        Q_Q(AudioManager);
        if (tmp != circularSeries) {
            circularSeries = tmp;
            emit q->audioSeriesChanged(circularSeries);
        }
    }

    AudioManager* const q_ptr;
    CircularBufferSeries* circularSeries;
    AudioRecorder *recorder;
};

AudioManager::AudioManager(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioManagerPrivate(this))
{
    qmlRegisterType<AudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioRecorder");

    Q_D(AudioManager);
    connect(d->recorder, &AudioRecorder::onBufferReady, this, [&](float * _t1, ulong _t2){
        Q_D(AudioManager);
        d->circularSeries->appendBuffer(_t1, _t2);
    });
    reset();
}

AudioManager::~AudioManager() {
    delete d_ptr;
}

CircularBufferSeries *AudioManager::audioSeries() const {
    Q_D(const AudioManager);
    return d->circularSeries;
}

AudioRecorder *AudioManager::recorder() const {
    Q_D(const AudioManager);
    return d->recorder;
}


void AudioManager::reset() {
    Q_D(AudioManager);
    d->recorder->reset();
    const int size = d->recorder->sampleRate() * d->recorder->frameLength() / 1000.;
    d->circularSeries->setSize(size);
}

void AudioManager::setAudioSeries(CircularBufferSeries *source) {
    Q_D(AudioManager);
    d->setAudioSeries(source);
}
void AudioManager::setRecorder(AudioRecorder *recorder) {
    Q_D(AudioManager);
    d->setRecorder(recorder);
}
