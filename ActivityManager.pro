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
    fileowner.cpp \
    studentseditor.cpp \
    twoitemobject.cpp \
    dataservice.cpp

HEADERS  += mainmenu.h \
    fileowner.h \
    studentseditor.h \
    twoitemobject.h \
    dataservice.h

FORMS    += mainmenu.ui \
    studentseditor.ui

RESOURCES += \
    nameslist.qrc
