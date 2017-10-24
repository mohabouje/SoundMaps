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
    Q_PROPERTY(RefreshRate refreshRate READ refreshRate WRITE setRefreshRate NOTIFY refreshRateChanged)
public:
    explicit QPortAudioManager(QObject *parent = nullptr);
    enum RefreshRate { Low, Medium, Hight};
    Q_ENUM(RefreshRate)

    virtual ~QPortAudioManager();
    QPortAudioSeries *audioSeries() const;
    QPortAudioRecorder* recorder() const;
    RefreshRate refreshRate() const;
signals:
    void audioSeriesChanged(QPortAudioSeries*);
    void recorderChanged(QPortAudioRecorder*);
    void refreshRateChanged(RefreshRate);
public slots:
    void setAudioSeries(QPortAudioSeries*);
    void setRecorder(QPortAudioRecorder*);
    void setRefreshRate(RefreshRate);
private:
    Q_DECLARE_PRIVATE(QPortAudioManager)
    Q_DISABLE_COPY(QPortAudioManager)
    QPortAudioManagerPrivate* d_ptr;
};

#endif // QPORTAUDIOMANAGER_H
