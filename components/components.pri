QT += charts

HEADERS += \
    $$PWD/drawermodel.h \
    $$PWD/tabbarmodel.h \
    $$PWD/componentsmanager.h \
    $$PWD/thememanager.h

SOURCES += \
    $$PWD/drawermodel.cpp \
    $$PWD/tabbarmodel.cpp \
    $$PWD/componentsmanager.cpp \
    $$PWD/thememanager.cpp

DISTFILES += \
    $$PWD/MainTabBar.qml \
    $$PWD/TabImageButton.qml \
    $$PWD/AudioSettings.qml \
    $$PWD/ShortTimeAnalysisChart.qml \
    $$PWD/ShortTimeAnalysisChart.qml \
    $$PWD/ImageToolButton.qml

RESOURCES += \
    $$PWD/components.qrc
