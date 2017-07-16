#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QAudioInput>
class AudioBuffer;
class AudioRecorderPrivate;
class AudioRecorder : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
    Q_PROPERTY(int bufferDuration READ bufferDuration WRITE setBufferDuration NOTIFY bufferDurationChanged)
    Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(QStringList supportedSampleRates READ supportedSampleRates NOTIFY supportedSampleRatesChanged)
public:
    explicit AudioRecorder(QObject *parent = nullptr);
    enum FormatEngine {
        Default = 0,
        Nearest,
        Prefered };
    Q_ENUMS(FormatEngine)

    enum DefaultBufferSize {
        Low = 100,
        Medium = 50,
        High = 25
    };
    Q_ENUMS(DefaultBufferSize)
    ~AudioRecorder();
    Q_INVOKABLE QAudio::Error record();
    Q_INVOKABLE void stop();
    Q_INVOKABLE QStringList availableDevices() const;
    Q_INVOKABLE int indexForSampleRate(int sampleRate) const;
    Q_INVOKABLE void initialize();

    bool active() const;
    QStringList supportedSampleRates() const;
    QAudio::State state() const;
    AudioBuffer* buffer() const;
    int sampleRate() const;
    int bufferDuration() const;
    QString device() const;
public slots:
    void setSampleRate(int sampleRate);
    void setDevice(const QString& name);
    void setBufferDuration(int duration);
signals:
    void stateChanged(QAudio::State state);
    void sampleRateChanged(int sampleRate);
    void deviceChanged(const QString& decive);
    void bufferDurationChanged(int duration);
    void supportedSampleRatesChanged(const QStringList&);
    void activeChanged(bool);
private:
    Q_DECLARE_PRIVATE(AudioRecorder)
    Q_DISABLE_COPY(AudioRecorder)
    AudioRecorderPrivate* d_ptr;
};
#endif // AUDIODEVICE_H
