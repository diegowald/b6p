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
#include "planificaciondia.h"
#include "datastore.h"
#include "planificacionsubsector.h"
#include <QDateTime>
#include "timehelper.h"

//Printing
#include "timeassignment.h"
#include <QUrl>

#include <QsLog.h>

#include <algorithm>

PlanificacionDia::PlanificacionDia(QDate date, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_Dia.setValue(date);
    m_Notas.setNull();
    m_IDSupervisor.setNull();
    m_EstadosPlanificacion.setNull();

    m_Dia.setParent(this);
    m_Notas.setParent(this);
    m_IDSupervisor.setParent(this);
    m_EstadosPlanificacion.setParent(this);

    setNew();
}

PlanificacionDia::PlanificacionDia(QObject *parent) : QObject(parent)
{
    QLOG_TRACE_FN();
    m_Dia.setNull();
    m_Notas.setNull();
    m_IDSupervisor.setNull();
    m_EstadosPlanificacion.setNull();

    m_Dia.setParent(this);
    m_Notas.setParent(this);
    m_IDSupervisor.setParent(this);
    m_EstadosPlanificacion.setParent(this);
}

RecordPtr PlanificacionDia::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr::create();

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["Notas"] = m_Notas.toVariant();
    (*res)["IDSupervisor"] = m_IDSupervisor.toVariant();
    (*res)["EstadoPlanificacion"] = m_EstadosPlanificacion.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();
    return res;
}

bool PlanificacionDia::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["Dia"] == m_Dia.toVariant())
            && ((*record)["Notas"] == m_Notas.toVariant())
            && ((*record)["IDSupervisor"] == m_IDSupervisor.toVariant())
            && ((*record)["EstadoPlanificacion"] == m_EstadosPlanificacion.toVariant());
    return res;
}

NullableField<QDate> &PlanificacionDia::Dia()
{
    QLOG_TRACE_FN();
    return m_Dia;
}

NullableField<QString> &PlanificacionDia::Notas()
{
    QLOG_TRACE_FN();
    return m_Notas;
}

NullableField<int> &PlanificacionDia::IDSupervisor()
{
    QLOG_TRACE_FN();
    return m_IDSupervisor;
}

NullableField<EstadosPlanificacion> &PlanificacionDia::EstadoPlanificacion()
{
    QLOG_TRACE_FN();
    return m_EstadosPlanificacion;
}

EmpleadoPtr PlanificacionDia::Supervisor()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDSupervisor.value(), false);
}

EstimacionDiaPtr PlanificacionDia::Estimacion()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getEstimacionesDias()->get(m_Dia.value(), false);
}

int PlanificacionDia::HorasPlanificadas()
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst planificaciones =
            DataStore::instance()->getPlanificacionesSubSectores()->getAll(this->Dia().value(), false);

    double total = 0;

    foreach(PlanificacionSubSectorPtr p, *planificaciones)
    {
        if (!p->isDeleted(false))
        {
            total += p->CantidadHoras();
        }
    }
    return total;
}

QString PlanificacionDia::Estado()
{
    QLOG_TRACE_FN();
    QString inProgress = tr("In progress");
    QString finished = tr("Finished");
    QString approved = tr("Approved");
    QString res;
    if (m_EstadosPlanificacion.isNull())
    {
        res = inProgress;
        m_EstadosPlanificacion.setValue(INPROGRESS);
    }
    else
    {
        switch (m_EstadosPlanificacion.value())
        {
        case FINISHED:
            res = finished;
            break;
        case APPROVED:
            res = approved;
            break;
        case INPROGRESS:
        default:
            res = inProgress;
            break;
        }
    }
    return res;
}

void PlanificacionDia::approve()
{
    QLOG_TRACE_FN();
    if (isReadyForApproval())
        m_EstadosPlanificacion.setValue(APPROVED);
}

bool PlanificacionDia::isEverythingAssigned()
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst pl =
            DataStore::instance()->getPlanificacionesSubSectores()->getAll(
                Dia().value(), false);

    // Si no hay planificaciones, entonces se considera que no esta completo
    if (pl->count() == 0)
        return false;


    foreach(PlanificacionSubSectorPtr p, *pl)
    {
        if (p->IDEmpleado().isNull() || (p->IDEmpleado().value() == 0))
            return false;
    }
    return true;
}

bool PlanificacionDia::isReadyForApproval()
{
    QLOG_TRACE_FN();
    EstadosPlanificacion estado =
            m_EstadosPlanificacion.isNull()
            ? INPROGRESS
            : m_EstadosPlanificacion.value();

    return ((estado == INPROGRESS)
            && isEverythingAssigned());
}

void PlanificacionDia::updatePlanificaciones(PlanificacionSubSectorLst dataFrom)
{
    QLOG_TRACE_FN();
    DataStore::instance()->getPlanificacionesSubSectores()->updateWithOtherData(dataFrom);
}

