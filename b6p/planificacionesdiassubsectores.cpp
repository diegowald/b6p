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

    p->Dia(NullableField<QDate>(record["Dia"].toDate()));
    p->IDSector(NullableField<int>(record["IDSector"].toInt()));
    p->IDSubSector(NullableField<int>(record["IDSubsector"].toInt()));
    p->IDEmpleado(NullableField<int>(record["IDEmpleado"].toInt()));
    p->HoraInicio(NullableField<QTime>(record["HoraInicio"].toTime()));
    p->HoraFin(NullableField<QTime>(record["HoraFin"].toTime()));

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

void PlanificacionesDiasSubSectores::edit(QVariant ID)
{
}

void PlanificacionesDiasSubSectores::deleteElement(QVariant ID)
{
}
