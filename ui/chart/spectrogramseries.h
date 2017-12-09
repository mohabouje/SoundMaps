#ifndef SPECTROGRAMSERIES_H
#define SPECTROGRAMSERIES_H

#include "arrayseries.h"

class SpectrogramSeries : public ArraySeries {
    Q_OBJECT
    Q_PROPERTY(double sampleRate READ sampleRate WRITE setSampleRate NOTIFY sampleRateChanged)
public:
    explicit SpectrogramSeries(QObject *parent = nullptr);
    double sampleRate() const { return m_samplerate; }
    void setSampleRate(double _sr);
public slots:
    void set(const QVector<double> &tmp);
signals:
    void sampleRateChanged(double);
protected:
    void init() override;
    double m_samplerate;
};

#endif // SPECTROGRAMSERIES_H
