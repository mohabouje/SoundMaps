#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

class AudioRecorder;
class ComponentsManager;
class AppDelegatePrivate;
class AudioDataSource;
class AppDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AudioRecorder* audioRecorder READ audioRecorder NOTIFY audioRecorderChanged)
    Q_PROPERTY(AudioDataSource* audioDataSource READ audioDataSource WRITE setAudioDataSource NOTIFY audioDataSourceChanged)
    Q_PROPERTY(ComponentsManager* componentsManager READ componentsManager NOTIFY componentsManagerChanged)
public:
    explicit AppDelegate(QObject *parent = nullptr);
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
    AudioRecorder *audioRecorder() const;
    AudioDataSource *audioDataSource() const;
    ComponentsManager* componentsManager() const;
signals:
    void audioRecorderChanged(AudioRecorder*);
    void componentsManagerChanged(ComponentsManager*);
    void audioDataSourceChanged(AudioDataSource*);
public slots:
    void setAudioDataSource(AudioDataSource*);
    void setAudioRecorder(AudioRecorder*);
    void setComponentsManager(ComponentsManager*);
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    AppDelegatePrivate* d_ptr;
};

#endif // APPDELEGATE_H
