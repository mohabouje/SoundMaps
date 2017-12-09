#include "spectrogramseries.h"
#include "eDSP/include/utility/vector.h"
SpectrogramSeries::SpectrogramSeries(QObject *parent) : ArraySeries (parent)
{

}

void SpectrogramSeries::init() {
    edsp::utility::set(std::begin(m_y), std::end(m_y), 0);
    edsp::utility::linspace(std::begin(m_x), std::end(m_x), 0, m_samplerate / 2);

    m_axisX = {m_x[0], m_x[m_x.size() - 1]};
    m_axisY = {0, 100};
    emit axisMinXChanged(m_axisX.first);
    emit axisMaxXChanged(m_axisY.second);
    emit axisMinYChanged(m_axisY.first);
    emit axisMaxYChanged(m_axisX.second);
}

void SpectrogramSeries::setSampleRate(double _sr) {
    if (_sr != m_samplerate) {
        m_samplerate = _sr;
        emit sampleRateChanged(m_samplerate);
    }
}

