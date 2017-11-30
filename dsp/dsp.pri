INCLUDEPATH += $$PWD/../eDSP/src/
DEPENDPATH += $$PWD/../eDSP/src/

LIBS += -L /usr/local/lib/ -lfftw3

HEADERS += \
    $$PWD/../eDSP/src/base/algoritmtemplate.h \
    $$PWD/../eDSP/src/base/constants.h \
    $$PWD/../eDSP/src/base/error.h \
    $$PWD/../eDSP/src/base/ierrornotifier.h \
    $$PWD/../eDSP/src/base/iinitializer.h \
    $$PWD/../eDSP/src/base/types.h \
    $$PWD/../eDSP/src/generators/brownnoisegenerator.h \
    $$PWD/../eDSP/src/generators/generator.h \
    $$PWD/../eDSP/src/generators/singenerator.h \
    $$PWD/../eDSP/src/generators/squaregenerator.h \
    $$PWD/../eDSP/src/generators/whitenoisegenerator.h \
    $$PWD/../eDSP/src/math/container.h \
    $$PWD/../eDSP/src/math/math_util.h \
    $$PWD/../eDSP/src/math/stats.h \
    $$PWD/../eDSP/src/math/trig.h \
    $$PWD/../eDSP/src/properties/energy.h \
    $$PWD/../eDSP/src/properties/loudness.h \
    $$PWD/../eDSP/src/properties/power.h \
    $$PWD/../eDSP/src/properties/strongpeak.h \
    $$PWD/../eDSP/src/properties/zerocrossingrate.h \
    $$PWD/../eDSP/src/transforms/dct.h \
    $$PWD/../eDSP/src/transforms/dht.h \
    $$PWD/../eDSP/src/transforms/fft.h \
    $$PWD/../eDSP/src/transforms/idct.h \
    $$PWD/../eDSP/src/transforms/ifft.h \
    $$PWD/../eDSP/src/window/window.h \
    $$PWD/../eDSP/src/config.h \
    $$PWD/../eDSP/src/version.h

SOURCES += \
    $$PWD/../eDSP/src/generators/brownnoisegenerator.cpp \
    $$PWD/../eDSP/src/generators/singenerator.cpp \
    $$PWD/../eDSP/src/generators/squaregenerator.cpp \
    $$PWD/../eDSP/src/generators/whitenoisegenerator.cpp \
    $$PWD/../eDSP/src/properties/energy.cpp \
    $$PWD/../eDSP/src/properties/loudness.cpp \
    $$PWD/../eDSP/src/properties/power.cpp \
    $$PWD/../eDSP/src/properties/strongpeak.cpp \
    $$PWD/../eDSP/src/properties/zerocrossingrate.cpp \
    $$PWD/../eDSP/src/transforms/dct.cpp \
    $$PWD/../eDSP/src/transforms/dht.cpp \
    $$PWD/../eDSP/src/transforms/fft.cpp \
    $$PWD/../eDSP/src/transforms/idct.cpp \
    $$PWD/../eDSP/src/transforms/ifft.cpp
