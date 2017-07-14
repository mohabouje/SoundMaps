#include "audiorecorder.h"

#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QDebug>

class AudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioRecorderPrivate)
    Q_DECLARE_PUBLIC(AudioRecorder)
public:
    AudioRecorderPrivate(AudioRecorder* parent) :
        q_ptr(parent) {
    }
    ~AudioRecorderPrivate() {}

    inline bool setFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        _audioFormat = format;
        q->audioFormatChanged(_audioFormat);
        return _audioDeviceInfo.isFormatSupported(format);
    }

    inline QAudioFormat setNearestFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        _audioFormat = (_audioDeviceInfo.isFormatSupported(format)) ? format : _audioDeviceInfo.nearestFormat(format);
        emit q->audioFormatChanged(_audioFormat);
        return _audioFormat;
    }

    inline QAudioFormat setPreferredFormatForDevice(const QAudioDeviceInfo& device) {
        Q_Q(AudioRecorder);
        _audioFormat = device.preferredFormat();
        emit q->audioFormatChanged(_audioFormat);
        return _audioFormat;
    }

    inline void setDevice(const QString& name, bool updateFormatIfNeeded = true) {
        const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
        foreach(const QAudioDeviceInfo& device, devices) {
            if (QString::compare(name, device.deviceName(), Qt::CaseInsensitive) == 0) {
                setDevice(device, updateFormatIfNeeded);
                return;
            }
        }
        qWarning() << "Device not found: " << name;
    }

    inline void setDevice(const QAudioDeviceInfo& deviceInfo, bool updateFormatIfNeeded = true) {
        Q_Q(AudioRecorder);
        _audioDeviceInfo = deviceInfo;
        if (updateFormatIfNeeded && !_audioDeviceInfo.isFormatSupported(_audioFormat)) {
            _audioFormat = _audioDeviceInfo.nearestFormat(_audioFormat);
            emit q->audioFormatChanged(_audioFormat);
        }
        emit q->audioInputDeviceChanged(_audioDeviceInfo);
    }

    inline bool isActive() const {
        return _audioDevice->isOpen() && (_audioInput->state() == QAudio::ActiveState);
    }

    inline QAudio::Error initialize() {
        if (_audioInput != nullptr) {
            _audioInput->stop();
            delete _audioInput;
        }

        _audioInput = new QAudioInput(_audioDeviceInfo, _audioFormat);
        QObject::connect(_audioInput, &QAudioInput::stateChanged, [&](QAudio::State state) {
            Q_Q(AudioRecorder);
            emit q->audioRecorderStateChanged(state);
        });
        return _audioInput->error();
    }

    inline QAudio::Error record() {
        Q_Q(AudioRecorder);
        if (isActive()) {
            qWarning() << "Trying to initialize an active device";
            return QAudio::NoError;
        }
        _audioInput->start(_audioDevice);
        const QAudio::Error error = _audioInput->error();
        emit q->audioRecorderStarted(error);
        return error;
    }

    AudioRecorder * const  q_ptr;
    QAudioInput*                _audioInput{nullptr};
    QIODevice*                  _audioDevice{nullptr};
    QAudioDeviceInfo            _audioDeviceInfo;
    QAudioFormat                _audioFormat;
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
        d->setNearestFormat(format);
        break;
    case Prefered:
        d->setPreferredFormatForDevice(d->_audioDeviceInfo);
        break;
    }
}

void AudioRecorder::setDevice(const QString &name, bool updateFormatIfNeeded) {
    Q_D(AudioRecorder);
    return d->setDevice(name, updateFormatIfNeeded);
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
