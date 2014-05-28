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

void DataStore::establishConnections(ACollection* newMember)
{
    QLOG_TRACE_FN();
    connect(newMember, SIGNAL(loaded(QString)), this, SIGNAL(loaded(QString)));
    connect(newMember, SIGNAL(loading(QString)), this, SIGNAL(loading(QString)));
    connect(newMember, SIGNAL(saved(QString)), this, SIGNAL(saved(QString)));
    connect(newMember, SIGNAL(saving(QString)), this, SIGNAL(saving(QString)));
    newMember->load();
}

QString DataStore::getDatabaseName(const QString computerName)
{
    return QString("./" + computerName + "planning.b6p");
}

AccesosPtr DataStore::getAccesos()
{
    QLOG_TRACE_FN();
    if (!accesosCreated)
    {
        accessosPtr = boost::make_shared<Accesos>(
                    getDatabaseName(getParametros()->getValue("Accesos", "")), this);
        establishConnections(accessosPtr.get());
        accesosCreated = true;
    }
    return accessosPtr;
}


ParametrosPtr DataStore::getParametros()
{
    QLOG_TRACE_FN();
    if (!parametrosCreated)
    {
        parametrosPtr = boost::make_shared<Parametros>(this);
        establishConnections(parametrosPtr.get());
        parametrosCreated = true;
    }
    return parametrosPtr;
}


EmpleadosPtr DataStore::getEmpleados()
{
    QLOG_TRACE_FN();
    if (!empleadosCreated)
    {
        empleadosPtr = boost::make_shared<Empleados>(
                    getDatabaseName(getParametros()->getValue("Empleados", "")), this);
        establishConnections(empleadosPtr.get());
        empleadosCreated = true;
    }
    return empleadosPtr;
}

EstimacionesDiasPtr DataStore::getEstimacionesDias()
{
    QLOG_TRACE_FN();
    if (!estimacionesDiasCreated)
    {
        estimacionesDiasPtr = boost::make_shared<EstimacionesDias>(
                    getDatabaseName(getParametros()->getValue("EstimacionesDias", "")), this);
        establishConnections(estimacionesDiasPtr.get());
        estimacionesDiasCreated = true;
    }
    return estimacionesDiasPtr;
}

PlanificacionesDiasPtr DataStore::getPlanificacionesDias()
{
    QLOG_TRACE_FN();
    if (!planificacionesDiasCreated)
    {
        planificacionesDiasPtr = boost::make_shared<PlanificacionesDias>(
                    getDatabaseName(getParametros()->getValue("PlanificacionesDias", "")), this);
        establishConnections(planificacionesDiasPtr.get());
        planificacionesDiasCreated = true;
    }
    return planificacionesDiasPtr;
}

PlanificacionesSubSectoresPtr DataStore::getPlanificacionesSubSectores()
{
    QLOG_TRACE_FN();
    if (!planificacionesSubSectoresCreated)
    {
        planificacionesSubSectoresPtr = boost::make_shared<PlanificacionesDiasSubSectores>(
                    getDatabaseName(getParametros()->getValue("PlanificacionesDiasSubSectores", "")), this);
        establishConnections(planificacionesSubSectoresPtr.get());
        planificacionesSubSectoresCreated = true;
    }
    return planificacionesSubSectoresPtr;

}

SectoresPtr DataStore::getSectores()
{
    QLOG_TRACE_FN();
    if (!sectoresCreated)
    {
        sectoresPtr = boost::make_shared<Sectores>(
                    getDatabaseName(getParametros()->getValue("Sectores", "")), this);
        establishConnections(sectoresPtr.get());
        sectoresCreated = true;
    }
    return sectoresPtr;
}

SubSectoresPtr DataStore::getSubSectores()
{
    QLOG_TRACE_FN();
    if (!subSectoresCreated)
    {
        subSectoresPtr = boost::make_shared<SubSectores>(
                    getDatabaseName(getParametros()->getValue("SubSectores", "")), this);
        establishConnections(subSectoresPtr.get());
        subSectoresCreated = true;
    }
    return subSectoresPtr;
}


