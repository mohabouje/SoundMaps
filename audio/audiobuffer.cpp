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
    AudioBufferPrivate(AudioBuffer* buffer) :
        q_ptr(buffer)
    {
    }
    ~AudioBufferPrivate() {}

    void reset(int bufferInMsecs, const QAudioFormat& format) {
        audioBuffer = QVector<double>(bufferInMsecs * format.sampleRate() / 1000, 0);
        audioFormat = format;
        pos = 0;
    }


    inline void writeData(const char *data, qint64 len) {
        Q_ASSERT_X(audioFormat.channelCount() == 1, __FUNCTION__, "Max allowed channel count: 1");
        Q_ASSERT_X(audioFormat.sampleType() == QAudioFormat::Float, __FUNCTION__, "Only float format supported");
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

AudioBuffer::AudioBuffer(QObject *parent) :
    QIODevice (parent),
    d_ptr(new AudioBufferPrivate(this))
{
}

AudioBuffer::~AudioBuffer() {

}

void AudioBuffer::start() {
    if (!QIODevice::open(QIODevice::WriteOnly)) {
        qCritical() << "Could not open the audio buffer input device";
    }
}

void AudioBuffer::stop() {
    QIODevice::close();
}

void AudioBuffer::restart(int bufferInMsecs, const QAudioFormat &format) {
    Q_D(AudioBuffer);
    if (isOpen()) { stop(); }
    d->reset(bufferInMsecs, format);
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
