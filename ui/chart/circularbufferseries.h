#ifndef AUDIODATASOURCE_H
#define AUDIODATASOURCE_H

#include <QObject>
#include <QtCharts>
#include <QAbstractSeries>
QT_CHARTS_USE_NAMESPACE
class CircularBufferSeries : public QObject {
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
public:
    explicit CircularBufferSeries(QObject *parent = nullptr);
    inline int size() const { return m_data.size(); }
    inline QXYSeries *series() const { return m_series; }
public slots:
    void setSize(int size);
    void setSeries(QXYSeries *series);
    Q_INVOKABLE void appendBuffer(const QVector<double>& data);
    Q_INVOKABLE void appendBuffer(const float *data, ulong size);
    Q_INVOKABLE void update();
signals:
    void sizeChanged(int size);
    void seriesChanged(QXYSeries*);
private:
    QVector<QPointF>     m_data{QVector<QPointF>()};
    QXYSeries*           m_series{nullptr};
};

#endif // AUDIODATASOURCE_H
