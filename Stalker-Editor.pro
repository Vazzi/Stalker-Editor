#-------------------------------------------------
#
# Project created by QtCreator 2011-07-24T12:01:58
#
#-------------------------------------------------

QT       += core gui

TARGET = Stalker-Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    dialognewmap.cpp \
    mapinfo.cpp \
    dialoginfoset.cpp

HEADERS  += mainwindow.h \
        myscene.h \
    dialognewmap.h \
    mapinfo.h \
    dialoginfoset.h

FORMS    += mainwindow.ui \
    dialognewmap.ui \
    dialoginfoset.ui

RESOURCES += \
    MyResources.qrc
