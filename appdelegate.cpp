#include "appdelegate.h"
#include "sm_config.h"

#include <eDSP/include/properties/properties.h>
#include <eDSP/include/frequency/cepstrum.h>
#include <eDSP/include/frequency/autocorrelation.h>
#include <eDSP/include/frequency/linearpredictivecoding.h>
#include <eDSP/include/filters/dcremoval.h>
#include <chrono>
#include <audio/audiomanager.h>
#include <ui/chart/circularseries.h>
#include <ui/componentsmanager.h>
#include <QDebug>
#include <lps/qenvironement.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent) :
        q_ptr(parent)
    {
        lpc.set_order(13);
    }
    ~AppDelegatePrivate() {}

    edsp::frequency::Spectrogram  spectrogram{};
    edsp::frequency::Cepstrum cepstrum{};
    edsp::frequency::AutoCorrelation autocorr{};
    edsp::frequency::LinearPredictiveCode<double> lpc{};
    edsp::filters::DCRemoval<double> dc{0.995};
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

void AppDelegate::initUi() {
    ComponentsManager* cm = sm::single_tone<ComponentsManager>();
    QEnvironement* environement = sm::single_tone<QEnvironement>();
    cm->init();
    cm->beaconListModel()->setEnvironement(environement);
}

void AppDelegate::initAudioSystem() {
    ComponentsManager* cm = sm::single_tone<ComponentsManager>();
    AudioManager* am = sm::single_tone<AudioManager>();
    AudioRecorder* audioRecorder = am->recorder();
    CircularSeries* circularSeries = cm->circularSeries();
    SpectrogramSeries *spectrogramSeries = cm->spectrogramSeries();



    connect(audioRecorder, &AudioRecorder::onBufferReady, this, [&, circularSeries, spectrogramSeries](float* buffer, int size) {
        Q_D(AppDelegate);
        std::vector<double> input(buffer, buffer + size), output(size);

        const auto energy = edsp::properties::energy(std::begin(input), std::end(input));
        const auto power = edsp::properties::power(std::begin(input), std::end(input));
        const auto azcr = edsp::properties::zero_crossing_rate(std::begin(input), std::end(input));
        const auto loudness = edsp::properties::loudness(std::begin(input), std::end(input));
        d->dc.compute(std::begin(input), std::end(input), std::begin(output));
        d->cepstrum.compute(std::begin(input), std::end(input), std::begin(output));
        d->autocorr.compute(std::begin(input), std::end(input), std::begin(output));
        d->spectrogram.compute(std::begin(input), std::end(input), std::begin(output));

        std::vector<double> coeff, reflections; double error;
        std::tie(error, coeff, reflections) = d->lpc.compute(std::begin(input), std::end(input));


        spectrogramSeries->set(std::begin(output), std::end(output));
        circularSeries->set(std::begin(input), std::end(input));
    });

    connect(audioRecorder, &AudioRecorder::sampleRateChanged, this, [circularSeries,
            spectrogramSeries,
            audioRecorder](double sr) {
        circularSeries->setSize(static_cast<int>(10 * sr));
        spectrogramSeries->setSampleRate(sr);
        spectrogramSeries->setSize(static_cast<int>(audioRecorder->frameLength()));
    });

    audioRecorder->setFrameLengthMSecs(20);
    audioRecorder->sampleRateChanged(audioRecorder->sampleRate());
}
