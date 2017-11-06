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
        circularSeries(new CircularBufferSeries(parent)),
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

    void setAudioSeries(CircularBufferSeries* tmp) {
        Q_Q(QPortAudioManager);
        if (tmp != circularSeries) {
            circularSeries = tmp;
            emit q->audioSeriesChanged(circularSeries);
        }
    }

    QPortAudioManager* const q_ptr;
    CircularBufferSeries* circularSeries;
    QPortAudioRecorder *recorder;
};

QPortAudioManager::QPortAudioManager(QObject *parent) :
    QObject(parent),
    d_ptr(new QPortAudioManagerPrivate(this))
{
    qmlRegisterType<QPortAudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "QPortAudioRecorder");

    Q_D(QPortAudioManager);
    connect(d->recorder, &QPortAudioRecorder::onBufferReady, this, [&](float * _t1, ulong _t2){
        Q_D(QPortAudioManager);
        d->circularSeries->appendBuffer(_t1, _t2);
    });
}

QPortAudioManager::~QPortAudioManager() {
    delete d_ptr;
}

CircularBufferSeries *QPortAudioManager::audioSeries() const {
    Q_D(const QPortAudioManager);
    return d->circularSeries;
}

QPortAudioRecorder *QPortAudioManager::recorder() const {
    Q_D(const QPortAudioManager);
    return d->recorder;
}


void QPortAudioManager::reset() {
    Q_D(QPortAudioManager);
    d->recorder->reset();
    d->circularSeries->setSize(d->recorder->sampleRate() * d->recorder->frameLength() / 1000. );
}

void QPortAudioManager::setAudioSeries(CircularBufferSeries *source) {
    Q_D(QPortAudioManager);
    d->setAudioSeries(source);
}
void QPortAudioManager::setRecorder(QPortAudioRecorder *recorder) {
    Q_D(QPortAudioManager);
    d->setRecorder(recorder);
}
