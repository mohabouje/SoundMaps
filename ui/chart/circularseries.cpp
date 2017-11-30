#include "circularseries.h"

CircularSeries::CircularSeries(QObject *parent) : ArraySeries (parent)
{

}

void CircularSeries::append(const QVector<double> &tmp) {
    Q_ASSERT_X(m_data.size() >= tmp.size(),
               __FUNCTION__,
               "Trying to append a buffer with a size higher than the current one");
    std::rotate(m_y.begin(), m_y.begin() + tmp.size(), m_y.end());
    std::copy(tmp.begin(), tmp.end(), m_y.end() - tmp.size());
}

void CircularSeries::append(const float *tmp, int size) {
    Q_ASSERT_X(m_data.size() >= size,
               __FUNCTION__,
               "Trying to append a buffer with a size higher than the current one");
    std::rotate(m_y.begin(), m_y.begin() + size, m_y.end());
    std::copy(tmp, tmp + size, m_y.end() - size);
}
