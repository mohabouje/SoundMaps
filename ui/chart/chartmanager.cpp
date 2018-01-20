#include "chartmanager.h"
#include "circularbuffer.h"
#include "spectrogrambuffer.h"

class ChartManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(ChartManagerPrivate)
    Q_DECLARE_PUBLIC(ChartManager)
public:
    ChartManagerPrivate(ChartManager* ptr)
        : q_ptr(ptr)
    {
    }

    ChartManager* const q_ptr;
    QXYSeries* series{ nullptr };
    bool useOpenGl{ true };
    ChartManager::RefreshRate rs{ ChartManager::Low };
    ChartManager::ChartTypes type{ ChartManager::ChartTypes::WaveForm };
    QMap<ChartManager::ChartTypes, ArrayBuffer*> buffers{
        { ChartManager::WaveForm, new CircularBuffer },
        { ChartManager::Energy, new CircularBuffer },
        { ChartManager::Pitch, new CircularBuffer },
        { ChartManager::Spectrogram, new SpectrogramBuffer }
    };
};

ChartManager::ChartManager(QObject* parent)
    : QObject(parent)
    , d_ptr(new ChartManagerPrivate(this))
{
    qmlRegisterType<CircularBuffer>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
        SM_PACKAGE_VERSION_MINOR, "CircularBuffer");
    qmlRegisterType<SpectrogramBuffer>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
        SM_PACKAGE_VERSION_MINOR,
        "SpectrogramBuffer");
    qmlRegisterType<ArrayBuffer>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
        SM_PACKAGE_VERSION_MINOR,
        "ArrayBuffer");
}

ChartManager::~ChartManager() { delete d_ptr; }

QObject* ChartManager::qmlSingleton(QQmlEngine* engine,
    QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(ChartManager);
}

ArrayBuffer* ChartManager::bufferForType(ChartManager::ChartTypes type) const
{
    Q_D(const ChartManager);
    return d->buffers[type];
}

ArrayBuffer* ChartManager::currentBuffer() const
{
    Q_D(const ChartManager);
    return d->buffers[d->type];
}

ChartManager::RefreshRate ChartManager::refreshRate() const
{
    Q_D(const ChartManager);
    return d->rs;
}

ChartManager::ChartTypes ChartManager::type() const
{
    Q_D(const ChartManager);
    return d->type;
}

QXYSeries* ChartManager::series() const
{
    Q_D(const ChartManager);
    return d->series;
}

bool ChartManager::isOpenGlEnabled() const
{
    Q_D(const ChartManager);
    return d->useOpenGl;
}

void ChartManager::setRefreshRate(ChartManager::RefreshRate refresh)
{
    Q_D(ChartManager);
    if (refresh != d->rs) {
        d->rs = refresh;
        emit refreshRateChanged(d->rs);
    }
}

void ChartManager::setType(ChartManager::ChartTypes type)
{
    Q_D(ChartManager);
    if (d->type != type) {
        d->type = type;
        emit typeChanged(type);
        emit currentBufferChanged(d->buffers[d->type]);
    }
}

void ChartManager::setSeries(QXYSeries* series)
{
    Q_D(ChartManager);
    if (series != d->series) {
        d->series = series;
        d->series->setUseOpenGL(d->useOpenGl);
        emit seriesChanged(d->series);
    }
}

void ChartManager::setOpenGl(bool state)
{
    Q_D(ChartManager);
    if (d->useOpenGl != state) {
        d->series->setUseOpenGL(state);
        d->useOpenGl = state;
        emit
    }
}

void ChartManager::update()
{
    Q_D(ChartManager);
    d->buffers[d->type]->update(d->series);
}
