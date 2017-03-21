QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JCopToolProxy

HEADERS       = mainwindow.h \
                mdichild.h \
                newcardsession.h \
    statuswidget.h \
    simplepcscmanager.h

SOURCES       = main.cpp \
                mainwindow.cpp \
                mdichild.cpp \
                newcardsession.cpp \
    statuswidget.cpp \
    simplepcscmanager.cpp

#DEFINES += SHOW_DEBUG

RESOURCES     = mdi.qrc

win32:LIBS += WinSCard.Lib

FORMS += \
    newcardsession.ui \
    statuswidget.ui

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
