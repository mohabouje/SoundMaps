#include "appdelegate.h"

AppDelegate::AppDelegate(QObject *parent) : QObject(parent)
{

}

AudioRecorder *AppDelegate::audioRecorder() const
{
    return _audioRecorder;
}

QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    AppDelegate* appDelegate = new AppDelegate();
    appDelegate->setQmlEngine(engine);
    appDelegate->setJsEngine(scriptEngine);
    return appDelegate;
}

void AppDelegate::setAudioRecorder(AudioRecorder *audioRecorder)
{
    _audioRecorder = audioRecorder;
}

void AppDelegate::setJsEngine(QJSEngine *jsEngine) {
    _jsEngine = jsEngine;
}

void AppDelegate::setQmlEngine(QQmlEngine *qmlEngine) {
    _qmlEngine = qmlEngine;
}
