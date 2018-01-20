#include "appdelegate.h"
#include "audio/audiomanager.h"
#include "sm_config.h"
#include "lps/qenvironement.h"
#include "ui/componentsmanager.h"
#include "ui/thememanager.h"

#include "sm_config.h"

#include <QApplication>
#include <QQmlApplicationEngine>
int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication app(argc, argv);
  // Singletone Elements
  qmlRegisterSingletonType<AppDelegate>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
                                        SM_PACKAGE_VERSION_MINOR, "AppDelegate",
                                        &AppDelegate::qmlSingleton);
  qmlRegisterSingletonType<ThemeManager>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
                                         SM_PACKAGE_VERSION_MINOR, "ThemeManager",
                                         &ThemeManager::qmlSingleton);
  qmlRegisterSingletonType<ComponentsManager>(
      SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR,
      "ComponentsManager", &ComponentsManager::qmlSingleton);
  qmlRegisterSingletonType<AudioManager>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
                                         SM_PACKAGE_VERSION_MINOR, "AudioManager",
                                         &AudioManager::qmlSingleton);
  qmlRegisterSingletonType<QEnvironement>(
      SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR,
      "QEnvironement", &QEnvironement::qmlSingleton);

  AppDelegate* appdelegate = sm::single_tone<AppDelegate>();
  appdelegate->initUi();
  appdelegate->initAudioSystem();

  QQmlApplicationEngine engine;
  engine.load(QUrl(QLatin1String("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;
  return app.exec();
}
