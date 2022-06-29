HEADERS += decoderadlmidifactory.h \
           decoder_adlmidi.h \
           adlmidihelper.h \
           adlmidimetadatamodel.h \
           settingsdialog.h

SOURCES += decoderadlmidifactory.cpp \
           decoder_adlmidi.cpp \
           adlmidihelper.cpp \
           adlmidimetadatamodel.cpp \
           settingsdialog.cpp

FORMS += settingsdialog.ui

#CONFIG += BUILD_PLUGIN_INSIDE
contains(CONFIG, BUILD_PLUGIN_INSIDE){
    include($$PWD/../../plugins.pri)
    TARGET = $$PLUGINS_PREFIX/Input/adlmidi

    win32{
        LIBS += -lADLMIDI
    }

    unix{
        target.path = $$PLUGIN_DIR/Input
        INSTALLS += target
        PKGCONFIG += libADLMIDI
    }
}else{
    QT += widgets
    CONFIG += warn_off plugin lib thread link_pkgconfig c++11
    TEMPLATE = lib

    unix{
        PKGCONFIG += qmmp-1 libADLMIDI

        PLUGIN_DIR = $$system(pkg-config qmmp-1 --variable=plugindir)/Input
        INCLUDEPATH += $$system(pkg-config qmmp-1 --variable=prefix)/include

        plugin.path = $${PLUGIN_DIR}
        plugin.files = lib$${TARGET}.so
        INSTALLS += plugin
    }
}
