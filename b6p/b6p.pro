#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T12:13:04
#
#-------------------------------------------------

# CONFIG      += designer plugin
# TARGET      = $$qtLibraryTarget($$TARGET)
# TEMPLATE    = lib
# QTDIR_build:DESTDIR     = $$QT_BUILD_TREE/plugins/designer

 #HEADERS     = analogclock.h \
 #              customwidgetplugin.h
 #SOURCES     = analogclock.cpp \
 #              customwidgetplugin.cpp

 #build_all:!build_pass {
 #    CONFIG -= build_all
 #    CONFIG += release
 #}

 ## install
 #target.path = $$[QT_INSTALL_PLUGINS]/designer
 #sources.files = $$SOURCES $$HEADERS *.pro
 #sources.path = $$[QT_INSTALL_EXAMPLES]/designer/customwidgetplugin
 #INSTALLS += target sources

 #symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
 #maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)
 #symbian: warning(This example does not work on Symbian platform)
 #maemo5: warning(This example does not work on Maemo platform)
 #simulator: warning(This example does not work on Simulator platform)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = b6p
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    timeassignment.cpp \
    timeassignmentplugin.cpp

HEADERS  += mainwindow.h \
    timeassignment.h \
    timeassignmentplugin.h

FORMS    += mainwindow.ui

