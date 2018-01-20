#ifndef CircularBuffer_H
#define CircularBuffer_H

#include "arraybuffer.h"

class CircularBuffer : public ArrayBuffer {
    Q_OBJECT
public:
    explicit CircularBuffer(QObject* parent = nullptr);

    template <class ForwardIterator, typename = std::enable_if<std::is_same<typename std::iterator_traits<ForwardIterator>::value_type, double>::value>>
    void set(const ForwardIterator first, const ForwardIterator last)
    {
        const auto size = std::distance(first, last);
        std::rotate(m_y.begin(), m_y.begin() + size, m_y.end());
        std::copy(first, last, m_y.end() - size);
    }

protected:
    void init() override;
};

#endif // CircularBuffer_H
