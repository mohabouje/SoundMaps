#include "thememanager.h"
#include <QColor>
#include <QSharedData>
class ThemeManagerPrivate : public QSharedData {
    Q_DISABLE_COPY(ThemeManagerPrivate)
    Q_DECLARE_PUBLIC(ThemeManager)
public:
    ThemeManagerPrivate(ThemeManager* ptr) : q_ptr(ptr) {

    }


    ThemeManager* const q_ptr;
    QColor  backgroundColor{Qt::red};
    QColor  foreGroundColor{Qt::darkGray};
    QColor  accentColor{Qt::red};
};

ThemeManager::ThemeManager(QObject *parent) : QObject(parent), d_ptr(new ThemeManagerPrivate(this)) {

}

ThemeManager::~ThemeManager()
{
    delete d_ptr;
}

QObject *ThemeManager::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return  new ThemeManager();
}

QColor ThemeManager::backgroundColor() const {
    Q_D(const ThemeManager);
    return  d->backgroundColor;
}

QColor ThemeManager::foregroundColor() const {
    Q_D(const ThemeManager);
    return  d->foreGroundColor;
}

QColor ThemeManager::accentColor() const {
    Q_D(const ThemeManager);
    return  d->accentColor;
}
