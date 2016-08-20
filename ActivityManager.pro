#-------------------------------------------------
#
# Project created by QtCreator 2016-08-19T21:27:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActivityManager
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    student.cpp \
    fileowner.cpp

HEADERS  += mainmenu.h \
    student.h \
    fileowner.h

FORMS    += mainmenu.ui

RESOURCES += \
    nameslist.qrc