CalendarioPersonasPtr DataStore::getCalendarios()
{
    QLOG_TRACE_FN();
    if (!calendariosCreated)
    {
        calendariosPtr = boost::make_shared<CalendarioPersonas>(
                    getDatabaseName(getParametros()->getValue("CalendarioPersonas", "")),
                    this);
        establishConnections(calendariosPtr.get());
        calendariosCreated = true;
    }
    return calendariosPtr;
}

CapacidadesPersonaSectorPtr DataStore::getCapacidades()
{
    QLOG_TRACE_FN();
    if (!capacidadesCreated)
    {
        capacidadesPtr = boost::make_shared<CapacidadesPersonaSector>(
                    getDatabaseName(getParametros()->getValue("CapacidadesPersonaSector", "")), this);
        establishConnections(capacidadesPtr.get());
        capacidadesCreated = true;
    }
    return capacidadesPtr;
}

LicenciasEmpleadosPtr DataStore::getLicencias()
{
    QLOG_TRACE_FN();
    if (!licenciasEmpleadosCreated)
    {
        licenciasEmpleadosPtr = boost::make_shared<LicenciasEmpleados>(
                    getDatabaseName(getParametros()->getValue("LicenciasEmpleados", "")), this);
        establishConnections(licenciasEmpleadosPtr.get());
        licenciasEmpleadosCreated = true;
    }
    return licenciasEmpleadosPtr;
}

ReporteHorasSectorSubSectorPtr DataStore::getReporteHorasSectorSubSector()
{
    QLOG_TRACE_FN();
    if (!reporteHorasSectorSubSectorCreated)
    {
        reporteHorasSectorSubSectorPtr = boost::make_shared<ReporteHorasSectorSubSector>(
                    getDatabaseName(getParametros()->getValue("ReporteHorasSectorSubSector", "")), this);
        establishConnections(reporteHorasSectorSubSectorPtr.get());
        reporteHorasSectorSubSectorCreated = true;
    }
    return reporteHorasSectorSubSectorPtr;
}

ReporteHorasDiaADiaPtr DataStore::getReporteHorasDiaADia()
{
    QLOG_TRACE_FN();
    if (!reporteHorasDiaADiaCreated)
    {
        reporteHorasDiaADiaPtr = boost::make_shared<ReporteHorasDiaADia>(
                    getDatabaseName(getParametros()->getValue("ReporteHorasDiaADia", "")), this);
        establishConnections(reporteHorasDiaADiaPtr.get());
        reporteHorasDiaADiaCreated = true;
    }
    return reporteHorasDiaADiaPtr;
}

ReporteHorasPorEmpleadoPtr DataStore::getReporteHorasPorEmpleado()
{
    QLOG_TRACE_FN();
    if (!reporteHorasPorEmpleadoCreated)
    {
        reporteHorasPorEmpleadoPtr = boost::make_shared<ReporteHorasPorEmpleado>(
                    getDatabaseName(getParametros()->getValue("ReporteHorasPorEmpleado", "")), this);
        establishConnections(reporteHorasPorEmpleadoPtr.get());
        reporteHorasPorEmpleadoCreated = true;
    }
    return reporteHorasPorEmpleadoPtr;
}

ReporteFrancosPlanificadosPtr DataStore::getReporteFrancosPlanificados()
{
    QLOG_TRACE_FN();
    if (!reporteFrancosPlanificadosCreated)
    {
        reporteFrancosPlanificadosPtr = boost::make_shared<ReporteFrancosPlanificados>(
                    getDatabaseName(getParametros()->getValue("ReporteFrancosPlanificados", "")), this);
        establishConnections(reporteFrancosPlanificadosPtr.get());
        reporteFrancosPlanificadosCreated = true;
    }
    return reporteFrancosPlanificadosPtr;
}


