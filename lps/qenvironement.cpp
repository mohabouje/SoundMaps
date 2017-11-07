#include "qenvironement.h"
#include "modelhelper.h"

#include <sstream>
#include <QSaveFile>
#include <QFile>
#include <QDebug>

QEnvironement::QEnvironement(QObject *parent) : QObject (parent) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    environement->set_width(DefaultWidth);
    environement->set_height(DefaultHeight);
    environement->set_length(DefaultLength);
}

QObject *QEnvironement::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(QEnvironement);
}

QEnvironement::~QEnvironement() {
    clear();
    delete environement;
}

QBeaconPtr QEnvironement::addBeacon() {
    Beacon* beacon = environement->add_beacons();
    beacon->set_uuid(QUuid::createUuid().toString().toStdString());
    beacon->set_enabled(true);
    beacon->set_snr(0.f);
    beacon->set_x(0.f);
    beacon->set_y(0.f);
    beacon->set_z(0.f);
    beacon->set_id(static_cast<google::protobuf::uint32>(environement->beacons_size() - 1));

    Code* code = beacon->mutable_code();
    code->set_type(Code::Gold);
    code->set_order(10);

    emit beaconsCountChanged(environement->beacons_size());
    return beaconAt(static_cast<int>(beacon->id()));
}

bool QEnvironement::removeBeacon(const QBeaconPtr &beacon) {
    if (beacon) {
        QBeacon* pointer = qSharedPointerDynamicCast<QBeaconPtr>(beacon)->data();
        Q_UNUSED(pointer);
        return true;
    }
    return false;
}

QBeaconPtr QEnvironement::beaconAt(int index) {
    Beacon* beacon = environement->mutable_beacons(index);
    const QUuid uuid(QString::fromStdString(beacon->uuid()));
    if (beaconsMap.contains(uuid)) {
        return beaconsMap.value(uuid);
    }
    const QBeaconPtr shared(new QBeacon(beacon));
    beaconsMap.insert(uuid, shared);
    beaconsSet.insert(shared);
    return shared;
}

void QEnvironement::setLength(float value) {
    if (value != environement->length()) {
        environement->set_length(value);
        emit lengthChanged(value);
    }
}

void QEnvironement::setWidth(float value) {
    if (value != environement->width()) {
        environement->set_width(value);
        emit widthChanged(value);
    }
}

void QEnvironement::setHeight(float value) {
    if (value != environement->height()) {
        environement->set_height(value);
        emit heightChanged(value);
    }
}

void QEnvironement::clear() {
    environement->Clear();
    beaconsMap.clear();
    emit beaconsCountChanged(0);
}

void QEnvironement::setName(const QString &name) {
    const std::string tmp = name.toStdString();
    if (tmp != environement->name()) {
        environement->set_name(tmp);
        emit nameChanged(name);
    }
}

bool QEnvironement::loadEnvironementFromFile(const QString &filename) {
    static const QString defaultPath = ModelHelper::defaultDocumentsFolder() + ENVIRONEMENT_FILENAME;
    QFile file(filename.isEmpty() ? defaultPath : filename);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        const QByteArray array = file.readAll();
        file.close();
        if (!array.isEmpty()) {
            const bool succeded = environement->ParseFromArray(array.data(), array.size());
            emit beaconsCountChanged(environement->beacons_size());
            return succeded;
        }
    }
    return false;
}

bool QEnvironement::saveEnvironementInFile(const QString &filename) const {
    static const QString defaultPath = ModelHelper::defaultDocumentsFolder() + ENVIRONEMENT_FILENAME;
    QSaveFile file(filename.isEmpty() ? defaultPath : filename);
    if (file.open(QIODevice::WriteOnly)) {
        const QByteArray data(environement->SerializeAsString().c_str(), environement->ByteSize());
        if (file.write(data) > -1) {
            return file.commit();
        }
    }
    return false;
}




