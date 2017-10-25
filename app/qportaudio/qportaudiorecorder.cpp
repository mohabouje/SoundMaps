#include "qportaudiorecorder.h"
#include <portaudio.h>
#include <QSharedData>
#include <QStringList>
class QPortAudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(QPortAudioRecorderPrivate)
    Q_DECLARE_PUBLIC(QPortAudioRecorder)
public:
    QPortAudioRecorderPrivate(QPortAudioRecorder* parent) : q_ptr(parent) {
        initialize();
    }

    ~QPortAudioRecorderPrivate() {
        Pa_Terminate();
    }

    bool initialize() {
        Q_Q(QPortAudioRecorder);
        const PaError err = Pa_Initialize();
        if( err != paNoError ) {
            isInitialized = false;
            emit q->onError(Pa_GetErrorText(err));
            return  false;
        }

        isInitialized = true;
        inputDeviceParam.device = Pa_GetDefaultInputDevice();
        sampleRate = Pa_GetDeviceInfo(inputDeviceParam.device)->defaultSampleRate;
        frameLength = 10;
        getSupportedSampleRates();
        return isInitialized  && restart();
    }

    PaError restart() {
        outputDeviceParam.channelCount = 1;
        outputDeviceParam.device = Pa_GetDefaultOutputDevice();
        outputDeviceParam.sampleFormat = paFloat32;
        outputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(outputDeviceParam.device)->defaultLowInputLatency;
        outputDeviceParam.hostApiSpecificStreamInfo = NULL;


        inputDeviceParam.channelCount = 1;
        inputDeviceParam.sampleFormat = paFloat32;
        inputDeviceParam.hostApiSpecificStreamInfo = NULL;
        inputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(inputDeviceParam.device)->defaultLowInputLatency;

        Q_Q(QPortAudioRecorder);
        const PaError err = Pa_OpenStream(&dataStream,
                                          &inputDeviceParam,
                                          NULL,
                                          sampleRate,
                                          static_cast<ulong>(frameLength / 1000.0 * sampleRate),
                                          paClipOff,
                                          &QPortAudioCallback, q);
        if (err != paNoError) {
            emit q->onError(Pa_GetErrorText(err));
        }
        return err;
    }

    inline bool isRunning() {
        return Pa_IsStreamActive(dataStream);
    }

    void getSupportedSampleRates() {
        static const QList<double> sampleRates = {8000.0, 11025.0, 16000.0, 22050.0, 44100.0, 48000.0 };
        supportedSR.clear();
        foreach(const double sampleRate, sampleRates) {
            if (Pa_IsFormatSupported(&inputDeviceParam,
                                     &outputDeviceParam,
                                     sampleRate)) {
                supportedSR.append(QString::number(sampleRate));
            }
        }
        Q_Q(QPortAudioRecorder);
        emit q->supportedSampleRatesChanged(supportedSR);
    }

    PaError record() {
        if (isRunning()) {
            return paNoError;
        }
        Q_Q(QPortAudioRecorder);
        const PaError err = Pa_StartStream(dataStream);
        if ( err != paNoError ) {
            emit q->onError(Pa_GetErrorText(err));
        }
        emit q->activeChanged(isRunning());
        return err;
    }

    PaError stop() {
        if (isRunning()) {
            Q_Q(QPortAudioRecorder);
            const PaError err = Pa_StopStream(dataStream);
            if ( err != paNoError ) {
                emit q->onError(Pa_GetErrorText(err));
            }
            emit q->activeChanged(!isRunning());
            return err;
        }
        return paNoError;
    }

    void setInputDevice(PaDeviceIndex index) {
        if (index != inputDeviceParam.device
                && index < Pa_GetDeviceCount()
                && Pa_GetDeviceInfo(index)->maxInputChannels > 0) {
            Q_Q(QPortAudioRecorder);
            inputDeviceParam.device = index;
            emit q->deviceChanged(index);
            getSupportedSampleRates();
        }
    }


    PaError setSampleRate(double sr) {
        if (sr != sampleRate) {
            Q_Q(QPortAudioRecorder);
            sampleRate = sr;
            emit q->sampleRateChanged(sr);
            return Pa_IsFormatSupported(&inputDeviceParam,
                                                         &outputDeviceParam,
                                                         sampleRate);

        }
        return paNoError;
    }

    static int QPortAudioCallback(const void *inputBuffer,
                                            void *outputBuffer,
                                            unsigned long framesPerBuffer,
                                            const PaStreamCallbackTimeInfo *timeInfo,
                                            PaStreamCallbackFlags statusFlags,
                                            void *userData)
    {
        Q_UNUSED(timeInfo);
        Q_UNUSED(statusFlags);
        Q_UNUSED(outputBuffer);
        QPortAudioRecorder* recorder = static_cast<QPortAudioRecorder*>(userData);
        emit recorder->onBufferReady((float*)(inputBuffer), framesPerBuffer);
        emit recorder->streamTimestampChanged(timeInfo->currentTime);
        return paContinue;
    }


    QPortAudioRecorder* const q_ptr;
    QStringList             supportedSR;
    PaStream*               dataStream;
    PaStreamParameters      inputDeviceParam;
    PaStreamParameters      outputDeviceParam;
    double                  sampleRate{8000.0};
    ulong                   frameLength{10};
    bool                    isInitialized{false};
};

