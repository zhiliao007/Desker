#-------------------------------------------------
#
# Project created by QtCreator 2018-01-01T12:18:11
#
#-------------------------------------------------

QT       += core gui
QT       += winextras
LIBS     += -lshell32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileicon.cpp

HEADERS  += mainwindow.h \
    windows_api.h \
    fileicon.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DISTFILES +=
