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
#include "empleado.h"
#include "datastore.h"
#include "days.h"
#include "timehelper.h"
#include<QsLog.h>

// Printing support
#include <QUrl>
#include "timeassignment.h"

EmployeeCalculatedCapacity::EmployeeCalculatedCapacity(Empleado* parentEmpleado, QDate Dia) :
    QObject(parentEmpleado)
{
    QLOG_TRACE_FN();
    empleado = parentEmpleado;
    capacityForTask = -1000;
    dia = Dia;
}

void EmployeeCalculatedCapacity::setCapacity(int value)
{
    QLOG_TRACE_FN();
    capacityForTask = value;
}

Empleado* EmployeeCalculatedCapacity::EmpleadoAsignado()
{
    QLOG_TRACE_FN();
    return empleado;
}

int EmployeeCalculatedCapacity::Capacity()
{
    QLOG_TRACE_FN();
    return capacityForTask;
}

int EmployeeCalculatedCapacity::HorasPreviamenteTrabajadas()
{
    QLOG_TRACE_FN();
    int horas = 0;
    // Esta no es la mejor manera de obtener un valor, ya que se puede reescribir si eventualmente
    // se conecta a otro lugar, pero si se tiene en cuenta que un solo slot va a estar conectado, entonces
    // deberia funcionar.
    emit calcularHorasPreviamenteTrabajadas(empleado->IDEmpleado().value(), horas);
    return horas;
}

int EmployeeCalculatedCapacity::DiasPreviamenteTrabajados()
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst diasTrabajados =
            DataStore::instance()->getPlanificacionesSubSectores()
            ->getDiasAnterioresTrabajadosPorEmpleado(dia, empleado->IDEmpleado().value());

    return diasTrabajados->count();
}

bool EmployeeCalculatedCapacity::hasWarningsDias()
{
    QLOG_TRACE_FN();
    bool warningDias = (DiasPreviamenteTrabajados() > DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 0));
    return warningDias;
}

bool EmployeeCalculatedCapacity::hasWarningsHorasMenorAMinimo()
{
    QLOG_TRACE_FN();
    bool warningHoras = (HorasPreviamenteTrabajadas() < DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MIN_HOURS, 0));
    return warningHoras;
}

bool EmployeeCalculatedCapacity::hasWarningsHorasMayorAMaximo()
{
    QLOG_TRACE_FN();
    bool warningHoras = (HorasPreviamenteTrabajadas() > DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MAX_HOURS, 24));
    return warningHoras;
}

Empleado::Empleado(bool isNew, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    if (isNew)
        idEmpleado.setValue(-1);
    else
        idEmpleado.setNull();
    apellido.setNull();
    nombre.setNull();
    fechaIngreso.setNull();
    isBaja.setNull();
    legajo.setNull();

    idEmpleado.setParent(this);
    apellido.setParent(this);
    nombre.setParent(this);
    fechaIngreso.setParent(this);
    isBaja.setParent(this);
    legajo.setParent(this);

    if (isNew)
        setNew();
}

RecordPtr Empleado::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr::create();

    (*res)["Legajo"] = legajo.toVariant();
    (*res)["Apellido"] = apellido.toVariant();
    (*res)["Nombres"] = nombre.toVariant();
    (*res)["FechaIngreso"] = fechaIngreso.toVariant();
    (*res)["isBaja"] = isBaja.toVariant();
    (*res)["ID"] = idEmpleado.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus(); // Capaz que es inmemoryRecordStatus

    (*res)[RECORD_ID] = idEmpleado.toVariant();
    return res;
}

bool Empleado::isEqualsTo(RecordPtr record, const QStringList &fieldsToMerge)
{
    QLOG_TRACE_FN();
    bool res = true;
    RecordPtr localRec = asRecordPtr();
    foreach (QString fld, fieldsToMerge) {
        res &= ((*record)[fld] == (*localRec)[fld]);
    }
    res &= ((*record)["RecordStatus"] == (*localRec)["RecordStatus"]);
    return res;
}

NullableField<int>& Empleado::IDEmpleado()
{
    QLOG_TRACE_FN();
    return idEmpleado;
}

NullableField<QString>& Empleado::Apellido()
{
    QLOG_TRACE_FN();
    return apellido;
}

NullableField<QString>& Empleado::Nombre()
{
    QLOG_TRACE_FN();
    return nombre;
}

NullableField<QString>& Empleado::Legajo()
{
    QLOG_TRACE_FN();
    return legajo;
}

NullableField<QDate>& Empleado::FechaIngreso()
{
    QLOG_TRACE_FN();
    return fechaIngreso;
}

NullableField<bool>& Empleado::IsBaja()
{
    QLOG_TRACE_FN();
    return isBaja;
}

