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
            float value = 0;
            if (audioFormat.sampleSize() == 8 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                value = static_cast<float>(*reinterpret_cast<const quint8*>(ptr));
            } else if (audioFormat.sampleSize() == 8 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                value = static_cast<float>(*reinterpret_cast<const qint8*>(ptr));
            } else if (audioFormat.sampleSize() == 16 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                value = static_cast<float>(qFromBigEndian<quint16>(ptr));
            } else if (audioFormat.sampleSize() == 16 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                value = static_cast<float>(qFromBigEndian<qint16>(ptr));
            } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                value = static_cast<float>(qFromBigEndian<quint32>(ptr));
            } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                value = static_cast<float>(qFromBigEndian<qint32>(ptr));
            } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::Float) {
                value = *reinterpret_cast<const float*>(ptr);
            }

            if (pos == audioBuffer.size()) {
                Q_Q(AudioBuffer);
                emit q->bufferReady(audioBuffer);
                pos = 0;
            }

            audioBuffer[pos] = value;
            ptr += sampleBytes;
            pos++;
            qWarning() << value << value / INT32_MAX;
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
    connect(this, &AudioBuffer::bufferReady, [&](const QVector<double> data){
    });
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
