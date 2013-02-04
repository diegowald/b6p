#include "planificacionesdias.h"

PlanificacionesDias::PlanificacionesDias(QObject *parent) :
    ACollection(tr("Days Planifications"), parent)
{
}

QString PlanificacionesDias::getSqlString()
{
    return "select Dia, Notas, IDSupervisor from planificaciondia;";
}

void PlanificacionesDias::addRecord(Record &record)
{
    PlanificacionDiaPtr p(new PlanificacionDia(this));

    p->Dia().setValue(record["Dia"].toDate());
    p->Notas().setValue(record["Notas"].toString());
    p->IDSupervisor().setValue(record["IDSupervisor"].toInt());
    p->setInitialized();

    m_Planificaciones[p->Dia().value()] = p;
}

QString PlanificacionesDias::getDeleteStatement()
{
    return "delete from planificaciondia where Dia = :Dia;";
}

QString PlanificacionesDias::getUpdateStatement()
{
    return "update planificaciondia set Notas = :Notas, IDSupervisor = :IDSupervisor where Dia = :Dia;";
}

QString PlanificacionesDias::getInsertStatement()
{
    return "insert into planificaciondia "
            " (Dia, Notas, IDSupervisor) "
            " values "
            " (:Dia, :Notas, :IDSupervisor);";
}

RecordSet PlanificacionesDias::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        switch (status)
        {
        case NEW:
            if (p->isNew())
                res->push_back(p->asRecordPtr());
            break;
        case MODIFIED:
            if (p->isModified())
                res->push_back(p->asRecordPtr());
            break;
        case DELETED:
            if (p->isDeleted())
                res->push_back(p->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

void PlanificacionesDias::defineHeaders(QStringList &list)
{
}

void PlanificacionesDias::fillData(QTreeWidget &tree)
{
}

bool PlanificacionesDias::addNew()
{
}

bool PlanificacionesDias::edit(QVariant ID)
{
}

bool PlanificacionesDias::deleteElement(QVariant ID)
{
}
