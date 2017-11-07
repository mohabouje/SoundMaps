#include "qbeacon.h"
#include <QDebug>

QBeacon::QBeacon(Beacon *beacon, QObject *parent) :
    QObject(parent),
    beacon(beacon) {

}

QBeacon::~QBeacon() {

}

void QBeacon::setPosition(const QVector3D &point) {
    if (point.x() != beacon->x()
            || point.y() != beacon->y()
            || point.z() != beacon->z()) {
        beacon->set_x(point.x());
        beacon->set_y(point.y());
        beacon->set_z(point.z());
        emit positionChanged(point);
    }
}

void QBeacon::setUuid(const QUuid &uuid) {
    const std::string tmp = uuid.toString().toStdString();
    if (tmp != beacon->uuid()) {
        beacon->set_uuid(tmp);
        emit uuidChanged(uuid);
    }
}

void QBeacon::setId(quint32 id) {
    if (id != beacon->id()) {
        beacon->set_id(id);
        emit idChanged(id);
    }
}

void QBeacon::setName(const QString &name) {
    const std::string tmp = name.toStdString();
    if (tmp != beacon->name()) {
        beacon->set_name(name.toStdString());
        emit nameChanged(name);
    }
}

void QBeacon::setSnr(float SNR) {
    if (SNR != beacon->snr()) {
        beacon->set_snr(SNR);
        emit snrChanged(SNR);
    }
}

void QBeacon::setState(bool state) {
    if (state != beacon->enabled()) {
        beacon->set_enabled(state);
        emit stateChanged(state);
    }
}
