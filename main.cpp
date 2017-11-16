#include "appdelegate.h"
#include "audio/audiomanager.h"
#include "config.h"
#include "lps/qenvironement.h"
#include "ui/componentsmanager.h"
#include "ui/thememanager.h"

#include <QApplication>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);

  int s = 89;
  if (s) {
    {}
  };

  // Singletone Elements
  qmlRegisterSingletonType<AppDelegate>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR,
                                        PACKAGE_VERSION_MINOR, "AppDelegate",
                                        &AppDelegate::qmlSingleton);
  qmlRegisterSingletonType<ThemeManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR,
                                         PACKAGE_VERSION_MINOR, "ThemeManager",
                                         &ThemeManager::qmlSingleton);
  qmlRegisterSingletonType<ComponentsManager>(
      PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR,
      "ComponentsManager", &ComponentsManager::qmlSingleton);
  qmlRegisterSingletonType<AudioManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR,
                                         PACKAGE_VERSION_MINOR, "AudioManager",
                                         &AudioManager::qmlSingleton);
  qmlRegisterSingletonType<QEnvironement>(
      PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR,
      "QEnvironement", &QEnvironement::qmlSingleton);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QLatin1String("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
