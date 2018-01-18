#ifndef QPORTAUDIOMANAGER_H
#define QPORTAUDIOMANAGER_H

#include "audiorecorder.h"
#include "sm_config.h"

#include <QObject>
#include <QQmlEngine>
class AudioManagerPrivate;
class AudioManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(AudioRecorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
public:
    explicit AudioManager(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    virtual ~AudioManager();
    AudioRecorder* recorder() const;
signals:
    void recorderChanged(AudioRecorder*);
public slots:
    Q_INVOKABLE void reset();
    void setRecorder(AudioRecorder*);
private:
    Q_DECLARE_PRIVATE(AudioManager)
    Q_DISABLE_COPY(AudioManager)
    SM_DECL_SINGLETON(AudioManager)
    SM_PIMPL_PTR(AudioManager)
};

#endif // QPORTAUDIOMANAGER_H
