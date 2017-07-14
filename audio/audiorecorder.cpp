#include "audiorecorder.h"

#include <QAudioInput>
#include <QAudioBuffer>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioInputSelectorControl>

class AudioRecorderPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioRecorderPrivate)
    Q_DECLARE_PUBLIC(AudioRecorder)
public:
    AudioRecorderPrivate(AudioRecorder* parent) :
        q_ptr(parent),
        _audioInput(new QAudioInput(_audioFormat, parent)) {
        _audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();

        Q_Q(AudioRecorder);
        QObject::connect(_audioInputSelector, &QAudioInputSelectorControl::activeInputChanged, q, &AudioRecorder::activeInputDeviceChanged);
        QObject::connect(_audioInputSelector, &QAudioInputSelectorControl::availableInputsChanged, [&](){
            emit q->activeInputsDevicesChanged(_audioInputSelector->availableInputs());
        });
    }
    ~AudioRecorderPrivate() {}

    bool setFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        _audioFormat = format;
        q->audioFormatChanged(_audioFormat);
        return _audioDeviceInfo.isFormatSupported(format);
    }

    QAudioFormat setNearestFormat(const QAudioFormat& format) {
        Q_Q(AudioRecorder);
        _audioFormat = (_audioDeviceInfo.isFormatSupported(format)) ? format : _audioDeviceInfo.nearestFormat(format);
        emit q->audioFormatChanged(_audioFormat);
        return _audioFormat;
    }

    QAudioFormat setPreferredFormatForDevice(const QAudioDeviceInfo& device) {
        Q_Q(AudioRecorder);
        _audioFormat = device.preferredFormat();
        emit q->audioFormatChanged(_audioFormat);
        return _audioFormat;
    }

    AudioRecorder * const  q_ptr;
    QAudioDeviceInfo _audioDeviceInfo;
    QAudioInput*     _audioInput;
    QAudioInputSelectorControl* _audioInputSelector;
    QIODevice*       _audioDevice;
    QAudioFormat     _audioFormat;
};

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent),
    d_ptr(new AudioRecorderPrivate(this))
{

}

AudioRecorder::~AudioRecorder() {

}

