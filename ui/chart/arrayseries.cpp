#include "arrayseries.h"

ArraySeries::ArraySeries(QObject *parent) : QObject (parent)
{

}

void ArraySeries::init() {
    std::fill(m_y.begin(), m_y.end(), 0);
    for (int i = 0, size = m_x.size(); i < size; ++i) {
        m_x[i] = i;
    }
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

template <class Container>
Container down_sampling(const Container& input, std::size_t OUT) {
    Container res(OUT);
    auto IN = input.size();
    for (std::size_t i = 0; i != OUT - 1; ++i) {
        auto index = i * (IN - 1) / (OUT - 1);
        auto p = i * (IN - 1) % (OUT - 1);
        res[i] = ((p * input[index + 1]) + (((OUT - 1) - p) * input[index])) / (OUT - 1);
    }
    res[OUT - 1] = input[IN - 1]; // done outside of loop to avoid out of bound access (0 * a[IN])
    return res;
}

template <class Container>
Container linspace(typename Container::value_type const& start,
                   typename Container::value_type const& end,
                   std::size_t N) {
    Container tmp (N);
    typename Container::value_type val = start, increment = (end - start) / static_cast<typename Container::value_type>(N);
    for (typename Container::iterator it = tmp.begin(), until = tmp.end();
         it != until; ++it, val += increment) {
        *it = val;
    }
    return tmp;
}


void ArraySeries::update() {
    std::transform(m_x.begin(), m_x.end(), m_y.begin(), m_data.begin(),
                   [](double x, double y) -> QPointF {
                        return QPointF(x,y);
    });

    m_series->replace(m_data);

    linspace<QVector<double>>(0, 100, 9);
}

void ArraySeries::setSeries(QXYSeries* series) {
    m_series = series;
    update();
}
