#include "appdelegate.h"
#include "sm_config.h"

#include <eDSP/include/properties/properties.h>
#include <eDSP/include/frequency/cepstrum.h>
#include <eDSP/include/frequency/autocorrelation.h>
#include <eDSP/include/frequency/linearpredictivecoding.h>
#include <chrono>
#include <audio/audiomanager.h>
#include <ui/chart/circularseries.h>
#include <ui/componentsmanager.h>
#include <QDebug>

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
    eDSP::frequency::Cepstrum cepstrum{};
    eDSP::frequency::AutoCorrelation autocorr;
    eDSP::frequency::LinearPredictiveCode<double, 13> lpc;
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
        Q_D(AppDelegate);
        const auto start = std::chrono::system_clock::now();
        std::vector<double> input(buffer, buffer + size), output(size);
        const auto energy = eDSP::properties::energy(std::begin(input), std::end(input));
        const auto power = eDSP::properties::power(std::begin(input), std::end(input));
        const auto azcr = eDSP::properties::zero_crossing_rate(std::begin(input), std::end(input));
        const auto loudness = eDSP::properties::loudness(std::begin(input), std::end(input));
        d->cepstrum.compute(std::begin(input), std::end(input), std::begin(output));
        d->spectrogram.compute(std::begin(input), std::end(input), std::begin(output));
        d->autocorr.compute(std::begin(input), std::end(input), std::begin(output));
        const auto& lpc_coeff = d->lpc.compute(std::begin(input), std::end(input));
        const auto end = std::chrono::system_clock::now();
        const auto elapsed_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
        qDebug() <<  "elapsed time: " << elapsed_seconds.count();


        spectrogramSeries->set(std::begin(output), std::end(output));
        circularSeries->set(std::begin(input), std::end(input));
    });

    connect(audioRecorder, &AudioRecorder::sampleRateChanged, this, [circularSeries,
            spectrogramSeries,
            audioRecorder](double sr) {
        circularSeries->setSize(static_cast<int>(DEFAULT_BUFFER_SIZE_SECS * sr));
        spectrogramSeries->setSampleRate(sr);
        spectrogramSeries->setSize(static_cast<int>(audioRecorder->frameLength()));
    });

    audioRecorder->sampleRateChanged(audioRecorder->sampleRate());
}
