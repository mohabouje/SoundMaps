#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <config.h>
#include <tabbarmodel.h>
#include <drawermodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TabBarModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "TabBarModel");
    qmlRegisterType<DrawerModel>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "DrawerModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
