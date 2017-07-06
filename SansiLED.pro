#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T15:50:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SansiLED
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    screen.cpp \
    inputdlg.cpp

HEADERS  += widget.h \
    screen.h \
    inputdlg.h

FORMS    += widget.ui

RESOURCES += \
    image1.qrc \
    buttonimage.qrc