CapacidadPersonaSectorLst Empleado::Capacities()
{
    QLOG_TRACE_FN();
    if (IDEmpleado().isNull())
        return QSharedPointer<QList<CapacidadPersonaSectorPtr> >(new QList<CapacidadPersonaSectorPtr>());
    else
        return DataStore::instance()->getCapacidades()->getAll(IDEmpleado().value(), false);
}

void Empleado::updateCapacities(CapacidadPersonaSectorLst newCapacities)
{
    QLOG_TRACE_FN();
    CapacidadesPersonaSectorPtr ptr = DataStore::instance()->getCapacidades();
    ptr->updateCapacityfromData(newCapacities);
}

void Empleado::updateDisponibilidades(CalendarioPersonaLst newDisponibilidades)
{
    QLOG_TRACE_FN();
    CalendarioPersonasPtr ptr = DataStore::instance()->getCalendarios();
    ptr->updateCalendarFromData(newDisponibilidades);
}

CalendarioPersonaLst Empleado::Disponibilidades()
{
    QLOG_TRACE_FN();
    if (IDEmpleado().isNull() || IDEmpleado().value() == -1)
        return QSharedPointer<QList<CalendarioPersonaPtr> >::create();
    else
        return DataStore::instance()->getCalendarios()->getAll(IDEmpleado().value(), false);
}

LicenciasEmpleadosLst Empleado::LicenciasProgramadas()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getLicencias()->getAllLicenciasEmpleado(idEmpleado.value());
}

LicenciaEmpleadoPtr Empleado::LicenciaProgramada(QDate &fecha)
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getLicencias()->getLicenciaEmpleado(idEmpleado.value(), fecha);
}


void Empleado::updateID(int newId)
{
    QLOG_TRACE_FN();
    DataStore::instance()->getCalendarios()->updateCalendarWithNewIDEmpleado(-1, newId);


    CapacidadPersonaSectorLst cps = Capacities();
    foreach (CapacidadPersonaSectorPtr cs, *cps)
    {
        cs->updateIDEmpleado(newId);
    }

    IDEmpleado().setValue(newId);
    setUnmodified();
}

EmployeeCalculatedCapacityPtr Empleado::canWork(QDate &Fecha, int IDSector, int IDSubSector, int HoraInicio, int HoraFin)
{
    QLOG_TRACE_FN();
    EmployeeCalculatedCapacityPtr res = EmployeeCalculatedCapacityPtr::create(this, Fecha);

    // Verifico si no esta en licencia
    LicenciaEmpleadoPtr licencia = DataStore::instance()->getLicencias()->getLicenciaEmpleado(idEmpleado.value(), Fecha);
    if (licencia != LicenciaEmpleadoPtr())
    {
        res->setCapacity(0);
        return res;
    }

    // Verifico si puede trabajar en el sector y subsector
    CapacidadPersonaSectorPtr cap =
            DataStore::instance()->getCapacidades()->get(idEmpleado.value(), IDSector, IDSubSector, false);
    if (cap.isNull())
    {
        res->setCapacity(0);
        return res;
    }


    // Verifico si puede trabajar el dia en la franja horaria.
    DAYS Dia = Days::DayOfWeek2DAYS(Fecha.dayOfWeek());
    CalendarioPersonaPtr cal = DataStore::instance()->getCalendarios()->get(
                idEmpleado.value(), Dia, HoraInicio, HoraFin, false);

    // Aca pueden darse varios casos. POr ahora solo vamos a contemplar que el empleado
    // efectivamente pueda trabajar en esa franja horaria.

    if (cal.isNull())
    {
        res->setCapacity(0);
        return res;
    }

    // Verifico si es horario de apertura y ademas cerro el dia anterior
    if (HoraInicio == DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0))
    {
        PlanificacionSubSectorLst diasPrevios = DataStore::instance()->getPlanificacionesSubSectores()->getDiasAnterioresTrabajadosPorEmpleado(Fecha, idEmpleado.value());
        foreach (PlanificacionSubSectorPtr p, *diasPrevios)
        {
            int days = Fecha.toJulianDay() - p->Dia().value().toJulianDay();
            if (days == 1)
            {
                if (p->HoraFin().value() == DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400))
                {
                    res->setCapacity(0);
                    return res;
                }
            }
        }
    }

    if (!cap.isNull())
        res->setCapacity(cap->Capacidad().value()); // A esto habria que afectarlo

    return res;
}

