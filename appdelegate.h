#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

class AudioRecorder;
class AppDelegatePrivate;
class AppDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AudioRecorder* audioRecorder READ audioRecorder NOTIFY audioRecorderChanged)
public:
    explicit AppDelegate(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
    AudioRecorder *audioRecorder() const;
signals:
    void audioRecorderChanged(AudioRecorder* audioRecorder);
public slots:
    void setAudioRecorder(AudioRecorder *audioRecorder);
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    AppDelegatePrivate* d_ptr;
};

#endif // APPDELEGATE_H
