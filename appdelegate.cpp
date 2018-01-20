#include "appdelegate.h"
#include "sm_config.h"

#include <QDebug>
#include <audio/audiomanager.h>
#include <chrono>
#include <eDSP/include/filters/dcremoval.h>
#include <eDSP/include/frequency/autocorrelation.h>
#include <eDSP/include/frequency/cepstrum.h>
#include <eDSP/include/frequency/linearpredictivecoding.h>
#include <eDSP/include/properties/properties.h>
#include <lps/qenvironement.h>
#include <ui/abstractmodel/abstractmodelmanager.h>
#include <ui/chart/chartmanager.h>

class AppDelegatePrivate : QSharedData {
    Q_DISABLE_COPY(AppDelegatePrivate)
    Q_DECLARE_PUBLIC(AppDelegate)
public:
    AppDelegatePrivate(AppDelegate* parent)
        : q_ptr(parent)
    {
        lpc.set_order(13);
    }
    ~AppDelegatePrivate() {}

    edsp::frequency::Spectrogram spectrogram{};
    edsp::frequency::Cepstrum cepstrum{};
    edsp::frequency::AutoCorrelation autocorr{};
    edsp::frequency::LinearPredictiveCode<double> lpc{};
    edsp::filters::DCRemoval<double> dc{ 0.995 };
    AppDelegate* const q_ptr;
};

AppDelegate::AppDelegate(QObject* parent)
    : QObject(parent)
    , d_ptr(new AppDelegatePrivate(this))
{
    qmlRegisterType<AbstractModelManager>(
        SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR, SM_PACKAGE_VERSION_MINOR,
        "ComponentsManager");
    qmlRegisterType<AudioManager>(SM_PACKAGE_NAME, SM_PACKAGE_VERSION_MAJOR,
        SM_PACKAGE_VERSION_MINOR, "AudioManager");
}

AppDelegate::~AppDelegate() { delete d_ptr; }

QObject* AppDelegate::qmlSingleton(QQmlEngine* engine,
    QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SM_STATIC_SINGLETON(AppDelegate);
}

void AppDelegate::initUi()
{
    AbstractModelManager* cm = sm::single_tone<AbstractModelManager>();
    QEnvironement* environement = sm::single_tone<QEnvironement>();
    cm->init();
    cm->beaconListModel()->setEnvironement(environement);
}

void AppDelegate::initAudioSystem()
{
    ChartManager* chartm = sm::single_tone<ChartManager>();
    AudioManager* am = sm::single_tone<AudioManager>();

    AudioRecorder* audioRecorder = am->recorder();
    CircularBuffer* waveformBuffer = qobject_cast<CircularBuffer*>(chartm->bufferForType(ChartManager::WaveForm));
    CircularBuffer* energyBuffer = qobject_cast<CircularBuffer*>(chartm->bufferForType(ChartManager::Energy));
    CircularBuffer* pitchBuffer = qobject_cast<CircularBuffer*>(chartm->bufferForType(ChartManager::Energy));
    SpectrogramBuffer* spectrogramBuffer = qobject_cast<SpectrogramBuffer*>(chartm->bufferForType(ChartManager::Spectrogram));

    Q_UNUSED(energyBuffer);
    Q_UNUSED(pitchBuffer);

    connect(audioRecorder, &AudioRecorder::onBufferReady, this,
        [&, waveformBuffer, spectrogramBuffer](float* buffer, ulong size) {
            Q_D(AppDelegate);
            std::vector<double> input(buffer, buffer + size), output(size);

            edsp::properties::energy(std::begin(input), std::end(input));
            edsp::properties::power(std::begin(input), std::end(input));
            edsp::properties::zero_crossing_rate(std::begin(input),
                std::end(input));
            edsp::properties::loudness(std::begin(input), std::end(input));
            d->dc.compute(std::begin(input), std::end(input),
                std::begin(output));
            d->cepstrum.compute(std::begin(input), std::end(input),
                std::begin(output));
            d->autocorr.compute(std::begin(input), std::end(input),
                std::begin(output));
            d->spectrogram.compute(std::begin(input), std::end(input),
                std::begin(output));

            std::vector<double> coeff, reflections;
            double error;
            std::tie(error, coeff, reflections) = d->lpc.compute(std::begin(input), std::end(input));

            spectrogramBuffer->set(std::begin(output), std::end(output));
            waveformBuffer->set(std::begin(input), std::end(input));
        });

    connect(audioRecorder, &AudioRecorder::sampleRateChanged, this,
        [waveformBuffer, spectrogramBuffer, audioRecorder](double sr) {
            waveformBuffer->setSize(static_cast<int>(10 * sr));
            spectrogramBuffer->setSampleRate(sr);
            spectrogramBuffer->setSize(
                static_cast<int>(audioRecorder->frameLength()));
        });

    audioRecorder->setFrameLengthMSecs(20);
    audioRecorder->sampleRateChanged(audioRecorder->sampleRate());
}
