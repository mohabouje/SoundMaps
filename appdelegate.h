#ifndef APPDELEGATE_H
#define APPDELEGATE_H

#include <QObject>
#include <QQmlEngine>

#include "util/singletone.h"

class ComponentsManager;
class AudioManager;

class AppDelegatePrivate;
class AppDelegate : public QObject
{
    Q_OBJECT
public:
    explicit AppDelegate(QObject *parent = nullptr);
    virtual ~AppDelegate();
    static QObject* qmlSingleton(QQmlEngine* engine, QJSEngine *scriptEngine);
private:
    Q_DECLARE_PRIVATE(AppDelegate)
    Q_DISABLE_COPY(AppDelegate)
    SINGLETON_CREATOR(AppDelegate)
    AppDelegatePrivate* d_ptr{nullptr};
};

#endif // APPDELEGATE_H
