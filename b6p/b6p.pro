#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T12:13:04
#
#-------------------------------------------------

QT       += core gui sql network
CONFIG += qt
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4) {
    QT *= printsupport
}

TARGET = b6p
TEMPLATE = app

TRANSLATIONS = b6p.ts \
               b6p_esAR.ts

#win32 {
#INCLUDEPATH += e:/boost/boost_1_55_0
#RC_FILE = b6p.rc
#}

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
    dlgmerge.cpp \
    licenciaempleado.cpp \
    licenciasempleados.cpp \
    dlgempleadoslicenciasplanificacion.cpp \
    dlglicencia.cpp \
    dlgquerybuilder.cpp \
    dlgdaterangefilter.cpp \
    basereport.cpp \
    reportehorassectorsubsector.cpp \
    reportehorasdiaadia.cpp \
    reportehorasporempleado.cpp \
    reportefrancosplanificados.cpp \
    reportitem.cpp \
    reportitemcollection.cpp \
    b6pcalendarwidget.cpp \
    CalendarWindow.cpp \
    dlgfilesynchronization.cpp \
    filesynchronization.cpp

HEADERS  += \
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
    CalendarWindow.h \
    mainwindow.h \
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
    dlgmerge.h \
    licenciaempleado.h \
    licenciasempleados.h \
    dlgempleadoslicenciasplanificacion.h \
    dlglicencia.h \
    dlgquerybuilder.h \
    dlgdaterangefilter.h \
    basereport.h \
    reportehorassectorsubsector.h \
    reportehorasdiaadia.h \
    reportehorasporempleado.h \
    reportefrancosplanificados.h \
    reportitem.h \
    reportitemcollection.h \
    b6pcalendarwidget.h \
    dlgfilesynchronization.h \
    filesynchronization.h

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
    dlgmerge.ui \
    dlgempleadoslicenciasplanificacion.ui \
    dlglicencia.ui \
    dlgquerybuilder.ui \
    dlgdaterangefilter.ui \
    CalendarWindow.ui \
    dlgfilesynchronization.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    b6p.rc

include(QsLog.pri)
