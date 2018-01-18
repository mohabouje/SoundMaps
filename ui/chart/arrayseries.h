#ifndef ARRAYLINESERIES_H
#define ARRAYLINESERIES_H

#include <QXYSeries>
#include <QVector>
#include <QObject>
#include <QPair>
QT_CHARTS_USE_NAMESPACE

using AxisLimit = QPair<double, double>;
class ArraySeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(double axisMinX READ axisMinX NOTIFY axisMinXChanged)
    Q_PROPERTY(double axisMinY READ axisMinY NOTIFY axisMinYChanged)
    Q_PROPERTY(double axisMaxX READ axisMaxX NOTIFY axisMaxXChanged)
    Q_PROPERTY(double axisMaxY READ axisMaxY NOTIFY axisMaxYChanged)
public:
    explicit ArraySeries(QObject *parent = nullptr);
    inline bool isInitialized() const { return m_series != nullptr; }
    inline int size() { return m_data.size(); }
    inline const QVector<double>& x() const { return m_x; }
    inline const QVector<double>& y() const { return m_y; }
    inline double axisMinX() const { return m_axisX.first; }
    inline double axisMinY() const { return m_axisY.first; }
    inline double axisMaxX() const { return m_axisX.second; }
    inline double axisMaxY() const { return m_axisY.second; }
public slots:
    void setSize(int size);
    Q_INVOKABLE void update();
    Q_INVOKABLE void setSeries(QXYSeries*);
signals:
    void axisMinXChanged(double);
    void axisMinYChanged(double);
    void axisMaxXChanged(double);
    void axisMaxYChanged(double);
    void sizeChanged(double);
protected:
    virtual void init() = 0;
    QXYSeries*       m_series{nullptr};
    QVector<double> m_x{};
    QVector<double> m_y{};
    QVector<QPointF> m_data{};
    QPair<double, double> m_axisX{};
    QPair<double, double> m_axisY{};
};

Q_DECLARE_METATYPE(AxisLimit);
#endif // ARRAYLINESERIES_H
