#include "planificaciondia.h"
#include "datastore.h"
#include "planificacionsubsector.h"

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
    RecordPtr res(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["Notas"] = m_Notas.toVariant();
    (*res)["IDSupervisor"] = m_IDSupervisor.toVariant();

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

EmpleadoPtr PlanificacionDia::Supervisor()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDSupervisor.value());
}

EstimacionDiaPtr PlanificacionDia::Estimacion()
{
    return DataStore::instance()->getEstimacionesDias()->get(m_Dia.value());
}

int PlanificacionDia::HorasPlanificadas()
{
    PlanificacionSubSectorLst planificaciones =
            DataStore::instance()->getPlanificacionesSubSectores()->getAll(this->Dia().value());

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
        res = inProgress;
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

void PlanificacionDia::updatePlanificaciones(PlanificacionSubSectorLst dataFrom)
{
    DataStore::instance()->getPlanificacionesSubSectores()->updateWithOtherData(dataFrom);
}
