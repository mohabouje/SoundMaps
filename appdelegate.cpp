#include "appdelegate.h"
#include "sm_config.h"

#include <audio/audiomanager.h>
#include <ui/chart/circularseries.h>
#include <ui/componentsmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent)
    {


    }
    ~AppDelegatePrivate() {}

    eDSP::frequency::Spectrogram  spectrogram{};
    AppDelegate* const  q_ptr;    
};

AppDelegate::AppDelegate(QObject *parent) :
    QObject(parent),
    d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<ComponentsManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "ComponentsManager");
    qmlRegisterType<AudioManager>(PACKAGE_NAME, PACKAGE_VERSION_MAJOR, PACKAGE_VERSION_MINOR, "AudioManager");
}


AppDelegate::~AppDelegate()
{
    delete d_ptr;
}

QObject *AppDelegate::qmlSingleton(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(AppDelegate);
}

#define DEFAULT_BUFFER_SIZE_SECS 10
void AppDelegate::init() {
    ComponentsManager* cm = qobject_cast<ComponentsManager*>(ComponentsManager::qmlSingleton(nullptr, nullptr));
    AudioManager* am = qobject_cast<AudioManager*>(AudioManager::qmlSingleton(nullptr, nullptr));
    AudioRecorder* audioRecorder = am->recorder();
    CircularSeries* circularSeries = cm->circularSeries();
    SpectrogramSeries *spectrogramSeries = cm->spectrogramSeries();


    connect(audioRecorder, &AudioRecorder::onBufferReady, this, [&, circularSeries, spectrogramSeries](float* buffer, int size) {
        QVector<double> input(size), output(size);
        std::copy(buffer, buffer + size, std::begin(input));

        Q_D(AppDelegate);
        d->spectrogram.compute(std::begin(input), std::end(input), std::begin(output));
        spectrogramSeries->set(output);
        circularSeries->append(input);
    });

    connect(audioRecorder, &AudioRecorder::sampleRateChanged, this, [circularSeries,
            spectrogramSeries,
            audioRecorder](double sr) {
        circularSeries->setSize(static_cast<int>(DEFAULT_BUFFER_SIZE_SECS * sr));
        spectrogramSeries->setSampleRate(sr);
        spectrogramSeries->setSize(static_cast<int>(audioRecorder->frameLength() / 1000.0 * sr));
    });

    audioRecorder->sampleRateChanged(audioRecorder->sampleRate());
}
