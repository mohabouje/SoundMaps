#include "chartmanager.h"
#include "circularseries.h"
#include "spectrogramseries.h"

class ChartManagerPrivate : public QSharedData {
  Q_DISABLE_COPY(ChartManagerPrivate)
  Q_DECLARE_PUBLIC(ChartManager)
public:
  ChartManagerPrivate(ChartManager *ptr)
      : q_ptr(ptr), circularSeries(new CircularSeries(ptr)),
        spectrogramSeries(new SpectrogramSeries(ptr)) {}

  ChartManager *const q_ptr;
  ChartManager::RefreshRate rs{ChartManager::Low};
  CircularSeries *circularSeries{nullptr};
  SpectrogramSeries *spectrogramSeries{nullptr};
};

ChartManager::ChartManager(QObject *parent)
    : QObject(parent), d_ptr(new ChartManagerPrivate(this)) {
  qmlRegisterType<CircularSeries>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
                                  SM_PACKAGE_VERSION_MINOR, "CircularSeries");
  qmlRegisterType<SpectrogramSeries>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
                                     SM_PACKAGE_VERSION_MINOR,
                                     "SpectrogramSeries");
}

ChartManager::~ChartManager() { delete d_ptr; }

QObject *ChartManager::qmlSingleton(QQmlEngine *engine,
                                    QJSEngine *scriptEngine) {
  Q_UNUSED(engine);
  Q_UNUSED(scriptEngine);
  return SM_STATIC_SINGLETON(ChartManager);
}

SpectrogramSeries *ChartManager::spectrogramSeries() const {
  Q_D(const ChartManager);
  return d->spectrogramSeries;
}

CircularSeries *ChartManager::circularSeries() const {
  Q_D(const ChartManager);
  return d->circularSeries;
}

ChartManager::RefreshRate ChartManager::refreshRate() const {
  Q_D(const ChartManager);
  return d->rs;
}

void ChartManager::setRefreshRate(ChartManager::RefreshRate refresh) {
  Q_D(ChartManager);
  if (refresh != d->rs) {
    d->rs = refresh;
    emit refreshRateChanged(d->rs);
  }
}
