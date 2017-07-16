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
        initialize();
    }
    ~AudioRecorderPrivate() {}

    inline bool setFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        audioFormat = format;
        audioFormat.setChannelCount(1);
        q->formatChanged(audioFormat);
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
            audioFormat = audioDeviceInfo.preferredFormat();
            audioFormat.setChannelCount(1);
            emit q->formatChanged(audioFormat);
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
        return initialized &&  (audioInput->state() == QAudio::ActiveState);
    }

    inline QAudio::Error initialize() {
        stop();
        delete audioBuffer;
        delete audioInput;
        audioInput = new QAudioInput(audioDeviceInfo, audioFormat);
        QObject::connect(audioInput, &QAudioInput::stateChanged, [&](QAudio::State state) {
            Q_Q(AudioRecorder);
            emit q->stateChanged(static_cast<AudioRecorder::State>(state));
        });
        setBufferDuration(audioBufferDuration);
        initialized = true;
        return audioInput->error();
    }

    inline QAudio::Error stop() {
        if (!isActive()) {
            qWarning() << "Trying to stop an inactive device";
            return QAudio::NoError;
        }
        audioBuffer->stop();
        audioInput->stop();
        initialized = false;
        return  audioInput->error();
    }

    inline QAudio::Error record() {
        QAudio::Error error = QAudio::NoError;
        if (isActive()) {
            qWarning() << "Trying to initialize an active device";
            return error;
        }

        if (!initialized) {
            qWarning() << "Trying to record a not initialized device";
            error = initialize();
        }

        if (error == QAudio::NoError) {
            audioBuffer->start();
            audioInput->start(audioBuffer);
            error = audioInput->error();
        }
        return error;
    }

    inline void setBufferDuration(int speed) {
        Q_Q(AudioRecorder);
        audioBufferDuration = speed;
        const int sampleSizeInBytes = audioFormat.sampleSize() / 8;
        const int sampleCount = audioBufferDuration * audioFormat.sampleRate() / 1000;
        const int bufferSizeInBytes = audioFormat.channelCount() * sampleCount * sampleSizeInBytes;
        audioBuffer = new AudioBuffer(sampleCount, audioFormat);
        audioInput->setBufferSize(bufferSizeInBytes);
        emit q->bufferDurationChanged(audioBufferDuration);
    }

    AudioRecorder * const  q_ptr;
    AudioBuffer*                                audioBuffer{nullptr};
    QAudioInput*                                audioInput{nullptr};
    QAudioDeviceInfo                            audioDeviceInfo;
    QAudioFormat                                audioFormat;
    int                                         audioBufferDuration;
    bool                                        initialized{false};
};

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioRecorderPrivate(this))
{
    availableDevices();
}

AudioRecorder::~AudioRecorder() {

}

void AudioRecorder::setFormat(const QAudioFormat &format, FormatEngine engine) {
    Q_D(AudioRecorder);
    switch (engine) {
    case Default:
        d->setFormat(format);
        break;
    case Nearest:
        d->setFormat(d->audioDeviceInfo.nearestFormat(format));
        break;
    case Prefered:
        d->setFormat(d->audioDeviceInfo.preferredFormat());
        break;
    }
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

QStringList AudioRecorder::supportedSampleRates() const{
    Q_D(const AudioRecorder);
    return d->supportedSampleRates();
}

AudioRecorder::State AudioRecorder::state() const {
    Q_D(const AudioRecorder);
    return static_cast<AudioRecorder::State>(d->audioInput->state());
}

int AudioRecorder::channelCount() const {
    Q_D(const AudioRecorder);
    return d->audioFormat.channelCount();
}

int AudioRecorder::sampleRate() const {
    Q_D(const AudioRecorder);
    return d->audioFormat.sampleRate();
}


QAudioFormat AudioRecorder::format() const {
    Q_D(const AudioRecorder);
    return d->audioFormat;
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
        setFormat(format);
        emit sampleRateChanged(sampleRate);
    }
}

void AudioRecorder::setChannelCount(int channelCount) {
    Q_D(AudioRecorder);
    QAudioFormat format = d->audioFormat;
    if (format.channelCount() != channelCount) {
        format.setChannelCount(channelCount);
        setFormat(format);
        emit channelCountChanged(channelCount);
    }
}
