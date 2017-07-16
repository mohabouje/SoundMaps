#include "audiobuffer.h"
#include <stdint.h>
#include <float.h>
#include <memory>
#include <QDebug>
#include <qendian.h>
class AudioBufferPrivate : public QSharedData {
    Q_DISABLE_COPY(AudioBufferPrivate)
    Q_DECLARE_PUBLIC(AudioBuffer)
public:
    AudioBufferPrivate(int bufferSamples, const QAudioFormat& format, AudioBuffer* buffer) :
        q_ptr(buffer),
        audioBuffer(QVector<double>(bufferSamples, 0)),
        audioFormat(format)
    {
    }
    ~AudioBufferPrivate() {}


    inline void writeData(const char *data, qint64 len) {
        const int sampleBytes = audioFormat.sampleSize() / 8;
        const qint64 numSamples = len / sampleBytes;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
        for (int i = 0; i < numSamples; ++i) {
            if (pos == audioBuffer.size()) {
                Q_Q(AudioBuffer);
                emit q->bufferReady(audioBuffer);
                pos = 0;
            }

            audioBuffer[pos] = static_cast<double>(*reinterpret_cast<const float*>(ptr));
            ptr += sampleBytes;
            pos++;
        }
    }

    AudioBuffer* const q_ptr;
    QVector<double> audioBuffer;
    QAudioFormat    audioFormat;
    int            pos{0};
};

AudioBuffer::AudioBuffer(int bufferSize, const QAudioFormat& format, QObject *parent) :
    QIODevice (parent),
    d_ptr(new AudioBufferPrivate(bufferSize, format, this))
{
}

AudioBuffer::~AudioBuffer() {

}

void AudioBuffer::start() {
    open(QIODevice::WriteOnly);
}

void AudioBuffer::stop() {
    close();
}

qint64 AudioBuffer::readData(char *data, qint64 maxlen) {
    Q_UNUSED(data);
    Q_UNUSED(maxlen);
    return -1;
}

qint64 AudioBuffer::writeData(const char *data, qint64 len) {
    Q_D(AudioBuffer);
    d->writeData(data, len);
    return len;
}
