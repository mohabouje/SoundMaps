#ifndef SpectrogramBuffer_H
#define SpectrogramBuffer_H

#include "arraybuffer.h"
#include <type_traits>

class SpectrogramBuffer : public ArrayBuffer {
    Q_OBJECT
    Q_PROPERTY(double sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
public:
    explicit SpectrogramBuffer(QObject* parent = nullptr);
    double sampleRate() const { return m_samplerate; }
    void setSampleRate(double _sr);

    template <class ForwardIterator, typename = std::enable_if<std::is_same<typename std::iterator_traits<ForwardIterator>::value_type, double>::value>>
    void set(const ForwardIterator first, const ForwardIterator last)
    {
        std::copy(first, last, std::begin(m_y));
    }
signals:
    void sampleRateChanged(double);

protected:
    void init() override;
    double m_samplerate;
};

#endif // SpectrogramBuffer_H
