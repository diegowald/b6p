/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "datastore.h"
#include <QsLog.h>


DataStore* DataStore::m_Instance = NULL;

DataStore* DataStore::instance()
{
    QLOG_TRACE_FN();
    if (m_Instance == NULL)
        m_Instance = new DataStore();
    return m_Instance;
}

void DataStore::initialize(QObject *parent)
{
    QLOG_TRACE_FN();
    setParent(parent);
}


DataStore::DataStore(QObject *parent) :
    QObject(parent), accesosCreated(false),
    parametrosCreated(false),
    empleadosCreated(false), estimacionesDiasCreated(false),
    planificacionesDiasCreated(false), planificacionesSubSectoresCreated(false),
    sectoresCreated(false), subSectoresCreated(false),
    calendariosCreated(false), capacidadesCreated(false),
    licenciasEmpleadosCreated(false),
    reporteHorasSectorSubSectorCreated(false),
    reporteHorasDiaADiaCreated(false),
    reporteHorasPorEmpleadoCreated(false),
    reporteFrancosPlanificadosCreated(false)
{
    QLOG_TRACE_FN();
}

DataStore::~DataStore()
{
    QLOG_TRACE_FN();
}

void DataStore::establishConnections(ACollectionPtr newMember)
{
    QLOG_TRACE_FN();
    connect(newMember.data(), SIGNAL(loaded(QString)), this, SIGNAL(loaded(QString)));
    connect(newMember.data(), SIGNAL(loading(QString)), this, SIGNAL(loading(QString)));
    connect(newMember.data(), SIGNAL(saved(QString)), this, SIGNAL(saved(QString)));
    connect(newMember.data(), SIGNAL(saving(QString)), this, SIGNAL(saving(QString)));
    newMember->load();
}

AccesosPtr DataStore::getAccesos()
{
    QLOG_TRACE_FN();
    if (!accesosCreated)
    {
        accessosPtr = AccesosPtr(new Accesos(getParametros()->getDatabaseNamePath(getParametros()->getValue("Accesos", "")), this));
        establishConnections(accessosPtr);
        accesosCreated = true;
    }
    return accessosPtr;
}


ParametrosPtr DataStore::getParametros()
{
    QLOG_TRACE_FN();
    if (!parametrosCreated)
    {
        parametrosPtr = ParametrosPtr(new Parametros(this));
        establishConnections(parametrosPtr);
        parametrosCreated = true;
    }
    return parametrosPtr;
}


EmpleadosPtr DataStore::getEmpleados()
{
    QLOG_TRACE_FN();
    if (!empleadosCreated)
    {
        empleadosPtr = EmpleadosPtr::create(getParametros()->getDatabaseNamePath(getParametros()->getValue("Empleados", "")), this);
        establishConnections(empleadosPtr);
        empleadosCreated = true;
    }
    return empleadosPtr;
}

EstimacionesDiasPtr DataStore::getEstimacionesDias()
{
    QLOG_TRACE_FN();
    if (!estimacionesDiasCreated)
    {
        estimacionesDiasPtr = EstimacionesDiasPtr(new EstimacionesDias(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("EstimacionesDias", "")), this));
        establishConnections(estimacionesDiasPtr);
        estimacionesDiasCreated = true;
    }
    return estimacionesDiasPtr;
}

PlanificacionesDiasPtr DataStore::getPlanificacionesDias()
{
    QLOG_TRACE_FN();
    if (!planificacionesDiasCreated)
    {
        planificacionesDiasPtr = PlanificacionesDiasPtr(new PlanificacionesDias(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("PlanificacionesDias", "")), this));
        establishConnections(planificacionesDiasPtr);
        planificacionesDiasCreated = true;
    }
    return planificacionesDiasPtr;
}

PlanificacionesSubSectoresPtr DataStore::getPlanificacionesSubSectores()
{
    QLOG_TRACE_FN();
    if (!planificacionesSubSectoresCreated)
    {
        planificacionesSubSectoresPtr = PlanificacionesSubSectoresPtr(
                    new PlanificacionesDiasSubSectores(
                        getParametros()->getDatabaseNamePath(getParametros()->getValue("PlanificacionesDiasSubSectores", "")), this));
        establishConnections(planificacionesSubSectoresPtr);
        planificacionesSubSectoresCreated = true;
    }
    return planificacionesSubSectoresPtr;

}

SectoresPtr DataStore::getSectores()
{
    QLOG_TRACE_FN();
    if (!sectoresCreated)
    {
        sectoresPtr = SectoresPtr(new Sectores(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("Sectores", "")), this));
        establishConnections(sectoresPtr);
        sectoresCreated = true;
    }
    return sectoresPtr;
}

SubSectoresPtr DataStore::getSubSectores()
{
    QLOG_TRACE_FN();
    if (!subSectoresCreated)
    {
        subSectoresPtr = SubSectoresPtr(new SubSectores(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("SubSectores", "")), this));
        establishConnections(subSectoresPtr);
        subSectoresCreated = true;
    }
    return subSectoresPtr;
}


