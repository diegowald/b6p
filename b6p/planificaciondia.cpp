#include "planificaciondia.h"
#include "datastore.h"
#include "planificacionsubsector.h"
#include <QDateTime>
#include "timehelper.h"

//Printing
#include "timeassignment.h"
#include <QUrl>


PlanificacionDia::PlanificacionDia(QDate date, QObject *parent) :
    QObject(parent)
{
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
    RecordPtr res = boost::make_shared<Record>();

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["Notas"] = m_Notas.toVariant();
    (*res)["IDSupervisor"] = m_IDSupervisor.toVariant();
    (*res)["EstadoPlanificacion"] = m_EstadosPlanificacion.toVariant();

    return res;
}

NullableField<QDate> &PlanificacionDia::Dia()
{
    return m_Dia;
}

NullableField<QString> &PlanificacionDia::Notas()
{
    return m_Notas;
}

NullableField<int> &PlanificacionDia::IDSupervisor()
{
    return m_IDSupervisor;
}

NullableField<EstadosPlanificacion> &PlanificacionDia::EstadoPlanificacion()
{
    return m_EstadosPlanificacion;
}

EmpleadoPtr PlanificacionDia::Supervisor()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDSupervisor.value(), false);
}

EstimacionDiaPtr PlanificacionDia::Estimacion()
{
    return DataStore::instance()->getEstimacionesDias()->get(m_Dia.value(), false);
}

int PlanificacionDia::HorasPlanificadas()
{
    PlanificacionSubSectorLst planificaciones =
            DataStore::instance()->getPlanificacionesSubSectores()->getAll(this->Dia().value(), false);

    double total = 0;

    foreach(PlanificacionSubSectorPtr p, *planificaciones)
    {
        total += p->CantidadHoras();
    }
    return total;
}

QString PlanificacionDia::Estado()
{
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
    if (isReadyForApproval())
        m_EstadosPlanificacion.setValue(APPROVED);
}

bool PlanificacionDia::isEverythingAssigned()
{
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
    EstadosPlanificacion estado =
            m_EstadosPlanificacion.isNull()
            ? INPROGRESS
            : m_EstadosPlanificacion.value();

    return ((estado == INPROGRESS)
            && isEverythingAssigned());
}

void PlanificacionDia::updatePlanificaciones(PlanificacionSubSectorLst dataFrom)
{
    DataStore::instance()->getPlanificacionesSubSectores()->updateWithOtherData(dataFrom);
}

PlanificacionSubSectorLst PlanificacionDia::getPlanificaciones()
{
    return DataStore::instance()->getPlanificacionesSubSectores()->getAll(m_Dia.value(), false);
}

bool PlanificacionDia::print(QTextDocument &textDoc)
{
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header

    html += "<tr>";
    //html += "<td bgcolor=\"lightgray\" colspan=\"8\"><font size=\"+1\">";
    html += "<td bgcolor=\"lightgray\" colspan=\"8\">";
    html += "<b><i>" + tr("Planification") + "</i></b>\n</td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td>" + tr("Date") + "</td><td>" + Dia().value().toString() + "</td>";
    html += "<td>" + tr("Estimation") + "</td><td>" + QString::number(Estimacion()->EstimacionHoras().value()) + " hs </td>";
    html += "<td>" + tr("Planned") + "</td><td>" + QString::number(HorasPlanificadas()) + " hs </td>";
    html += "<td>" + tr("Status") + "</td><td>" + Estado() + "</td>";
    html += "</tr>";

    html += "<tr>";
    html += "<td>" + tr("Notes") + "</td><td colspan=\"7\">" + Notas().value() + "</td>";
    html += "</tr>";
    html += "</table>";


    PlanificacionSubSectorLst ls = getPlanificaciones();
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Sector") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("SubSector") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Start") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("End") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employee") + "</i></b></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<b><i>" + tr("Diagram") + "</i></b></font>\n</td>";
    html += "</tr>";

    int imgNumber = 0;
    foreach(PlanificacionSubSectorPtr p, *ls)
    {
        html += "<tr>";
        if (p->getSector())
            html += "<td>" + p->getSector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        if (p->getSubsector())
            html += "<td>" + p->getSubsector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        html += "<td>" + TimeHelper::SecondsToString(p->HoraInicio().value()) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(p->HoraFin().value()) + "</td>";

        if (p->getEmpleado())
            html += "<td>" + p->getEmpleado()->Apellido().value() + ", " + p->getEmpleado()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

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
        ts.setTimeLineColor(Qt::black);
        ts.setStartAssignment(p->HoraInicio().value());
        ts.setEndAssignment(p->HoraFin().value());
        ts.setPaintBackgroundReferences(true);
        ts.setPaintVerticalGrid(true);
        ts.setShowBackgroundText(true);
        ts.setHollowTimeLine(true);
        ts.render(&px, QPoint(), QRegion(rect));
        textDoc.addResource(QTextDocument::ImageResource, QUrl(img), px);
        imgNumber++;
        html += "</tr>";
    }

    html += "\n</table>\n<br>\n";
    textDoc.setHtml(html);
    return true;
}
