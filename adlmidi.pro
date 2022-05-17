include($$PWD/../../plugins.pri)

TARGET = $$PLUGINS_PREFIX/Input/adlmidi

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

unix {
    target.path = $$PLUGIN_DIR/Input
    INSTALLS += target
    PKGCONFIG += libADLMIDI
    QMAKE_CLEAN = $$PLUGINS_PREFIX/Input/libadlmidi.so
}

win32 {
    LIBS += -lADLMIDI
}
