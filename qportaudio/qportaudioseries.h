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
    void initialize(int sampleRate, int bufferInMSecs);
public slots:
    void appendBuffer(const QVector<double>& data);
    void appendBuffer(const float *data, ulong size);
    Q_INVOKABLE void update(QAbstractSeries *series);
private:
    QVector<QPointF>     m_data;
};

#endif // AUDIODATASOURCE_H
