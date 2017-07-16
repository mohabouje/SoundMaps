#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <QAudioInput>
class AudioRecorderPrivate;
class AudioRecorder : public QObject {
    Q_OBJECT
    Q_PROPERTY(int sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
    Q_PROPERTY(int channelCount READ channelCount WRITE setChannelCount NOTIFY channelCountChanged)
    Q_PROPERTY(int bufferDuration READ bufferDuration WRITE setBufferDuration NOTIFY bufferDurationChanged)
    Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(AudioRecorder::State state READ state NOTIFY stateChanged)
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

    enum State {
        ActiveState = QAudio::ActiveState,
        SuspendedState = QAudio::SuspendedState,
        StoppedState = QAudio::StoppedState,
        IdleState = QAudio::IdleState
    };
    Q_ENUMS(State)

    ~AudioRecorder();
    Q_INVOKABLE bool isActive() const;
    Q_INVOKABLE QAudio::Error record();
    Q_INVOKABLE void stop();
    Q_INVOKABLE QStringList availableDevices() const;
    Q_INVOKABLE int indexForSampleRate(int sampleRate) const;

    QStringList supportedSampleRates() const;
    AudioRecorder::State state() const;
    int channelCount() const;
    int sampleRate() const;
    QAudioFormat format() const;
    QString device() const;
    int bufferDuration() const;
public slots:
    void setSampleRate(int sampleRate);
    void setChannelCount(int channels);
    void setDevice(const QString& name);
    void setFormat(const QAudioFormat& format, FormatEngine engine = Default);
    void setBufferDuration(int duration);
signals:
    void stateChanged(AudioRecorder::State state);
    void formatChanged(const QAudioFormat& format);
    void sampleRateChanged(int sampleRate);
    void channelCountChanged(int numChannels);
    void deviceChanged(const QString& decive);
    void bufferDurationChanged(int duration);
    void supportedSampleRatesChanged(const QStringList&);
private:
    Q_DECLARE_PRIVATE(AudioRecorder)
    Q_DISABLE_COPY(AudioRecorder)
    AudioRecorderPrivate* d_ptr;
};
#endif // AUDIODEVICE_H
