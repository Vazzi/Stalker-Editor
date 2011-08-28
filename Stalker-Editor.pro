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
    mapfile.cpp \
    mapinfo.cpp \
    dialogsavemap.cpp

HEADERS  += mainwindow.h \
        myscene.h \
    dialognewmap.h \
    mapfile.h \
    mapinfo.h \
    dialogsavemap.h

FORMS    += mainwindow.ui \
    dialognewmap.ui \
    dialogsavemap.ui

RESOURCES += \
    MyResources.qrc
