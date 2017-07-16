#include "audiobuffer.h"
#include "audiorecorder.h"

#include <QAudioInputSelectorControl>
#include <QDebug>

class AudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioRecorderPrivate)
    Q_DECLARE_PUBLIC(AudioRecorder)
public:
    AudioRecorderPrivate(AudioRecorder* parent) :
        q_ptr(parent)
    {
        setDevice(QAudioDeviceInfo::defaultInputDevice());
        setFormat(audioDeviceInfo.preferredFormat());
        setBufferDuration(AudioRecorder::Medium);
        initialize();
    }
    ~AudioRecorderPrivate() {}

    void ensureBasicProperties() {
        audioFormat.setChannelCount(1);
        audioFormat.setSampleType(QAudioFormat::Float);
    }

    inline bool setFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        const int currentSampleRate = audioFormat.sampleRate();
        audioFormat = format;
        if (audioFormat.sampleRate() != currentSampleRate) {
            emit q->sampleRateChanged(audioFormat.sampleRate());
        }
        return audioDeviceInfo.isFormatSupported(format);
    }
    inline void setDevice(const QString& name) {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
        foreach(const QAudioDeviceInfo& device, devices) {
            if (QString::compare(name, device.deviceName(), Qt::CaseInsensitive) == 0
                    && QString::compare(name, audioDeviceInfo.deviceName(), Qt::CaseInsensitive) != 0) {
                setDevice(device);
                return;
            }
        }
        qWarning() << "Device not found: " << name;
    }

    inline void setDevice(const QAudioDeviceInfo& deviceInfo) {
        Q_Q(AudioRecorder);
        audioDeviceInfo = deviceInfo;
        if (!audioDeviceInfo.isFormatSupported(audioFormat)) {
            setFormat(audioDeviceInfo.preferredFormat());
        }
        emit q->deviceChanged(audioDeviceInfo.deviceName());
        emit q->supportedSampleRatesChanged(supportedSampleRates());
    }

    inline QStringList supportedSampleRates() const {
        QStringList list;
        const QList<int> sampleRates = audioDeviceInfo.supportedSampleRates();
        foreach(const int sampleRate, sampleRates) {
            list << QString::number(sampleRate);
        }
        return  list;
    }

    inline bool isActive() const {
        return  audioInput && (audioInput->state() == QAudio::ActiveState);
    }

    inline QAudio::Error initialize() {
        audioBuffer->deleteLater();
        audioInput->deleteLater();

        audioBuffer = new AudioBuffer(audioBufferDuration * audioFormat.sampleRate() / 1000, audioFormat);
        audioInput = new QAudioInput(audioDeviceInfo, audioFormat);
        QObject::connect(audioInput, &QAudioInput::stateChanged, [&](QAudio::State state) {
            Q_Q(AudioRecorder);
            emit q->stateChanged(static_cast<AudioRecorder::State>(state));
        });
        return audioInput->error();
    }

    inline QAudio::Error stop() {
        if (!isActive()) {
            qWarning() << "Trying to stop an inactive device";
            return QAudio::NoError;
        }
        audioBuffer->stop();
        audioInput->stop();
        return  audioInput->error();
    }

    inline QAudio::Error record() {
        if (isActive()) {
            qWarning() << "Trying to initialize an active device";
            return QAudio::NoError;
        }

        audioBuffer->start();
        audioInput->start(audioBuffer);
        return audioInput->error();
    }

    inline void setBufferDuration(int speed) {
        Q_Q(AudioRecorder);
        audioBufferDuration = speed;
        emit q->bufferDurationChanged(audioBufferDuration);
    }

    AudioRecorder * const  q_ptr;
    AudioBuffer*                                audioBuffer{nullptr};
    QAudioInput*                                audioInput{nullptr};
    QAudioDeviceInfo                            audioDeviceInfo;
    QAudioFormat                                audioFormat;
    int                                         audioBufferDuration{AudioRecorder::Medium};
};

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioRecorderPrivate(this))
{
    availableDevices();
    connect(buffer(), &AudioBuffer::bufferReady, [&](const QVector<double> data){
        qInfo() <<  data.size();
    });
}

AudioRecorder::~AudioRecorder() {

}


void AudioRecorder::setDevice(const QString &name) {
    Q_D(AudioRecorder);
    if (QString::compare(d->audioDeviceInfo.deviceName(), name, Qt::CaseInsensitive) != 0) {
        d->setDevice(name);
    }
}

void AudioRecorder::setBufferDuration(int duration) {
    Q_D(AudioRecorder);
    if (d->audioBufferDuration != duration ) {
        d->setBufferDuration(duration);
    }
}


bool AudioRecorder::isActive() const {
    Q_D(const AudioRecorder);
    return d->isActive();
}

QAudio::Error AudioRecorder::record() {
    Q_D(AudioRecorder);
    return d->record();
}

void AudioRecorder::stop() {
    Q_D(AudioRecorder);
    d->stop();
}

QStringList AudioRecorder::availableDevices() const {
    static bool firstRun = true;
    static QStringList list;
    if (firstRun) {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
        foreach(const QAudioDeviceInfo& device, devices) {
            if (device.supportedSampleRates().size() > 3) {
                list << device.deviceName();
            }
        }
        firstRun = false;
    }
    return list;
}

int AudioRecorder::indexForSampleRate(int sampleRate) const {
    Q_D(const AudioRecorder);
    return d->audioDeviceInfo.supportedSampleRates().indexOf(sampleRate);
}

void AudioRecorder::initialize() {
    Q_D(AudioRecorder);
    d->initialize();
}

QStringList AudioRecorder::supportedSampleRates() const{
    Q_D(const AudioRecorder);
    return d->supportedSampleRates();
}

AudioRecorder::State AudioRecorder::state() const {
    Q_D(const AudioRecorder);
    return static_cast<AudioRecorder::State>(d->audioInput->state());
}

int AudioRecorder::sampleRate() const {
    Q_D(const AudioRecorder);
    return d->audioFormat.sampleRate();
}

AudioBuffer *AudioRecorder::buffer() const {
    Q_D(const AudioRecorder);
    return  d->audioBuffer;
}

QString AudioRecorder::device() const {
    Q_D(const AudioRecorder);
    return d->audioDeviceInfo.deviceName();
}

int AudioRecorder::bufferDuration() const {
    Q_D(const AudioRecorder);
    return d->audioBufferDuration;
}

void AudioRecorder::setSampleRate(int sampleRate) {
    Q_D(AudioRecorder);
    QAudioFormat format = d->audioFormat;
    if (format.sampleRate() != sampleRate) {
        format.setSampleRate(sampleRate);
        d->setFormat(format);
    }
}
