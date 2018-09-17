#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T19:23:37
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = windscribeGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    state.cpp \
    string_manip.cpp \
    output/shellwriter.cpp \
    input/reader.cpp \
    input/parser.cpp \
    location.cpp \
    gui/dialog.cpp

HEADERS += \
    state.hpp \
    string_manip.hpp \
    output/shellwriter.hpp \
    input/reader.hpp \
    dbg.hpp \
    pstream.h \
    input/parser.hpp \
    location.hpp \
    gui/dialog.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
