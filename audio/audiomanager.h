#ifndef QPORTAUDIOMANAGER_H
#define QPORTAUDIOMANAGER_H

#include "ui/chart/circularbufferseries.h"
#include "audiorecorder.h"
#include "config.h"

#include <QObject>
#include <QQmlEngine>
class AudioManagerPrivate;
class AudioManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(CircularBufferSeries* audioSeries READ audioSeries WRITE setAudioSeries NOTIFY audioSeriesChanged)
    Q_PROPERTY(AudioRecorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
public:
    explicit AudioManager(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    virtual ~AudioManager();
    CircularBufferSeries *audioSeries() const;
    AudioRecorder* recorder() const;
signals:
    void audioSeriesChanged(CircularBufferSeries*);
    void recorderChanged(AudioRecorder*);
public slots:
    Q_INVOKABLE void reset();
    void setAudioSeries(CircularBufferSeries*);
    void setRecorder(AudioRecorder*);
private:
    Q_DECLARE_PRIVATE(AudioManager)
    Q_DISABLE_COPY(AudioManager)
    SM_DECL_SINGLETON(AudioManager)
    AudioManagerPrivate* d_ptr;
};

#endif // QPORTAUDIOMANAGER_H