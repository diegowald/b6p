#include "planificacionesdiassubsectores.h"

PlanificacionesDiasSubSectores::PlanificacionesDiasSubSectores(QObject *parent) :
    ACollection(tr("Planifications of Sectors and subsectors for a day"), parent)
{
}

QString PlanificacionesDiasSubSectores::getSqlString()
{
    return "select Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin from planificacionsubsector;";
}

void PlanificacionesDiasSubSectores::addRecord(Record &record)
{
    PlanificacionSubSectorPtr p(new PlanificacionSubSector(this));

    p->Dia().setValue(record["Dia"].toDate());
    p->IDSector().setValue(record["IDSector"].toInt());
    p->IDSubSector().setValue(record["IDSubsector"].toInt());
    p->IDEmpleado().setValue(record["IDEmpleado"].toInt());
    p->HoraInicio().setValue(record["HoraInicio"].toTime());
    p->HoraFin().setValue(record["HoraFin"].toTime());
    p->setInitialized();

    m_Planificacion.push_back(p);
}

QString PlanificacionesDiasSubSectores::getDeleteStatement()
{
    return "delete from planificacionsubsector where "
            " Dia = :Dia, IDSector = :IDSector, IDSubSector = :IDSubSector, "
            " IDEmpleado = :IDEmpleado, HoraInicio = :HoraInicio, HoraFin = :HoraFin;";
}

QString PlanificacionesDiasSubSectores::getUpdateStatement()
{
    return "";
}

QString PlanificacionesDiasSubSectores::getInsertStatement()
{
    return "insert into planificacionsubsector "
            " (Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin) "
            " values "
            " (:Dia, :IDSector, :IDSubsector, :IDEmpleado, :HoraInicio, :HoraFin);";
}

RecordSet PlanificacionesDiasSubSectores::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
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

void PlanificacionesDiasSubSectores::defineHeaders(QStringList &list)
{
}

void PlanificacionesDiasSubSectores::fillData(QTreeWidget &tree)
{
}

bool PlanificacionesDiasSubSectores::addNew()
{
}

bool PlanificacionesDiasSubSectores::edit(QVariant ID)
{
}

bool PlanificacionesDiasSubSectores::deleteElement(QVariant ID)
{
}