PlanificacionSubSectorLst PlanificacionDia::getPlanificaciones()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getPlanificacionesSubSectores()->getAll(m_Dia.value(), false);
}

bool PlanificacionDia::print2(QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header

    html += "<tr>";
    html += "<td bgcolor=\"lightgray\" colspan=\"8\">";
    html += "<b><i>" + tr("Planification") + "</i></b></td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td>" + tr("Date") + "</td><td>" + Dia().value().toString("ddd dd-MM-yyyy") + "</td>";
    html += "<td>" + tr("Estimation") + "</td><td>" + QString::number(Estimacion()->EstimacionHoras().value()) + " hs </td>";
    html += "<td>" + tr("Planned") + "</td><td>" + QString::number(HorasPlanificadas()) + " hs </td>";
    html += "<td>" + tr("Status") + "</td><td>" + Estado() + "</td>";
    html += "</tr>";

    /*    html += "<tr>";
    html += "<td>" + tr("Notes") + "</td><td colspan=\"7\">" + Notas().value() + "</td>";
    html += "</tr>";*/
    html += "</table>";


    PlanificacionSubSectorLst ls = getPlanificaciones();
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Sector") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("SubSector") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Start") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("End") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employee") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Diagram") + "</i></b></font></td>";
    html += "</tr>";

    int imgNumber = 0;
    foreach(PlanificacionSubSectorPtr p, *ls)
    {
        html += "<tr>";
        if (p->getSector())
            html += "<td><font size=\"-1\">" + p->getSector()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        if (p->getSubsector())
            html += "<td><font size=\"-1\">" + p->getSubsector()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        html += "<td><font size=\"-1\">" + TimeHelper::SecondsToString(p->HoraInicio().value()) + "</font></td>";
        html += "<td><font size=\"-1\">" + TimeHelper::SecondsToString(p->HoraFin().value()) + "</font></td>";

        if (p->getEmpleado())
            html += "<td><font size=\"-1\">" + p->getEmpleado()->Apellido().value() + ", " + p->getEmpleado()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        QString img = "img%1";
        img = img.arg(imgNumber);
        html += "<td><img src=\"" + img + "\"></td>";
        QRect rect;
        rect.setWidth(500);
        rect.setHeight(24);
        QPixmap px(rect.size());
        TimeAssignment ts;
        ts.resize(rect.size());
        ts.setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
        ts.setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
        ts.setTimeLineColor(Qt::black);
        TimeAssignmentSlot t;
        t.startAssignment = p->HoraInicio().value();
        t.endAssignment = p->HoraFin().value();
        ts.addAssignment(t);
        ts.setPaintBackgroundReferences(true);
        ts.setPaintVerticalGrid(true);
        ts.setShowBackgroundText(true);
        ts.setHollowTimeLine(true);
        ts.render(&px, QPoint(), QRegion(rect));
        textDoc.addResource(QTextDocument::ImageResource, QUrl(img), px);
        imgNumber++;
        html += "</tr>";
    }
    html += "</table>";


    // Licencias
    QDate date = m_Dia.value();
    LicenciasEmpleadosLst licencias = DataStore::instance()->getLicencias()->getFrancos(date);
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Rest") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employees") + "</i></b></font>\n</td>";
    html += "</tr>";

    QStringList empleadosEnFranco;

    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        EmpleadoPtr empleado = DataStore::instance()->getEmpleados()->getEmpleado(licencia->IDEmpleado().value(), true);
        empleadosEnFranco.append(empleado->Apellido().value() + ", " + empleado->Nombre().value());
    }
    QSet<QString> francosNoDuplicados = empleadosEnFranco.toSet();
    empleadosEnFranco = francosNoDuplicados.toList();

    html += "<tr>";
    html += "<td colspan=\"2\">" + empleadosEnFranco.join("; ") + "</td>";
    html += "</tr>";

    html += "\n</table>\n<br>\n";
    textDoc.setHtml(html);
    return true;
}

QMultiMap<QString, PlanificacionSubSectorPtr> PlanificacionDia::list2map(PlanificacionSubSectorLst lst)
{
    QMultiMap<QString, PlanificacionSubSectorPtr> res;
    QString key = "%1, %2"; //"%1 %2 %3 %4";
    foreach (PlanificacionSubSectorPtr p, *lst)
    {
        QString keyEmpleado;
        QString apellido = "";
        QString nombre  = "";
        QString sector = "";
        QString subsector = "";
        EmpleadoPtr e = p->getEmpleado();
        if (!e.isNull())
        {
            apellido = e->Apellido().isNull() ? "" : e->Apellido().value();
            nombre = e->Nombre().isNull() ? "" : e->Nombre().value();
        }
        SectorPtr s = p->getSector();
        if (!s.isNull())
        {
            sector = s->Nombre().isNull() ? "" : s->Nombre().value();
        }
        SubSectorPtr ss = p->getSubsector();
        if (!ss.isNull())
        {
            subsector = ss->Nombre().isNull() ? "" : ss->Nombre().value();
        }
        keyEmpleado = key.arg(apellido, nombre, sector, subsector);
        res.insert(keyEmpleado, p);
    }
    return res;
}

