#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

class ComponentsManager;
class QPortAudioManager;

class AppDelegatePrivate;
class AppDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ComponentsManager* componentsManager READ componentsManager NOTIFY componentsManagerChanged)
    Q_PROPERTY(QPortAudioManager* audioManager READ audioManager WRITE setAudioManager NOTIFY audioManagerChanged)
public:
    explicit AppDelegate(QObject *parent = nullptr);
    virtual ~AppDelegate();
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
    ComponentsManager* componentsManager() const;
    QPortAudioManager *audioManager() const;
signals:
    void componentsManagerChanged(ComponentsManager*);
    void audioManagerChanged(QPortAudioManager*);
public slots:
    void setComponentsManager(ComponentsManager*);
    void setAudioManager(QPortAudioManager *value);
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    AppDelegatePrivate* d_ptr;
};

#endif // APPDELEGATE_H
