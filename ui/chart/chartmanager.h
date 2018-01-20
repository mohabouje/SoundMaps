#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include "sm_config.h"
#include "spectrogramseries.h"
#include "circularseries.h"


#include <QObject>
#include <QQmlEngine>
#include <QColor>

class ChartManagerPrivate;
class ChartManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(CircularSeries* circularSeries READ circularSeries NOTIFY circularSeriesChanged)
    Q_PROPERTY(SpectrogramSeries* spectrogramSeries READ spectrogramSeries NOTIFY spectrogramSeriesChanged)
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)

public:
    explicit ChartManager(QObject *parent = nullptr);
    virtual ~ChartManager();
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    enum RefreshRate { Low = 100, Medium = 50, Hight = 20};
    Q_ENUM(RefreshRate)

    SpectrogramSeries* spectrogramSeries() const;
    CircularSeries* circularSeries() const;
    RefreshRate refreshRate() const;
public slots:
    void setRefreshRate(RefreshRate);
signals:
    void refreshRateChanged(RefreshRate);
    void circularSeriesChanged(CircularSeries*);
    void spectrogramSeriesChanged(SpectrogramSeries*);
private:
    Q_DECLARE_PRIVATE(ChartManager)
    Q_DISABLE_COPY(ChartManager)
    SM_DECL_SINGLETON(ChartManager)
    SM_DECL_PIMPL(ChartManager)
};
#endif // CHARTMANAGER_H
