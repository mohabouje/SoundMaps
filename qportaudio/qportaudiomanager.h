#ifndef QPORTAUDIOMANAGER_H
#define QPORTAUDIOMANAGER_H

#include "qportaudioseries.h"
#include "qportaudiorecorder.h"

#include <QObject>
class QPortAudioManagerPrivate;
class QPortAudioManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QPortAudioSeries* audioSeries READ audioSeries WRITE setAudioSeries NOTIFY audioSeriesChanged)
    Q_PROPERTY(QPortAudioRecorder* recorder READ recorder WRITE setRecorder NOTIFY recorderChanged)
public:
    explicit QPortAudioManager(QObject *parent = nullptr);
    virtual ~QPortAudioManager();
    QPortAudioSeries *audioSeries() const;
    QPortAudioRecorder* recorder() const;
signals:
    void audioSeriesChanged(QPortAudioSeries*);
    void recorderChanged(QPortAudioRecorder*);
public slots:
    Q_INVOKABLE void reset();
    void setAudioSeries(QPortAudioSeries*);
    void setRecorder(QPortAudioRecorder*);
private:
    Q_DECLARE_PRIVATE(QPortAudioManager)
    Q_DISABLE_COPY(QPortAudioManager)
    QPortAudioManagerPrivate* d_ptr;
};

#endif // QPORTAUDIOMANAGER_H
