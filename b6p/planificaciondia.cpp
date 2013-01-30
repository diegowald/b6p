#include "planificaciondia.h"
#include "datastore.h"

PlanificacionDia::PlanificacionDia(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_Notas.setNull();
    m_IDSupervisor.setNull();

    m_Dia.reparent(this);
    m_Notas.reparent(this);
    m_IDSupervisor.reparent(this);
}

NullableField<QDate> PlanificacionDia::Dia()
{
    return m_Dia;
}

NullableField<QString> PlanificacionDia::Notas()
{
    return m_Notas;
}

NullableField<int> PlanificacionDia::IDSupervisor()
{
    return m_IDSupervisor;
}

void PlanificacionDia::Dia(NullableField<QDate> value)
{
    m_Dia = value;
    m_Dia.reparent(this);
}

void PlanificacionDia::Notas(NullableField<QString> value)
{
    m_Notas = value;
    m_Notas.reparent(this);
}

void PlanificacionDia::IDSupervisor(NullableField<int> value)
{
    m_IDSupervisor = value;
    m_IDSupervisor.reparent(this);
}

EmpleadoPtr PlanificacionDia::getSupervisor()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(*m_IDSupervisor.value());
}