bool Empleado::isAvailable(QDate &Fecha, bool incluirLicencias)
{
    QLOG_TRACE_FN();

    // Verifico si puede trabajar el dia en la franja horaria.
    DAYS Dia = Days::DayOfWeek2DAYS(Fecha.dayOfWeek());
    bool canWork =  DataStore::instance()->getCalendarios()->canWork(idEmpleado.value(), Dia);

    if (!canWork)
        return false;

    if (!IsBaja().isNull() && IsBaja().value())
        return false;

    if (!incluirLicencias)
    {
        if (DataStore::instance()->getLicencias()->isOnLicence(idEmpleado.value(), Fecha))
        {
            // El empleado esta de licencia
            return false;
        }
    }

    // El empleado puede trabajar ese dia
    return true;
}

bool Empleado::canBeDeleted()
{
    QLOG_TRACE_FN();
    return true;
}

bool Empleado::DadoDeBaja()
{
    QLOG_TRACE_FN();
    return IsBaja().isNull() ? false : IsBaja().value();
}

bool Empleado::isPowerUser()
{
    QLOG_TRACE_FN();
    // Devuelve true si el empleado esta en el grupo Gerencia o Supervisor
    CapacidadPersonaSectorPtr c = DataStore::instance()->getCapacidades()->get(idEmpleado.value(), 8, 0, false);
    if (!c.isNull())
        return true;
    c = DataStore::instance()->getCapacidades()->get(idEmpleado.value(), 9, 0, false);
    return !c.isNull();
}

bool Empleado::print(QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header

    html += "<tr>";
    html += "<td bgcolor=\"lightgray\" colspan=\"2\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employee") + "</i></b></font>\n</td>";
    html += "</tr>";

    html += "<tr><td>" + tr("LastName") + "</td><td>" + Apellido().value() + "</td></tr>";
    html += "<tr><td>" + tr("Names") + "</td><td>" + Nombre().value() + "</td></tr>";
    html += "<tr><td>" + tr("ID") + "</td><td>" + Legajo().value() + "</td></tr>";
    html += "<tr><td>" + tr("Start Date") + "</td><td>" + FechaIngreso().value().toString() + "</td></tr>";
    html += "</table>";

    html += "<br>";

    CapacidadPersonaSectorLst capacidades = Capacities();

    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr><td colspan=\"4\" bgcolor=\"lightgray\"><font size=\"+1\"<b><i>" + tr("Expertise") + "</i></b></font></td></tr>";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Sector") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("SubSector") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Proficiency") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("") + "</i></font>\n</td>";
    html += "</tr>";

    foreach (CapacidadPersonaSectorPtr c, *capacidades) {
        html += "<tr>";
        if (c->getSector())
            html += "<td>" + c->getSector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        if (c->getSubSector())
            html += "<td>" + c->getSubSector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        html += "<td>" + QString::number(c->Capacidad().value()) + "</td>";

        html += "<td>" + tr("Diagram") + "</td>";
        html += "</tr>";
    }
    html += "\n</table>\n<br>\n";

    CalendarioPersonaLst calendarios = Disponibilidades();
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr><td colspan=\"4\" bgcolor=\"lightgray\"><font size=\"+1\"<b><i>" + tr("Availability")  + "</i></b></font></td></tr>";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Day") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Start Time") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("End Time") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Start Time 2") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("End Time 2") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\"><i></i></font>\n</td>";
    html += "</tr>";

    int imgNumber = 0;
    foreach (CalendarioPersonaPtr c, *calendarios) {
        html += "<tr>";
        html += "<td>" + Days::Days2String(Days::DayOfWeek2DAYS(c->Dia().value())) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraIngreso1().value()) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraEgreso1().value()) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraIngreso2().value()) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraEgreso2().value()) + "</td>";
        QString img = "img%1";
        img = img.arg(imgNumber);
        html += "<td><img src=\"" + img + "\"></td>";

        QRect rect;
        rect.setWidth(500);
        rect.setHeight(30);
        QPixmap px(rect.size());
        TimeAssignment ts;
        ts.resize(rect.size());
        ts.setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
        ts.setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
        ts.setStartAssignment(c->HoraIngreso1().value());
        ts.setEndAssignment(c->HoraEgreso1().value());
        ts.setStartAssignment2(c->HoraIngreso2().value());
        ts.setEndAssignment2(c->HoraEgreso2().value());

        ts.setPaintBackgroundReferences(true);
        ts.setPaintVerticalGrid(true);
        ts.setShowBackgroundText(true);
        ts.setHollowTimeLine(true);
        ts.setTimeLineColor(Qt::black);

        ts.render(&px, QPoint(), QRegion(rect));
        textDoc.addResource(QTextDocument::ImageResource, QUrl(img), px);
        imgNumber++;
        html += "</tr>";
    }

    html += "\n</table>\n<br>\n";

    textDoc.setHtml(html);
    return true;
}
