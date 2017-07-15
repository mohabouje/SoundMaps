#include "appdelegate.h"
#include "config.h"

#include <audio/audiorecorder.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent),
        audioRecorder(new AudioRecorder(parent)) {

    }
    ~AppDelegatePrivate() {}


    void setAudioRecorder(AudioRecorder* tmp) {
        Q_Q(AppDelegate);
        if (tmp != audioRecorder) {
            audioRecorder = tmp;
            q->audioRecorderChanged(audioRecorder);
        }
    }


    AppDelegate* const  q_ptr;
    AudioRecorder*   audioRecorder;
};

AppDelegate::AppDelegate(QObject *parent) : QObject(parent) {

    qmlRegisterType<AudioRecorder>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioRecorder");

}

AudioRecorder *AppDelegate::audioRecorder() const {
    Q_D(const AppDelegate);
    return d->audioRecorder;
}

QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new AppDelegate();
}

void AppDelegate::setAudioRecorder(AudioRecorder *audioRecorder) {
    Q_D(AppDelegate);
    d->setAudioRecorder(audioRecorder);
}

