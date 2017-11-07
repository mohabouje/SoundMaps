#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include "config.h"

#include <QObject>
#include <QQmlEngine>
#include <QColor>
class ThemeManagerPrivate;
class ThemeManager : public QObject {
    Q_OBJECT
public:
    explicit ThemeManager(QObject *parent = nullptr);
    virtual ~ThemeManager();
    static QObject* qmlSingleton(QQmlEngine* engine = nullptr, QJSEngine *scriptEngine = nullptr);
    Q_INVOKABLE QColor backgroundColor() const;
    Q_INVOKABLE QColor foregroundColor() const;
    Q_INVOKABLE QColor accentColor() const;
private:
    Q_DECLARE_PRIVATE(ThemeManager)
    Q_DISABLE_COPY(ThemeManager)
    SM_DECL_SINGLETON(ThemeManager)
    ThemeManagerPrivate*    d_ptr;
};

#endif // THEMEMANAGER_H
