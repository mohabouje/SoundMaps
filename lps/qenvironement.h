#ifndef DATAMODEL_H
#define DATAMODEL_H
#include "qbeacon.h"
#include <QMap>
#include <QObject>
#include <QQmlEngine>
#include <QSet>
class QEnvironement : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
  Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
  Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
  Q_PROPERTY(int beaconsCount READ beaconsCount NOTIFY beaconsCountChanged)
public:
  explicit QEnvironement(QObject *parent = nullptr);
  static QObject *qmlSingleton(QQmlEngine *engine = nullptr,
                               QJSEngine *scriptEngine = nullptr);
  ~QEnvironement() override;
  inline QString name() const { return QString::fromStdString(environement->name()); }
  inline float length() const { return environement->length(); }
  inline float width() const { return environement->width(); }
  inline float height() const { return environement->height(); }
  inline int beaconsCount() const { return environement->beacons_size(); }
  inline const QSet<QBeacon_ptr> &beacons() const { return beaconsSet; }
  Q_INVOKABLE QBeacon_ptr beaconAt(int index);
public slots:
  Q_INVOKABLE bool loadEnvironementFromFile(const QString &filename);
  Q_INVOKABLE bool saveEnvironementInFile(const QString &filename) const;
  Q_INVOKABLE bool removeBeacon(const QBeacon_ptr &beaconAt);
  Q_INVOKABLE void clear();
  Q_INVOKABLE void init();
  Q_INVOKABLE QBeacon_ptr addBeacon();
  void setName(const QString &);
  void setLength(float value);
  void setWidth(float value);
  void setHeight(float value);
signals:
  void lengthChanged(float);
  void widthChanged(float);
  void heightChanged(float);
  void nameChanged(const QString &);
  void beaconsCountChanged(int);

private:
  static constexpr float DefaultWidth{10.0};
  static constexpr float DefaultHeight{3.0};
  static constexpr float DefaultLength{10.0};
  QScopedPointer<Environement> environement{new Environement};
  QSet<QBeacon_ptr> beaconsSet{};
  QHash<QUuid, QBeacon_ptr> beaconsMap{};
  SM_DECL_SINGLETON(QEnvironement)
};
#endif // DATAMODEL_H
