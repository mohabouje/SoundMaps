#include "arraybuffer.h"
#include "sm_config.h"
ArrayBuffer::ArrayBuffer(QObject* parent)
    : QObject(parent)
{
}

void ArrayBuffer::setSize(int sz)
{
    if (sz != size()) {
        m_x.resize(sz);
        m_y.resize(sz);
        m_data.resize(sz);
        emit sizeChanged(sz);
    }
    init();
}

void ArrayBuffer::update(QXYSeries* series)
{
    std::transform(std::begin(m_x), std::end(m_x), std::begin(m_y), std::begin(m_data),
        [](const double& x, const double& y) -> QPointF { return { x, y }; });
    series->replace(m_data);
}

void ArrayBuffer::setAxisMinX(double value)
{
    if (!sm::float_compare(value, m_axisX.first)) {
        m_axisX.first = value;
        emit axisMinXChanged(m_axisX.first);
    }
}
void ArrayBuffer::setAxisMaxX(double value)
{
    if (!sm::float_compare(value, m_axisX.second)) {
        m_axisX.second = value;
        emit axisMinXChanged(m_axisX.second);
    }
}
void ArrayBuffer::setAxisMinY(double value)
{
    if (!sm::float_compare(value, m_axisY.first)) {
        m_axisY.first = value;
        emit axisMinXChanged(m_axisY.first);
    }
}
void ArrayBuffer::setAxisMaxY(double value)
{
    if (!sm::float_compare(value, m_axisY.second)) {
        m_axisY.second = value;
        emit axisMinXChanged(m_axisY.second);
    }
}
