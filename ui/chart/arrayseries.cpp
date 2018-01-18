#include "arrayseries.h"
ArraySeries::ArraySeries(QObject *parent) : QObject (parent)
{

}

void ArraySeries::setSize(int sz) {
    if (sz != size()) {
        m_x.resize(sz);
        m_y.resize(sz);
        m_data.resize(sz);
        emit sizeChanged(sz);
    }
    init();
}

void ArraySeries::update() {
    std::transform(std::begin(m_x), std::end(m_x), std::begin(m_y), std::begin(m_data),
                   [](const double& x, const double& y) -> QPointF { return {x,y}; });
    m_series->replace(m_data);
}

void ArraySeries::setSeries(QXYSeries* series) {
    m_series = series;
    m_series->setUseOpenGL(true);
    update();
}
