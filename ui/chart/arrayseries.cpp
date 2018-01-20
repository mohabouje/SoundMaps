#include "arrayseries.h"
#include "sm_config.h"
ArraySeries::ArraySeries(QObject* parent)
    : QObject(parent)
{
}

void ArraySeries::setSize(int sz)
{
    if (sz != size()) {
        m_x.resize(sz);
        m_y.resize(sz);
        m_data.resize(sz);
        emit sizeChanged(sz);
    }
    init();
}

void ArraySeries::update()
{
    std::transform(std::begin(m_x), std::end(m_x), std::begin(m_y), std::begin(m_data),
        [](const double& x, const double& y) -> QPointF { return { x, y }; });
    m_series->replace(m_data);
}

void ArraySeries::setSeries(QXYSeries* series)
{
    if (series != m_series) {
        m_series = series;
        m_series->setUseOpenGL(m_useOpenGl);
        emit seriesChanged(m_series);
    }
    update();
}

void ArraySeries::setOpenGl(bool state)
{
    m_useOpenGl = state;
    if (m_series != nullptr) {
        m_series->setUseOpenGL(state);
    }
}

void ArraySeries::setAxisMinX(double value)
{
    if (!sm::float_compare(value, m_axisX.first)) {
        m_axisX.first = value;
        emit axisMinXChanged(m_axisX.first);
    }
}
void ArraySeries::setAxisMaxX(double value)
{
    if (!sm::float_compare(value, m_axisX.second)) {
        m_axisX.second = value;
        emit axisMinXChanged(m_axisX.second);
    }
}
void ArraySeries::setAxisMinY(double value)
{
    if (!sm::float_compare(value, m_axisY.first)) {
        m_axisY.first = value;
        emit axisMinXChanged(m_axisY.first);
    }
}
void ArraySeries::setAxisMaxY(double value)
{
    if (!sm::float_compare(value, m_axisY.second)) {
        m_axisY.second = value;
        emit axisMinXChanged(m_axisY.second);
    }
}
