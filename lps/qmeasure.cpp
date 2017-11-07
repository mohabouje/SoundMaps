#include "qmeasure.h"
QMeasure::QMeasure(const QMeasure &measure) :
    m_beacon(measure.m_beacon),
    m_measure(measure.m_measure),
    m_rssi(measure.m_rssi)
{
}

QMeasure QMeasure::createMeasure(const QBeaconPtr& beacon, float distance, float rssi) {
    QMeasure measure;
    measure.setBeacon(beacon);
    measure.setMeasure(distance);
    measure.setRSSI(rssi);
    return measure;
}

void QMeasure::setBeacon(const QBeaconPtr& beacon) {
    Q_ASSERT_X(!beacon.isNull(), __FUNCTION__, "Error: null ptr for measure");
    m_beacon = beacon;
}

void QMeasure::setMeasure(float measure) {
    Q_ASSERT_X(measure > 0, __FUNCTION__, "Error: negative measure estimated");
    m_measure = measure;
}

void QMeasure::setRSSI(float rssi) {
    m_rssi = rssi;
}
