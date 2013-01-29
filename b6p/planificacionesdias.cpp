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

    p->Dia(NullableField<QDate>(record["Dia"].toDate()));
    p->Notas(NullableField<QString>(record["Notas"].toString()));
    p->IDSupervisor(NullableField<int>(record["IDSupervisor"].toInt()));

    m_Planificaciones[*p->Dia().value()] = p;
}

void PlanificacionesDias::saveData()
{
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

void PlanificacionesDias::edit(QVariant ID)
{
}

void PlanificacionesDias::deleteElement(QVariant ID)
{
}
