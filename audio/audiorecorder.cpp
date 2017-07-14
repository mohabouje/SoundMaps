#include "audiorecorder.h"

#include <QAudioInputSelectorControl>
#include <QDebug>

class AudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioRecorderPrivate)
    Q_DECLARE_PUBLIC(AudioRecorder)
public:
    AudioRecorderPrivate(AudioRecorder* parent) :
        q_ptr(parent)
    {}
    ~AudioRecorderPrivate() {}

    inline bool setFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        audioFormat = format;
        q->formatChanged(audioFormat);
        return audioDeviceInfo.isFormatSupported(format);
    }


    inline void setDevice(const QString& name) {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
        foreach(const QAudioDeviceInfo& device, devices) {
            if (QString::compare(name, device.deviceName(), Qt::CaseInsensitive) == 0
                    && QString::compare(name, device.deviceName(), Qt::CaseInsensitive) != 0) {
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
            audioFormat = audioDeviceInfo.nearestFormat(audioFormat);
            emit q->formatChanged(audioFormat);
        }
        emit q->deviceChanged(audioDeviceInfo.deviceName());
    }

    inline bool isActive() const {
        return audioBuffer->isOpen() && (audioInput->state() == QAudio::ActiveState);
    }

    inline QAudio::Error initialize() {
        if (audioInput != nullptr) {
            audioInput->stop();
            delete audioInput;
        }

        audioInput = new QAudioInput(audioDeviceInfo, audioFormat);
        QObject::connect(audioInput, &QAudioInput::stateChanged, [&](QAudio::State state) {
            Q_Q(AudioRecorder);
            emit q->stateChanged(state);
        });
        return audioInput->error();
    }

    inline QAudio::Error record() {
        if (isActive()) {
            qWarning() << "Trying to initialize an active device";
            return QAudio::NoError;
        }
        audioInput->start(audioBuffer);
        return audioInput->error();
    }

    inline void setBufferDuration(int speed) {
        Q_Q(AudioRecorder);
        audioBufferDuration = speed;
        const int sampleSizeInBytes = audioFormat.sampleSize() / 8;
        const int samples = audioFormat.sampleRate() * audioBufferDuration / 1000;
        audioInput->setBufferSize(samples * sampleSizeInBytes);
        emit q->bufferDurationChanged(audioBufferDuration);
    }

    AudioRecorder * const  q_ptr;
    QAudioInput*                                audioInput{nullptr};
    QIODevice*                                  audioBuffer{nullptr};
    QAudioDeviceInfo                            audioDeviceInfo;
    QAudioFormat                                audioFormat;
    int                                         audioBufferDuration;
};

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioRecorderPrivate(this))
{

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

QAudio::Error AudioRecorder::initialize() {
    Q_D(AudioRecorder);
    return d->initialize();

}

QAudio::Error AudioRecorder::record() {
    Q_D(AudioRecorder);
    return d->record();
}

QStringList AudioRecorder::availableDevices() const {
    QStringList list;
    const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach(const QAudioDeviceInfo& device, devices) {
        list << device.deviceName();
    }
    return list;
}

QAudio::State AudioRecorder::state() const {
    Q_D(const AudioRecorder);
    return d->audioInput->state();
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
