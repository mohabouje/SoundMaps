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
        amplitude = maxAmplitudForFormat(format);
    }
    ~AudioBufferPrivate() {}


    inline void writeData(const char *data, qint64 len) {
        const int channelBytes = audioFormat.sampleSize() / 8;
        const int sampleBytes = audioFormat.channelCount() * channelBytes;
        const qint64 numSamples = len / sampleBytes;

        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j <audioFormat.channelCount(); ++j) {
                double value = 0;
                if (audioFormat.sampleSize() == 8 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                    value = static_cast<double>(*reinterpret_cast<const quint8*>(ptr));
                } else if (audioFormat.sampleSize() == 8 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                    value = static_cast<double>(*reinterpret_cast<const qint8*>(ptr));
                } else if (audioFormat.sampleSize() == 16 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                    value = static_cast<double>(qFromBigEndian<quint16>(ptr));
                } else if (audioFormat.sampleSize() == 16 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                    value = static_cast<double>(qFromBigEndian<qint16>(ptr));
                } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::UnSignedInt) {
                    value = static_cast<double>(qFromBigEndian<quint32>(ptr));
                } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::SignedInt) {
                    value = static_cast<double>(qFromBigEndian<qint32>(ptr));
                } else if (audioFormat.sampleSize() == 32 && audioFormat.sampleType() == QAudioFormat::Float) {
                    value = static_cast<double>(*reinterpret_cast<const float*>(ptr) * 0x7fffffff);
                }

                if (pos == audioBuffer.size()) {
                    Q_Q(AudioBuffer);
                    emit q->bufferReady(audioBuffer);
                    pos = 0;
                }

                audioBuffer[pos] = value;
                ptr += channelBytes;
                pos++;
            }
        }
    }



    inline qint32 maxAmplitudForFormat(const QAudioFormat& format) const {
        const int sampleSize = format.sampleSize();
        const QAudioFormat::SampleType sampleType = format.sampleType();
        switch (sampleSize) {
        case 8:
            switch (sampleType) {
            case QAudioFormat::UnSignedInt:
                return UCHAR_MAX;
            case QAudioFormat::SignedInt:
                return CHAR_MAX;
            default:
                return 0;
            }
        case 16:
            switch (sampleType) {
            case QAudioFormat::UnSignedInt:
                return USHRT_MAX;
            case QAudioFormat::SignedInt:
                return SHRT_MAX;
            default:
                return 0;
            }
        case 32:
            switch (sampleType) {
            case QAudioFormat::UnSignedInt:
                return UINT_MAX;
            case QAudioFormat::SignedInt:
                return INT_MAX;
            case QAudioFormat::Float:
                return 1;
            default:
                return 0;
            }
        default:
            return 0;
        }
    }

    AudioBuffer* const q_ptr;
    QVector<double> audioBuffer;
    QAudioFormat    audioFormat;
    qint32         amplitude{0};
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
