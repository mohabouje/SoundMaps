#ifndef AUDIODATASOURCE_H
#define AUDIODATASOURCE_H

#include <QObject>
#include <QtCharts>
#include <QAbstractSeries>
QT_CHARTS_USE_NAMESPACE
class QPortAudioSeries : public QObject {
    Q_OBJECT
public:
    explicit QPortAudioSeries(QObject *parent = nullptr);
    Q_INVOKABLE void initialize(int sampleRate, int bufferInMSecs);
    Q_INVOKABLE void setSeries(QXYSeries *series);
    Q_INVOKABLE QXYSeries *series() const;
public slots:
    void appendBuffer(const QVector<double>& data);
    void appendBuffer(const float *data, ulong size);
    Q_INVOKABLE void update(QAbstractSeries *series);
    Q_INVOKABLE void update();
private:
    QVector<QPointF>     m_data{QVector<QPointF>(0)};
    QXYSeries *m_series;
};

#endif // AUDIODATASOURCE_H