bool PlanificacionDia::print(QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header

    html += "<tr>";
    html += "<td bgcolor=\"lightgray\" colspan=\"8\">";
    html += "<b><i>" + tr("Planification") + "</i></b></td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td>" + tr("Date") + "</td><td>" + Dia().value().toString("ddd dd-MM-yyyy") + "</td>";
    html += "<td>" + tr("Estimation") + "</td><td>" + QString::number(Estimacion()->EstimacionHoras().value()) + " hs </td>";
    html += "<td>" + tr("Planned") + "</td><td>" + QString::number(HorasPlanificadas()) + " hs </td>";
    html += "<td>" + tr("Status") + "</td><td>" + Estado() + "</td>";
    html += "</tr>";

    /*    html += "<tr>";
    html += "<td>" + tr("Notes") + "</td><td colspan=\"7\">" + Notas().value() + "</td>";
    html += "</tr>";*/
    html += "</table>";


    PlanificacionSubSectorLst ls = getPlanificaciones();
    QMultiMap<QString, PlanificacionSubSectorPtr> pls = list2map(ls);
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Sector") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("SubSector") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Start") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("End") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employee") + "</i></b></font></td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Diagram") + "</i></b></font></td>";
    html += "</tr>";

    int imgNumber = 0;
    QString prevKey = "";
    foreach (QString key, pls.keys())
    {
        if ((key == prevKey) && (key != ", "))
        {
            continue;
        }
        prevKey = key;
        PlanificacionSubSectorPtr p = pls.values(key).first();
        html += "<tr>";
        if (p->getSector())
            html += "<td><font size=\"-1\">" + p->getSector()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        if (p->getSubsector())
            html += "<td><font size=\"-1\">" + p->getSubsector()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        html += "<td><font size=\"-1\">" + TimeHelper::SecondsToString(p->HoraInicio().value()) + "</font></td>";
        html += "<td><font size=\"-1\">" + TimeHelper::SecondsToString(p->HoraFin().value()) + "</font></td>";

        if (p->getEmpleado())
            html += "<td><font size=\"-1\">" + p->getEmpleado()->Apellido().value() + ", " + p->getEmpleado()->Nombre().value() + "</font></td>";
        else
            html += "<td> </td>";

        QString img = "img%1";
        img = img.arg(imgNumber);
        html += "<td><img src=\"" + img + "\"></td>";
        QRect rect;
        rect.setWidth(500);
        rect.setHeight(24);
        QPixmap px(rect.size());
        TimeAssignment ts;
        ts.resize(rect.size());
        ts.setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
        ts.setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
        ts.setTimeLineColor(Qt::black);

        foreach (PlanificacionSubSectorPtr p1, pls.values(key))
        {
            TimeAssignmentSlot t;
            t.startAssignment = p1->HoraInicio().value();
            t.endAssignment = p1->HoraFin().value();
            t.idSector = p1->IDSector().value();
            t.isSubSector = p1->IDSubSector().value();
            ts.addAssignment(t);
        }
        ts.setPaintBackgroundReferences(true);
        ts.setPaintVerticalGrid(true);
        ts.setShowBackgroundText(true);
        ts.setHollowTimeLine(true);
        ts.render(&px, QPoint(), QRegion(rect));
        textDoc.addResource(QTextDocument::ImageResource, QUrl(img), px);
        imgNumber++;
        html += "</tr>";
    }
    html += "</table>";


    // Licencias
    QDate date = m_Dia.value();
    LicenciasEmpleadosLst licencias = DataStore::instance()->getLicencias()->getFrancos(date);
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Rest") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employees") + "</i></b></font>\n</td>";
    html += "</tr>";

    QStringList empleadosEnFranco;

    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        EmpleadoPtr empleado = DataStore::instance()->getEmpleados()->getEmpleado(licencia->IDEmpleado().value(), true);
        empleadosEnFranco.append(empleado->Apellido().value() + ", " + empleado->Nombre().value());
    }
    QSet<QString> francosNoDuplicados = empleadosEnFranco.toSet();
    empleadosEnFranco = francosNoDuplicados.toList();

    html += "<tr>";
    html += "<td colspan=\"2\">" + empleadosEnFranco.join("; ") + "</td>";
    html += "</tr>";

    html += "\n</table>\n<br>\n";
    textDoc.setHtml(html);
    return true;
}


bool PlanificacionDia::isPlanificacionDeleted()
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr estimacion = Estimacion();
    if (estimacion == EstimacionDiaPtr())
        return true;

    return estimacion->isDeleted(false);
}
