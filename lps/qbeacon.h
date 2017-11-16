#ifndef QBEACON_H
#define QBEACON_H
#include "config.h"
#include "model.pb.h"
#include <QMetaType>
#include <QUuid>
#include <QSharedPointer>
#include <QVector3D>
class QBeacon : public QObject {
    Q_OBJECT
    Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
    Q_PROPERTY(quint32 id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(float snr READ snr WRITE setSnr NOTIFY snrChanged)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
public:
    explicit QBeacon(Beacon* beacon, QObject* parent = nullptr);
    virtual ~QBeacon();
    inline QUuid uuid() const {  return QUuid(QString::fromStdString(beacon->uuid())); }
    inline quint32 id() const { return beacon->id(); }
    inline QString name() const { return QString::fromStdString(beacon->name()); }
    inline float snr() const { return beacon->snr(); }
    inline bool state() const { return beacon->enabled();}
    inline QVector3D position() const { return QVector3D(beacon->x(), beacon->y(), beacon->z()); }
signals:
    void idChanged(quint32);
    void positionChanged(const QVector3D&);
    void uuidChanged(const QUuid&);
    void nameChanged(const QString&);
    void snrChanged(float);
    void stateChanged(bool);
public slots:
    void setPosition(const QVector3D& point);
    void setUuid(const QUuid& uuid);
    void setName(const QString &name);
    void setId(quint32 id);
    void setSnr(float SNR);
    void setState(bool state);
private:
    friend class QEnvironement;
    Beacon*         beacon;
    inline Beacon* pointer() const { return beacon; }
};
typedef QSharedPointer<QBeacon> QBeacon_ptr;
#endif // QBEACON_H
