#include "audiorecorder.h"
#include <portaudio.h>
#include <QSharedData>
#include <QStringList>
class AudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioRecorderPrivate)
    Q_DECLARE_PUBLIC(AudioRecorder)
public:
    AudioRecorderPrivate(AudioRecorder* parent) : q_ptr(parent) {
        initialize();
    }

    ~AudioRecorderPrivate() {
        Pa_Terminate();
    }

    bool initialize() {
        Q_Q(AudioRecorder);
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

        Q_Q(AudioRecorder);
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
        Q_Q(AudioRecorder);
        emit q->supportedSampleRatesChanged(supportedSR);
    }

    PaError record() {
        if (isRunning()) {
            return paNoError;
        }
        Q_Q(AudioRecorder);
        const PaError err = Pa_StartStream(dataStream);
        if ( err != paNoError ) {
            emit q->onError(Pa_GetErrorText(err));
        }
        emit q->activeChanged(isRunning());
        return err;
    }

    PaError stop() {
        if (isRunning()) {
            Q_Q(AudioRecorder);
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
            Q_Q(AudioRecorder);
            inputDeviceParam.device = index;
            emit q->deviceChanged(index);
            getSupportedSampleRates();
        }
    }


    PaError setSampleRate(double sr) {
        if (sr != sampleRate) {
            Q_Q(AudioRecorder);
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
        AudioRecorder* recorder = static_cast<AudioRecorder*>(userData);
        emit recorder->onBufferReady((float*)(inputBuffer), framesPerBuffer);
        emit recorder->streamTimestampChanged(timeInfo->currentTime);
        return paContinue;
    }


    AudioRecorder* const q_ptr;
    QStringList             supportedSR;
    PaStream*               dataStream;
    PaStreamParameters      inputDeviceParam;
    PaStreamParameters      outputDeviceParam;
    double                  sampleRate{8000.0};
    ulong                   frameLength{10};
    bool                    isInitialized{false};
};

AudioRecorder::AudioRecorder(QObject *parent)
    : QObject(parent),
      d_ptr(new AudioRecorderPrivate(this))
{

}

double AudioRecorder::streamTimestamp() const {
    Q_D(const AudioRecorder);
    return Pa_GetStreamTime(d->dataStream);
}

void AudioRecorder::toggle() {
    Q_D(AudioRecorder);
    if (active()) {
        d->stop();
    } else {
        d->record();
    }
}

int AudioRecorder::stop() {
    Q_D(AudioRecorder);
    return d->stop();
}

int AudioRecorder::record() {
    Q_D(AudioRecorder);
    return d->record();
}
bool AudioRecorder::active() const {
    Q_D(const AudioRecorder);
    return isInitialized() && Pa_IsStreamActive(d->dataStream);
}
bool AudioRecorder::isInitialized() const {
    Q_D(const AudioRecorder);
    return d->isInitialized;
}

QStringList AudioRecorder::inputDevices() const {
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

QStringList AudioRecorder::supportedSampleRates() const {
    Q_D(const AudioRecorder);
    return d->supportedSR;

}

bool AudioRecorder::reset() {
    Q_D(AudioRecorder);
    return d->restart() == paNoError;
}

int AudioRecorder::device() const {
    Q_D(const AudioRecorder);
    return d->inputDeviceParam.device;
}

void AudioRecorder::setSampleRate(double sampleRate) {
    Q_D(AudioRecorder);
    d->setSampleRate(sampleRate);
}

void AudioRecorder::setFrameLength(ulong frame) {
    Q_D(AudioRecorder);
    if (frame != d->frameLength) {
        d->frameLength = frame;
        emit frameLengthChanged(frame);
    }
}

void AudioRecorder::setDevice(int index) {
    Q_D(AudioRecorder);
    d->setInputDevice(index);
}

ulong AudioRecorder::frameLength() const {
    Q_D(const AudioRecorder);
    return d->frameLength;
}
double AudioRecorder::sampleRate() const {
    Q_D(const AudioRecorder);
    return d->sampleRate;
}
double AudioRecorder::latency() const {
    Q_D(const AudioRecorder);
    return d->inputDeviceParam.suggestedLatency;
}
