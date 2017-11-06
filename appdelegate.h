#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

class ComponentsManager;
class AudioManager;

class AppDelegatePrivate;
class AppDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ComponentsManager* componentsManager READ componentsManager NOTIFY componentsManagerChanged)
    Q_PROPERTY(AudioManager* audioManager READ audioManager WRITE setAudioManager NOTIFY audioManagerChanged)
public:
    explicit AppDelegate(QObject *parent = nullptr);
    virtual ~AppDelegate();
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
    ComponentsManager* componentsManager() const;
    AudioManager *audioManager() const;
signals:
    void componentsManagerChanged(ComponentsManager*);
    void audioManagerChanged(AudioManager*);
public slots:
    void setComponentsManager(ComponentsManager*);
    void setAudioManager(AudioManager *value);
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    static AppDelegate* instance;
    AppDelegatePrivate* d_ptr{nullptr};
};

#endif // APPDELEGATE_H
