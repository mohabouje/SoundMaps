#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include "circularbuffer.h"
#include "sm_config.h"
#include "spectrogrambuffer.h"

#include <QColor>
#include <QObject>
#include <QQmlEngine>

class ChartManagerPrivate;
class ChartManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
    Q_PROPERTY(ArrayBuffer* currentBuffer READ currentBuffer NOTIFY currentBufferChanged)
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
    Q_PROPERTY(ChartTypes type READ type WRITE setType NOTIFY typeChanged)
public:
    explicit ChartManager(QObject* parent = nullptr);
    virtual ~ChartManager();
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine* scriptEngine = nullptr);
    enum RefreshRate { Low = 100,
        Medium = 50,
        Hight = 20 };
    Q_ENUM(RefreshRate)

    enum ChartTypes {
        WaveForm = 0,
        Energy,
        Pitch,
        Spectrogram
    };
    Q_ENUM(ChartTypes)

    ArrayBuffer* bufferForType(ChartTypes) const;
    ArrayBuffer* currentBuffer() const;

    RefreshRate refreshRate() const;
    ChartTypes type() const;
    QXYSeries* series() const;
    bool isOpenGlEnabled() const;
public slots:
    void setRefreshRate(RefreshRate);
    void setType(ChartTypes);
    void setSeries(QXYSeries*);
    void setOpenGl(bool);
    Q_INVOKABLE void update();
signals:
    void refreshRateChanged(RefreshRate);
    void seriesChanged(QXYSeries*);
    void typeChanged(ChartTypes);
    void currentBufferChanged(ArrayBuffer*);

private:
    Q_DECLARE_PRIVATE(ChartManager)
    Q_DISABLE_COPY(ChartManager)
    SM_DECL_SINGLETON(ChartManager)
    SM_DECL_PIMPL(ChartManager)
};
#endif // CHARTMANAGER_H
