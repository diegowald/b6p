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

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = b6p
TEMPLATE = app

TRANSLATIONS = b6p.ts \
               b6p_esAR.ts

win32 {
INCLUDEPATH += c:/boost/boost_1_53_0
RC_FILE = b6p.rc
}
SOURCES += main.cpp\
        mainwindow.cpp \
    timeassignment.cpp \
    timeassignmentplugin.cpp \
    acollection.cpp \
    sector.cpp \
    subsector.cpp \
    empleado.cpp \
    parametro.cpp \
    calendariopersona.cpp \
    capacidadpersonasector.cpp \
    planificaciondia.cpp \
    estimaciondia.cpp \
    planificacionsubsector.cpp \
    empleados.cpp \
    datastore.cpp \
    parametros.cpp \
    estimacionesdias.cpp \
    planificacionesdias.cpp \
    planificacionesdiassubsectores.cpp \
    sectores.cpp \
    subsectores.cpp \
    days.cpp \
    genericlist.cpp \
    dlgemployee.cpp \
    timeassignmentitemedit.cpp \
    availabilitywidget.cpp \
    capacitywidget.cpp \
    calendariopersonas.cpp \
    capacidadespersonasector.cpp \
    sqlhandler.cpp \
    dlgestimaciondia.cpp \
    dlgselectorbytdate.cpp \
    dlgplanificaciondia.cpp \
    dlgparametros.cpp \
    timeeditor.cpp \
    dlgaddmanyestimationdays.cpp \
    accesos.cpp \
    acceso.cpp \
    dlglogin.cpp \
    databasesynchronization.cpp \
    dlgsynchronization.cpp \
    SincroManager.cpp \
    timehelper.cpp \
    dlgapproveplanifications.cpp \
    dlgmerge.cpp

HEADERS  += mainwindow.h \
    timeassignment.h \
    timeassignmentplugin.h \
    acollection.h \
    sector.h \
    subsector.h \
    empleado.h \
    parametro.h \
    calendariopersona.h \
    capacidadpersonasector.h \
    planificaciondia.h \
    estimaciondia.h \
    planificacionsubsector.h \
    empleados.h \
    datastore.h \
    parametros.h \
    estimacionesdias.h \
    planificacionesdias.h \
    planificacionesdiassubsectores.h \
    sectores.h \
    subsectores.h \
    nullablefield.h \
    days.h \
    genericlist.h \
    dlgemployee.h \
    timeassignmentitemedit.h \
    availabilitywidget.h \
    capacitywidget.h \
    calendariopersonas.h \
    capacidadespersonasector.h \
    sqlhandler.h \
    IRecord.h \
    dlgestimaciondia.h \
    dlgselectorbytdate.h \
    dlgplanificaciondia.h \
    dlgparametros.h \
    timeeditor.h \
    dlgaddmanyestimationdays.h \
    accesos.h \
    acceso.h \
    dlglogin.h \
    databasesynchronization.h \
    dlgsynchronization.h \
    SincroManager.h \
    timehelper.h \
    dlgapproveplanifications.h \
    dlgmerge.h

FORMS    += mainwindow.ui \
    genericlist.ui \
    dlgemployee.ui \
    timeassignmentitemedit.ui \
    availabilitywidget.ui \
    capacitywidget.ui \
    dlgestimaciondia.ui \
    dlgselectorbytdate.ui \
    dlgplanificaciondia.ui \
    dlgparametros.ui \
    timeeditor.ui \
    dlgaddmanyestimationdays.ui \
    dlglogin.ui \
    dlgsynchronization.ui \
    dlgapproveplanifications.ui \
    dlgmerge.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    b6p.rc

include(QsLog.pri)
