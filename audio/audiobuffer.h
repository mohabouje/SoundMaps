#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <QAudioFormat>
#include <QIODevice>
class AudioBufferPrivate;
class AudioBuffer : public QIODevice {
    Q_OBJECT
public:
    explicit AudioBuffer(QObject *parent = nullptr);
    ~AudioBuffer();
public slots:
    void start();
    void stop();
    void restart(int bufferInMsecs, const QAudioFormat& format);
signals:
    void bufferReady(const QVector<double> data);
protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
private:
    Q_DECLARE_PRIVATE(AudioBuffer)
    Q_DISABLE_COPY(AudioBuffer)
    AudioBufferPrivate* d_ptr;
};

#endif // AUDIOBUFFER_H
