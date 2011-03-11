#-------------------------------------------------
#
# Project created by QtCreator 2011-03-10T10:44:03
#
#-------------------------------------------------

QT       += core gui

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    roomwindow.cpp \
            Socket.cpp \
            ConnectionManager.cpp

HEADERS  += mainwindow.h \
            Socket.h \
            ConnectionManager.h \
    roomwindow.h

FORMS    += mainwindow.ui \
    roomwindow.ui

RESOURCES += \
    chatresource.qrc
