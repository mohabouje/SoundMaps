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
    $$PWD/ShortTimeAnalysisChartForm.ui.qml \
    $$PWD/ShortTimeAnalysisChart.qml \
    $$PWD/ShortTimeAnalysisChartForm.ui.qml \
    $$PWD/ShortTimeAnalysisChart.qml \
    $$PWD/ImageToolButtonForm.ui.qml \
    $$PWD/ImageToolButton.qml

RESOURCES += \
    $$PWD/components.qrc
