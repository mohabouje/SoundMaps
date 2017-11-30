#ifndef ARRAYLINESERIES_H
#define ARRAYLINESERIES_H

#include <QXYSeries>
#include <QVector>
#include <QObject>
QT_CHARTS_USE_NAMESPACE

class ArraySeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
public:
    explicit ArraySeries(QObject *parent = nullptr);
    virtual void init();
    void setSize(int size);
    int size() { return m_data.size(); }
    const QVector<double>& x() const { return m_x; }
    const QVector<double>& y() const { return m_y; }  
    Q_INVOKABLE void update();
    Q_INVOKABLE void setSeries(QXYSeries*);
signals:
    void sizeChanged(int);
protected:
    QVector<double> m_x;
    QVector<double> m_y;
    QVector<QPointF> m_data;
    QXYSeries*       m_series;
};
#endif // ARRAYLINESERIES_H
