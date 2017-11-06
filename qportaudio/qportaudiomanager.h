#ifndef QPORTAUDIOMANAGER_H
#define QPORTAUDIOMANAGER_H

#include "components/circularbufferseries.h"
#include "qportaudiorecorder.h"

#include <QObject>
class QPortAudioManagerPrivate;
class QPortAudioManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(CircularBufferSeries* audioSeries READ audioSeries WRITE setAudioSeries NOTIFY audioSeriesChanged)
    Q_PROPERTY(QPortAudioRecorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
public:
    explicit QPortAudioManager(QObject *parent = nullptr);
    virtual ~QPortAudioManager();
    CircularBufferSeries *audioSeries() const;
    QPortAudioRecorder* recorder() const;
signals:
    void audioSeriesChanged(CircularBufferSeries*);
    void recorderChanged(QPortAudioRecorder*);
public slots:
    Q_INVOKABLE void reset();
    void setAudioSeries(CircularBufferSeries*);
    void setRecorder(QPortAudioRecorder*);
private:
    Q_DECLARE_PRIVATE(QPortAudioManager)
    Q_DISABLE_COPY(QPortAudioManager)
    QPortAudioManagerPrivate* d_ptr;
};

#endif // QPORTAUDIOMANAGER_H
