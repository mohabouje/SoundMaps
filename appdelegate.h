#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

#include "config.h"
#include <audio/audiorecorder.h>
class AppDelegate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AppDelegate)
    Q_PROPERTY(AudioRecorder* audioRecorder READ audioRecorder WRITE setAudioRecorder NOTIFY audioRecorderChanged)
public:
    explicit AppDelegate(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
    AudioRecorder *audioRecorder() const;
signals:
    void audioRecorderChanged(AudioRecorder* audioRecorder);
public slots:
    void setAudioRecorder(AudioRecorder *audioRecorder);
protected:
    void setQmlEngine(QQmlEngine *qmlEngine);
    void setJsEngine(QJSEngine *jsEngine);
private:
    AudioRecorder*   _audioRecorder;
    QQmlEngine*      _qmlEngine{nullptr};
    QJSEngine*       _jsEngine{nullptr};
};

#endif // APPDELEGATE_H
