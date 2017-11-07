#ifndef QMEASURE_H
#define QMEASURE_H
#include "config.h"
#include "qbeacon.h"
#include <QMetaType>
class QMeasure  {
public:
    static QMeasure createMeasure(const QBeaconPtr& beacon, float distance, float rssi);
    QMeasure() = default;
    QMeasure(const QMeasure& measure);
    ~QMeasure() = default;
    inline QBeaconPtr beacon() const { return m_beacon; }
    inline float measure() const { return m_measure; }
    inline float rssi() const { return m_rssi; }
    inline bool operator<(const QMeasure& entry) const {
        return m_measure < entry.m_measure;
    }
    inline bool operator>(const QMeasure& entry) const {
        return !(*this < entry);
    }
    inline bool operator==(const QMeasure& entry) const {
        return (m_beacon->id() == entry.m_beacon->id())
                && m_measure == entry.m_measure
                && m_rssi == entry.m_rssi;
    }
    inline bool operator!=(const QMeasure& entry) const {
        return !(*this == entry);
    }
    void setBeacon(const QBeaconPtr& beacon);
    void setMeasure(float measure);
    void setRSSI(float rssi);
private:
    QBeaconPtr       m_beacon{nullptr};
    float            m_measure{0.f};
    float            m_rssi{0.f};
};

inline uint qHash(const QMeasure &f) {
    return qHash(f.beacon()->uuid());
}
Q_DECLARE_METATYPE(QMeasure)
#endif // QMEASURE_H
