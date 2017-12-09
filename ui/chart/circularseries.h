#ifndef CIRCULARSERIES_H
#define CIRCULARSERIES_H

#include "arrayseries.h"

class CircularSeries : public ArraySeries
{
    Q_OBJECT
public:
    explicit CircularSeries(QObject *parent = nullptr);

    template<class ForwardIterator>
    void set(const ForwardIterator first, const ForwardIterator last) {
        const auto size = std::distance(first, last);
        std::rotate(m_y.begin(), m_y.begin() + size, m_y.end());
        std::copy(first, last, m_y.end() - size);
    }
protected:
    void init() override;
};

#endif // CIRCULARSERIES_H
