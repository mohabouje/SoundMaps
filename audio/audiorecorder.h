#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QObject>
#include <QAudioInput>
#include <QAudioBuffer>
#include <QAudioFormat>
class AudioRecorderPrivate;
class AudioRecorder : public QObject {
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = nullptr);
    ~AudioRecorder();
signals:
    void audioRecorderStarted(QAudio::Error error);
    void audioFormatNotSupported(const QAudioFormat& format);
    void audioFormatChanged(const QAudioFormat& format);
    void activeInputDeviceChanged(const QString& name);
    void activeInputsDevicesChanged(const QStringList& list);
private:
    Q_DECLARE_PRIVATE(AudioRecorder)
    Q_DISABLE_COPY(AudioRecorder)
    AudioRecorderPrivate* d_ptr;
};



#endif // AUDIODEVICE_H
