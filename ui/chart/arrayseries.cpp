#include "arrayseries.h"
#include "eDSP/include/utility/vector.h"
ArraySeries::ArraySeries(QObject *parent) : QObject (parent)
{

}

void ArraySeries::init() {
    eDSP::utility::set(std::begin(m_y), std::end(m_y), 0);
    eDSP::utility::linspace(std::begin(m_x), std::end(m_x), 0, m_x.size());
}

void ArraySeries::setSize(int sz) {
    if (sz != size()) {
        m_x.resize(sz);
        m_y.resize(sz);
        m_data.resize(sz);
        init();
        emit sizeChanged(sz);
    }
}

void ArraySeries::update() {
    std::transform(std::begin(m_x), std::end(m_x), std::begin(m_y), std::begin(m_data),
                   [](double& x, double& y) -> QPointF {
                        return QPointF(x,y);
    });

    m_series->replace(m_data);
}

void ArraySeries::setSeries(QXYSeries* series) {
    m_series = series;
    update();
}
