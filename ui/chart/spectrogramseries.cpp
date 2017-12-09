#include "spectrogramseries.h"
#include "eDSP/include/utility/vector.h"
SpectrogramSeries::SpectrogramSeries(QObject *parent) : ArraySeries (parent)
{

}

void SpectrogramSeries::init() {
    eDSP::utility::set(std::begin(m_y), std::end(m_y), 0);
    eDSP::utility::linspace(std::begin(m_x), std::end(m_x), 0, m_samplerate / 2);
}

void SpectrogramSeries::setSampleRate(double _sr) {
    if (_sr != m_samplerate) {
        m_samplerate = _sr;
        emit sampleRateChanged(m_samplerate);
    }
}

void SpectrogramSeries::set(const QVector<double> &tmp) {
    Q_ASSERT_X(m_data.size() >= tmp.size(),
               __FUNCTION__,
               "Trying to append a buffer with a size higher than the current one");
    std::copy(std::begin(tmp), std::end(tmp), std::begin(m_y));
}
