#include "planificacionsubsector.h"
#include "datastore.h"

PlanificacionSubSector::PlanificacionSubSector(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_IDEmpleado.setNull();
    m_HoraInicio.setNull();
    m_HoraFin.setNull();

    m_Dia.reparent(this);
    m_IDSector.reparent(this);
    m_IDSubSector.reparent(this);
    m_IDEmpleado.reparent(this);
    m_HoraInicio.reparent(this);
    m_HoraFin.reparent(this);
}


NullableField<QDate> PlanificacionSubSector::Dia()
{
    return m_Dia;
}

NullableField<int> PlanificacionSubSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> PlanificacionSubSector::IDSubSector()
{
    return m_IDSubSector;
}

NullableField<int> PlanificacionSubSector::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<QTime> PlanificacionSubSector::HoraInicio()
{
    return m_HoraInicio;
}

NullableField<QTime> PlanificacionSubSector::HoraFin()
{
    return m_HoraFin;
}

void PlanificacionSubSector::Dia(NullableField<QDate> value)
{
    m_Dia = value;
}

void PlanificacionSubSector::IDSector(NullableField<int> value)
{
    m_IDSector = value;
}

void PlanificacionSubSector::IDSubSector(NullableField<int> value)
{
    m_IDSubSector = value;
}

void PlanificacionSubSector::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado = value;
}

void PlanificacionSubSector::HoraInicio(NullableField<QTime> value)
{
    m_HoraInicio = value;
}

void PlanificacionSubSector::HoraFin(NullableField<QTime> value)
{
    m_HoraFin = value;
}

SectorPtr PlanificacionSubSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(*m_IDSector.value());
}

SubSectorPtr PlanificacionSubSector::getSubsector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(*m_IDSubSector.value());
}

EmpleadoPtr PlanificacionSubSector::getEmpleado()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(*m_IDEmpleado.value());
}
