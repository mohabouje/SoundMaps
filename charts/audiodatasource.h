#ifndef AUDIODATASOURCE_H
#define AUDIODATASOURCE_H

#include <QObject>
#include <QtCharts>
#include <QAbstractSeries>
QT_CHARTS_USE_NAMESPACE
class AudioDataSource : public QObject {
    Q_OBJECT
public:
    explicit AudioDataSource(QObject *parent = nullptr);
public slots:
    void initialize(int sampleRate, int bufferInMSecs);
    void appendBuffer(const QVector<double>& data);
    Q_INVOKABLE void update(QAbstractSeries *series);
private:
    QVector<QPointF>     m_data;
};

#endif // AUDIODATASOURCE_H
