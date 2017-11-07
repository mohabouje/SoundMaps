#ifndef DATAMODEL_H
#define DATAMODEL_H
#include "qbeacon.h"
#include <QMap>
#include <QObject>
#include <QQmlEngine>
#include <QSet>
class QEnvironement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float length READ length WRITE setLength NOTIFY lengthChanged)
    Q_PROPERTY(float width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(float height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int beaconsCount READ beaconsCount NOTIFY beaconsCountChanged)
public:
    explicit QEnvironement(QObject* parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    ~QEnvironement() override;
    inline QString name() const { return QString::fromStdString(environement->name()); }
    inline float length() const { return environement->length(); }
    inline float width() const { return environement->width(); }
    inline float height() const { return environement->height(); }
    inline int beaconsCount() const { return environement->beacons_size(); }
    inline const QSet<QBeaconPtr>& beacons() const { return beaconsSet; }
    bool removeBeacon(const QBeaconPtr& beaconAt);
    Q_INVOKABLE QBeaconPtr addBeacon();
    Q_INVOKABLE QBeaconPtr beaconAt(int index);
public slots:
    Q_INVOKABLE bool loadEnvironementFromFile(const QString& filename);
    Q_INVOKABLE bool saveEnvironementInFile(const QString& filename) const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE void init();
    void setName(const QString&);
    void setLength(float value);
    void setWidth(float value);
    void setHeight(float value);
signals:
    void lengthChanged(float);
    void widthChanged(float);
    void heightChanged(float);
    void nameChanged(const QString&);
    void beaconsCountChanged(int);
private:
    static constexpr float DefaultWidth{10.0};
    static constexpr float DefaultHeight{3.0};
    static constexpr float DefaultLength{10.0};
    Environement*               environement{new Environement};
    QSet<QBeaconPtr>            beaconsSet;
    QMap<QUuid, QBeaconPtr>     beaconsMap;
    SM_DECL_SINGLETON(QEnvironement)
};
#endif // DATAMODEL_H
