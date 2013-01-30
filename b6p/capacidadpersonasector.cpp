#include "capacidadpersonasector.h"
#include "datastore.h"

CapacidadPersonaSector::CapacidadPersonaSector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_ID_SubSector.setNull();
    m_IDEmpleado.setNull();
    m_Capacidad.setNull();

    m_IDSector.reparent(this);
    m_ID_SubSector.reparent(this);
    m_IDEmpleado.reparent(this);
    m_Capacidad.reparent(this);
}

NullableField<int> CapacidadPersonaSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> CapacidadPersonaSector::ID_SubSector()
{
    return m_ID_SubSector;
}

NullableField<int> CapacidadPersonaSector::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<int> CapacidadPersonaSector::Capacidad()
{
    return m_Capacidad;
}

void CapacidadPersonaSector::IDSector(NullableField<int> value)
{
    m_IDSector = value;
    m_IDSector.reparent(this);
}

void CapacidadPersonaSector::IDSubSector(NullableField<int> value)
{
    m_ID_SubSector = value;
    m_ID_SubSector.reparent(this);
}

void CapacidadPersonaSector::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado = value;
    m_IDEmpleado.reparent(this);
}

void CapacidadPersonaSector::Capacidad(NullableField<int> value)
{
    m_Capacidad = value;
    m_Capacidad.reparent(this);
}

SectorPtr CapacidadPersonaSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(*m_IDSector.value());
}

SubSectorPtr CapacidadPersonaSector::getSubSector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(*m_ID_SubSector.value());
}
