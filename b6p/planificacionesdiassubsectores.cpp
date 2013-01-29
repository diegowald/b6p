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

void PlanificacionesDiasSubSectores::saveData()
{
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
