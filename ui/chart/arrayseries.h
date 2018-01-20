#ifndef ARRAYLINESERIES_H
#define ARRAYLINESERIES_H

#include <QObject>
#include <QPair>
#include <QVector>
#include <QXYSeries>
QT_CHARTS_USE_NAMESPACE

using AxisLimit = QPair<double, double>;
class ArraySeriesPrivate;
class ArraySeries : public QObject {
    Q_OBJECT
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(double axisMinX READ axisMinX WRITE setAxisMinX NOTIFY axisMinXChanged)
    Q_PROPERTY(double axisMinY READ axisMinY WRITE setAxisMaxX NOTIFY axisMinYChanged)
    Q_PROPERTY(double axisMaxX READ axisMaxX WRITE setAxisMinY NOTIFY axisMaxXChanged)
    Q_PROPERTY(double axisMaxY READ axisMaxY WRITE setAxisMaxY NOTIFY axisMaxYChanged)
    Q_PROPERTY(QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
public:
    explicit ArraySeries(QObject* parent = nullptr);
    inline const QVector<double>& x() const { return m_x; }
    inline const QVector<double>& y() const { return m_y; }
    inline bool isInitialized() const { return m_series != nullptr; }
    inline int size() { return m_data.size(); }
    inline double axisMinX() const { return m_axisX.first; }
    inline double axisMinY() const { return m_axisY.first; }
    inline double axisMaxX() const { return m_axisX.second; }
    inline double axisMaxY() const { return m_axisY.second; }
    inline QXYSeries* series() const { return m_series; }
public slots:
    Q_INVOKABLE void update();
    void setSize(int size);
    void setSeries(QXYSeries*);
    void setOpenGl(bool state);
    void setAxisMinX(double value);
    void setAxisMaxX(double value);
    void setAxisMinY(double value);
    void setAxisMaxY(double value);
signals:
    void axisMinXChanged(double);
    void axisMinYChanged(double);
    void axisMaxXChanged(double);
    void axisMaxYChanged(double);
    void sizeChanged(double);
    void seriesChanged(QXYSeries*);

protected:
    virtual void init() = 0;
    bool m_useOpenGl{ true };
    QXYSeries* m_series{ nullptr };
    QVector<double> m_x{};
    QVector<double> m_y{};
    QVector<QPointF> m_data{};
    QPair<double, double> m_axisX{};
    QPair<double, double> m_axisY{};
};

Q_DECLARE_METATYPE(AxisLimit);
#endif // ARRAYLINESERIES_H
