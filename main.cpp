#include <config.h>
#include "appdelegate.h"
#include "components/thememanager.h"
#include <QApplication>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);


    // Singletone Elements
    qmlRegisterSingletonType<AppDelegate>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AppDelegate", &AppDelegate::qmlSingleton);
    qmlRegisterSingletonType<ThemeManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ThemeManager", &ThemeManager::qmlSingleton);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