CalendarioPersonasPtr DataStore::getCalendarios()
{
    QLOG_TRACE_FN();
    if (!calendariosCreated)
    {
        calendariosPtr = CalendarioPersonasPtr(
                    new CalendarioPersonas(
                        getParametros()->getDatabaseNamePath(getParametros()->getValue("CalendarioPersonas", "")),
                        this));
        establishConnections(calendariosPtr);
        calendariosCreated = true;
    }
    return calendariosPtr;
}

CapacidadesPersonaSectorPtr DataStore::getCapacidades()
{
    QLOG_TRACE_FN();
    if (!capacidadesCreated)
    {
        capacidadesPtr = CapacidadesPersonaSectorPtr(new CapacidadesPersonaSector(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("CapacidadesPersonaSector", "")), this));
        establishConnections(capacidadesPtr);
        capacidadesCreated = true;
    }
    return capacidadesPtr;
}

LicenciasEmpleadosPtr DataStore::getLicencias()
{
    QLOG_TRACE_FN();
    if (!licenciasEmpleadosCreated)
    {
        licenciasEmpleadosPtr = LicenciasEmpleadosPtr(new LicenciasEmpleados(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("LicenciasEmpleados", "")), this));
        establishConnections(licenciasEmpleadosPtr);
        licenciasEmpleadosCreated = true;
    }
    return licenciasEmpleadosPtr;
}

ReporteHorasSectorSubSectorPtr DataStore::getReporteHorasSectorSubSector()
{
    QLOG_TRACE_FN();
    if (!reporteHorasSectorSubSectorCreated)
    {
        reporteHorasSectorSubSectorPtr = ReporteHorasSectorSubSectorPtr(new ReporteHorasSectorSubSector(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("ReporteHorasSectorSubSector", "")), this));
        establishConnections(reporteHorasSectorSubSectorPtr);
        reporteHorasSectorSubSectorCreated = true;
    }
    return reporteHorasSectorSubSectorPtr;
}

ReporteHorasDiaADiaPtr DataStore::getReporteHorasDiaADia()
{
    QLOG_TRACE_FN();
    if (!reporteHorasDiaADiaCreated)
    {
        reporteHorasDiaADiaPtr = ReporteHorasDiaADiaPtr(new ReporteHorasDiaADia(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("ReporteHorasDiaADia", "")), this));
        establishConnections(reporteHorasDiaADiaPtr);
        reporteHorasDiaADiaCreated = true;
    }
    return reporteHorasDiaADiaPtr;
}

ReporteHorasPorEmpleadoPtr DataStore::getReporteHorasPorEmpleado()
{
    QLOG_TRACE_FN();
    if (!reporteHorasPorEmpleadoCreated)
    {
        reporteHorasPorEmpleadoPtr = ReporteHorasPorEmpleadoPtr(new ReporteHorasPorEmpleado(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("ReporteHorasPorEmpleado", "")), this));
        establishConnections(reporteHorasPorEmpleadoPtr);
        reporteHorasPorEmpleadoCreated = true;
    }
    return reporteHorasPorEmpleadoPtr;
}

ReporteFrancosPlanificadosPtr DataStore::getReporteFrancosPlanificados()
{
    QLOG_TRACE_FN();
    if (!reporteFrancosPlanificadosCreated)
    {
        reporteFrancosPlanificadosPtr = ReporteFrancosPlanificadosPtr(new ReporteFrancosPlanificados(
                    getParametros()->getDatabaseNamePath(getParametros()->getValue("ReporteFrancosPlanificados", "")), this));
        establishConnections(reporteFrancosPlanificadosPtr);
        reporteFrancosPlanificadosCreated = true;
    }
    return reporteFrancosPlanificadosPtr;
}


void DataStore::refreshData()
{
    QLOG_TRACE_FN();

    accessosPtr.reset();
    parametrosPtr.reset();
    empleadosPtr.reset();
    estimacionesDiasPtr.reset();
    planificacionesDiasPtr.reset();
    planificacionesSubSectoresPtr.reset();
    sectoresPtr.reset();
    subSectoresPtr.reset();
    calendariosPtr.reset();
    capacidadesPtr.reset();
    licenciasEmpleadosPtr.reset();
    reporteHorasSectorSubSectorPtr.reset();
    reporteHorasDiaADiaPtr.reset();
    reporteHorasPorEmpleadoPtr.reset();
    reporteFrancosPlanificadosPtr.reset();

    accesosCreated = false;
    parametrosCreated = false;
    empleadosCreated = false;
    estimacionesDiasCreated = false;
    planificacionesDiasCreated = false;
    planificacionesSubSectoresCreated = false;
    sectoresCreated = false;
    subSectoresCreated = false;
    calendariosCreated = false;
    capacidadesCreated = false;
    licenciasEmpleadosCreated = false;
    reporteHorasSectorSubSectorCreated = false;
    reporteHorasDiaADiaCreated = false;
    reporteHorasPorEmpleadoCreated = false;
    reporteFrancosPlanificadosCreated = false;
}
