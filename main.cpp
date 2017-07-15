#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <config.h>
#include "appdelegate.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    // Singletone Elements
    qmlRegisterSingletonType<AppDelegate>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AppDelegate", &AppDelegate::qmlSingleton);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.addImportPath("qrc:///");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
