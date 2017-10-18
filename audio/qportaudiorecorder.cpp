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
            _isInitialized = false;
            emit q->onError(Pa_GetErrorText(err));
            return  false;
        }

        _isInitialized = true;
        _inputDeviceParam.device = Pa_GetDefaultInputDevice();
        _sampleRate = Pa_GetDeviceInfo(_inputDeviceParam.device)->defaultSampleRate;
        _frameLength = static_cast<ulong>(0.1 * _sampleRate);
        getSupportedSampleRates();
        return _isInitialized  && restart();
    }

    PaError restart() {
        _outputDeviceParam.channelCount = 1;
        _outputDeviceParam.device = Pa_GetDefaultOutputDevice();
        _outputDeviceParam.sampleFormat = paFloat32;
        _outputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(_outputDeviceParam.device)->defaultLowInputLatency;
        _outputDeviceParam.hostApiSpecificStreamInfo = NULL;


        _inputDeviceParam.channelCount = 1;
        _inputDeviceParam.sampleFormat = paFloat32;
        _inputDeviceParam.hostApiSpecificStreamInfo = NULL;
        _inputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(_inputDeviceParam.device)->defaultLowInputLatency;

        Q_Q(QPortAudioRecorder);
        const PaError err = Pa_OpenStream(&_dataStream, &_inputDeviceParam, NULL, _sampleRate, _frameLength, paClipOff, &QPortAudioCallback, q);
        if (err != paNoError) {
            emit q->onError(Pa_GetErrorText(err));
        }
        return err;
    }

    inline bool isRunning() {
        return Pa_IsStreamActive(_dataStream);
    }

    void getSupportedSampleRates() {
        static const QList<double> sampleRates = {8000.0, 11025.0, 16000.0, 22050.0, 44100.0, 48000.0 };
        _supportedSR.clear();
        foreach(const double sampleRate, sampleRates) {
            if (Pa_IsFormatSupported(&_inputDeviceParam,
                                     &_outputDeviceParam,
                                     sampleRate)) {
                _supportedSR.append(QString::number(sampleRate));
            }
        }
        Q_Q(QPortAudioRecorder);
        emit q->supportedSampleRatesChanged(_supportedSR);
    }

    PaError record() {
        if (isRunning()) {
            return paNoError;
        }
        Q_Q(QPortAudioRecorder);
        const PaError err = Pa_StartStream(_dataStream);
        if ( err != paNoError ) {
            emit q->onError(Pa_GetErrorText(err));
        }
        emit q->activeChanged(isRunning());
        return err;
    }

    PaError stop() {
        if (isRunning()) {
            Q_Q(QPortAudioRecorder);
            const PaError err = Pa_StopStream(_dataStream);
            if ( err != paNoError ) {
                emit q->onError(Pa_GetErrorText(err));
            }
            emit q->activeChanged(!isRunning());
            return err;
        }
        return paNoError;
    }

    void setInputDevice(PaDeviceIndex index) {
        if (index != _inputDeviceParam.device
                && index < Pa_GetDeviceCount()
                && Pa_GetDeviceInfo(index)->maxInputChannels > 0) {
            Q_Q(QPortAudioRecorder);
            _inputDeviceParam.device = index;
            emit q->deviceChanged(index);
            getSupportedSampleRates();
        }
    }


    PaError setSampleRate(double sr) {
        if (sr != _sampleRate) {
            Q_Q(QPortAudioRecorder);
            _sampleRate = sr;
            emit q->sampleRateChanged(sr);
            return Pa_IsFormatSupported(&_inputDeviceParam,
                                                         &_outputDeviceParam,
                                                         _sampleRate);

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
        static_cast<QPortAudioRecorder*>(userData)->bufferReady(inputBuffer, outputBuffer, framesPerBuffer);
        return paContinue;
    }


    QPortAudioRecorder* const q_ptr;
    QStringList             _supportedSR;
    PaStream*               _dataStream;
    PaStreamParameters      _inputDeviceParam;
    PaStreamParameters      _outputDeviceParam;
    double                  _sampleRate{8000.0};
    ulong                   _frameLength{80};
    bool                    _isInitialized{false};
};

QPortAudioRecorder::QPortAudioRecorder(QObject *parent)
    : QObject(parent),
      d_ptr(new QPortAudioRecorderPrivate(this))
{

}


double QPortAudioRecorder::streamTimestamp() const {
    Q_D(const QPortAudioRecorder);
    return Pa_GetStreamTime(d->_dataStream);
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
    return isInitialized() && Pa_IsStreamActive(d->_dataStream);
}
bool QPortAudioRecorder::isInitialized() const {
    Q_D(const QPortAudioRecorder);
    return d->_isInitialized;
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
    return d->_supportedSR;

}

bool QPortAudioRecorder::reset() {
    Q_D(QPortAudioRecorder);
    return d->restart() == paNoError;
}

int QPortAudioRecorder::device() const {
    Q_D(const QPortAudioRecorder);
    return d->_inputDeviceParam.device;
}

void QPortAudioRecorder::setSampleRate(double sampleRate) {
    Q_D(QPortAudioRecorder);
    d->setSampleRate(sampleRate);
}

void QPortAudioRecorder::setFrameLength(ulong frame) {
    Q_D(QPortAudioRecorder);
    if (frame != d->_frameLength) {
        d->_frameLength = frame;
        emit frameLengthChanged(frame);
    }
}

void QPortAudioRecorder::setDevice(int index) {
    Q_D(QPortAudioRecorder);
    d->setInputDevice(index);
}

void QPortAudioRecorder::bufferReady(const void *input, void *output, ulong framelength) {
    Q_UNUSED(output);
    emit onBufferReady((float*)(input), framelength);
}

ulong QPortAudioRecorder::frameLength() const {
    Q_D(const QPortAudioRecorder);
    return d->_frameLength;
}
double QPortAudioRecorder::sampleRate() const {
    Q_D(const QPortAudioRecorder);
    return d->_sampleRate;
}
double QPortAudioRecorder::latency() const {
    Q_D(const QPortAudioRecorder);
    return d->_inputDeviceParam.suggestedLatency;
}
