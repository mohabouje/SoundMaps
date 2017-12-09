#ifndef SPECTROGRAMSERIES_H
#define SPECTROGRAMSERIES_H

#include "arrayseries.h"

class Spectrogramseries : public ArraySeries {
    Q_OBJECT
public:
    explicit Spectrogramseries(QObject *parent = nullptr);
    void init() override;
    quint16 sampleRate() const { return m_samplerate; }
    void setSampleRate(quint16 _sr);
public slots:
    void set(const QVector<double> &tmp);
signals:
    void sampleRateChanged(quint16);
private:
    quint16 m_samplerate;
};

#endif // SPECTROGRAMSERIES_H
