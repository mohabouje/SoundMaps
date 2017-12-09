INCLUDEPATH += $$PWD/../eDSP/include/
DEPENDPATH += $$PWD/../eDSP/include/

LIBS += -L /usr/local/lib/ -lfftw3

HEADERS += \
    $$PWD/../eDSP/include/base/analog_filter.h \
    $$PWD/../eDSP/include/base/constants.h \
    $$PWD/../eDSP/include/base/sfinae.h \
    $$PWD/../eDSP/include/base/transform.h \
    $$PWD/../eDSP/include/base/types.h \
    $$PWD/../eDSP/include/filters/biquad.h \
    $$PWD/../eDSP/include/filters/biquaddesigner.h \
    $$PWD/../eDSP/include/frequency/autocorrelation.h \
    $$PWD/../eDSP/include/frequency/cepstrum.h \
    $$PWD/../eDSP/include/frequency/dct.h \
    $$PWD/../eDSP/include/frequency/dht.h \
    $$PWD/../eDSP/include/frequency/fft.h \
    $$PWD/../eDSP/include/frequency/idct.h \
    $$PWD/../eDSP/include/frequency/ifft.h \
    $$PWD/../eDSP/include/frequency/linearpredictivecoding.h \
    $$PWD/../eDSP/include/frequency/spectrogram.h \
    $$PWD/../eDSP/include/generators/generators.h \
    $$PWD/../eDSP/include/math/complex.h \
    $$PWD/../eDSP/include/math/math.h \
    $$PWD/../eDSP/include/math/stats.h \
    $$PWD/../eDSP/include/math/trig.h \
    $$PWD/../eDSP/include/properties/properties.h \
    $$PWD/../eDSP/include/utility/map.h \
    $$PWD/../eDSP/include/utility/vector.h \
    $$PWD/../eDSP/include/window/window.h \
    $$PWD/../eDSP/include/config.h \
    $$PWD/../eDSP/include/version.h
