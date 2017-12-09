#include "circularseries.h"
#include "eDSP/include/utility/vector.h"

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

void CircularSeries::init() {
    eDSP::utility::set(std::begin(m_y), std::end(m_y), 0);
    eDSP::utility::linspace(std::begin(m_x), std::end(m_x), 0, m_x.size());

    m_axisX = {m_x[0], m_x[m_x.size() - 1]};
    m_axisY = {-1, 1};
    emit axisMinXChanged(m_axisX.first);
    emit axisMaxXChanged(m_axisY.second);
    emit axisMinYChanged(m_axisY.first);
    emit axisMaxYChanged(m_axisX.second);
}