QPortAudioRecorder::QPortAudioRecorder(QObject *parent)
    : QObject(parent),
      d_ptr(new QPortAudioRecorderPrivate(this))
{

}

double QPortAudioRecorder::streamTimestamp() const {
    Q_D(const QPortAudioRecorder);
    return Pa_GetStreamTime(d->dataStream);
}

void QPortAudioRecorder::toggle() {
    Q_D(QPortAudioRecorder);
    if (active()) {
        d->stop();
    } else {
        d->record();
    }
}

int QPortAudioRecorder::stop() {
    Q_D(QPortAudioRecorder);
    return d->stop();
}

int QPortAudioRecorder::record() {
    Q_D(QPortAudioRecorder);
    return d->record();
}
bool QPortAudioRecorder::active() const {
    Q_D(const QPortAudioRecorder);
    return isInitialized() && Pa_IsStreamActive(d->dataStream);
}
bool QPortAudioRecorder::isInitialized() const {
    Q_D(const QPortAudioRecorder);
    return d->isInitialized;
}

QStringList QPortAudioRecorder::inputDevices() const {
    QStringList list;
    const PaDeviceIndex count = Pa_GetDeviceCount();
    for (PaDeviceIndex index=0; index<count; index++) {
        const PaDeviceInfo* info = Pa_GetDeviceInfo(index);
        if (info->maxInputChannels > 0) {
            list.append(info->name);
        }
    }
    return list;
}

QStringList QPortAudioRecorder::supportedSampleRates() const {
    Q_D(const QPortAudioRecorder);
    return d->supportedSR;

}

bool QPortAudioRecorder::reset() {
    Q_D(QPortAudioRecorder);
    return d->restart() == paNoError;
}

int QPortAudioRecorder::device() const {
    Q_D(const QPortAudioRecorder);
    return d->inputDeviceParam.device;
}

void QPortAudioRecorder::setSampleRate(double sampleRate) {
    Q_D(QPortAudioRecorder);
    d->setSampleRate(sampleRate);
}

void QPortAudioRecorder::setFrameLength(ulong frame) {
    Q_D(QPortAudioRecorder);
    if (frame != d->frameLength) {
        d->frameLength = frame;
        emit frameLengthChanged(frame);
    }
}

void QPortAudioRecorder::setDevice(int index) {
    Q_D(QPortAudioRecorder);
    d->setInputDevice(index);
}

ulong QPortAudioRecorder::frameLength() const {
    Q_D(const QPortAudioRecorder);
    return d->frameLength;
}
double QPortAudioRecorder::sampleRate() const {
    Q_D(const QPortAudioRecorder);
    return d->sampleRate;
}
double QPortAudioRecorder::latency() const {
    Q_D(const QPortAudioRecorder);
    return d->inputDeviceParam.suggestedLatency;
}
