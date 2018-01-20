#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>
#include <eDSP/include/frequency/spectrogram.h>

#include "sm_config.h"

class ComponentsManager;
class AudioManager;
class AppDelegatePrivate;
class AppDelegate : public QObject
{
    Q_OBJECT
public:
    explicit AppDelegate(QObject *parent = nullptr);
    virtual ~AppDelegate();
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
public slots:
    void initUi();
    void initAudioSystem();
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    SM_DECL_SINGLETON(AppDelegate)
    SM_DECL_PIMPL(AppDelegate)
};

#endif // APPDELEGATE_H
