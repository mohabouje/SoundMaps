#include "qportaudiomanager.h"

#include "config.h"

#include <qshareddata.h>
#include <qqml.h>

class QPortAudioManagerPrivate : QSharedData {
    Q_DISABLE_COPY(QPortAudioManagerPrivate)
    Q_DECLARE_PUBLIC(QPortAudioManager)
public:
    QPortAudioManagerPrivate(QPortAudioManager* parent) :
        q_ptr(parent),
        audioSeries(new QPortAudioSeries(parent)),
        recorder(new QPortAudioRecorder(parent))
    {

    }

    void setRecorder(QPortAudioRecorder* tmp) {
        Q_Q(QPortAudioManager);
        if (tmp != recorder) {
            recorder = tmp;
            emit q->recorderChanged(recorder);
        }
    }


    void setAudioSeries(QPortAudioSeries* tmp) {
        Q_Q(QPortAudioManager);
        if (tmp != audioSeries) {
            audioSeries = tmp;
            emit q->audioSeriesChanged(audioSeries);
        }
    }

    QPortAudioManager* const q_ptr;
    QPortAudioManager::RefreshRate rs;
    QPortAudioSeries* audioSeries;
    QPortAudioRecorder *recorder;
};

QPortAudioSeries *QPortAudioManager::audioSeries() const {
    Q_D(const QPortAudioManager);
    return d->audioSeries;
}

QPortAudioRecorder *QPortAudioManager::recorder() const {
    Q_D(const QPortAudioManager);
    return d->recorder;
}

QPortAudioManager::RefreshRate QPortAudioManager::refreshRate() const {
    Q_D(const QPortAudioManager);
    return d->rs;
}

void QPortAudioManager::setAudioSeries(QPortAudioSeries *source) {
    Q_D(QPortAudioManager);
    d->setAudioSeries(source);
}
void QPortAudioManager::setRecorder(QPortAudioRecorder *recorder) {
    Q_D(QPortAudioManager);
    d->setRecorder(recorder);
}

void QPortAudioManager::setRefreshRate(QPortAudioManager::RefreshRate refresh) {
    Q_D(QPortAudioManager);
    if (refresh != d->rs) {
        d->rs = refresh;
        d->audioSeries->initialize(d->recorder->sampleRate(), d->rs);
        emit refreshRateChanged(d->rs);
    }
}

#define FRAME_SIZE_MSECS    20
QPortAudioManager::QPortAudioManager(QObject *parent) :
    QObject(parent),
    d_ptr(new QPortAudioManagerPrivate(this))
{
    qmlRegisterType<QPortAudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "QPortAudioRecorder");
    qmlRegisterType<QPortAudioSeries>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "QPortAudioSeries");

    Q_D(QPortAudioManager);
    d->audioSeries->initialize(d->recorder->sampleRate(), FRAME_SIZE_MSECS);
    connect(d->recorder, &QPortAudioRecorder::sampleRateChanged, this,  [&](double sampleRate) {
        Q_D(QPortAudioManager);
        d->audioSeries->initialize(sampleRate, d->rs);
    });
    connect(d->recorder, &QPortAudioRecorder::onBufferReady, this, [&](float * _t1, ulong _t2){
        Q_D(QPortAudioManager);
        d->audioSeries->appendBuffer(_t1, _t2);
    });



}

QPortAudioManager::~QPortAudioManager() {
    delete d_ptr;
}
