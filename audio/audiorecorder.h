#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QAudioInput>
class AudioRecorderPrivate;
class AudioRecorder : public QObject {
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = nullptr);
    enum FormatEngine { Default, Nearest, Prefered };
    ~AudioRecorder();

    Q_INVOKABLE bool isActive() const;
    Q_INVOKABLE QAudio::Error initialize();
    Q_INVOKABLE QAudio::Error record();
public slots:
    void setDevice(const QString& name, bool updateFormatIfNeeded = true);
    void setFormat(const QAudioFormat& format, FormatEngine engine);
signals:
    void audioRecorderStarted(QAudio::Error error);
    void audioRecorderStateChanged(QAudio::State state);
    void audioFormatNotSupported(const QAudioFormat& format);
    void audioFormatChanged(const QAudioFormat& format);
    void audioInputDeviceChanged(const QAudioDeviceInfo& info);
    void activeInputDeviceChanged(const QString& name);
    void activeInputsDevicesChanged(const QStringList& list);
private:
    Q_DECLARE_PRIVATE(AudioRecorder)
    Q_DISABLE_COPY(AudioRecorder)
    AudioRecorderPrivate* d_ptr;
};
#endif // AUDIODEVICE_H
