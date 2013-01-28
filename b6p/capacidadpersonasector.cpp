#include "capacidadpersonasector.h"
#include "datastore.h"

CapacidadPersonaSector::CapacidadPersonaSector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_ID_SubSector.setNull();
    m_IDEmpleado.setNull();
    m_Capacidad.setNull();
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

NullableField<float> CapacidadPersonaSector::Capacidad()
{
    return m_Capacidad;
}

void CapacidadPersonaSector::IDSector(NullableField<int> value)
{
    m_IDSector = value;
}

void CapacidadPersonaSector::IDSubSector(NullableField<int> value)
{
    m_ID_SubSector = value;
}

void CapacidadPersonaSector::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado = value;
}

void CapacidadPersonaSector::Capacidad(NullableField<float> value)
{
    m_Capacidad = value;
}

SectorPtr CapacidadPersonaSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(*m_IDSector.value());
}

SubSectorPtr CapacidadPersonaSector::getSubSector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(*m_ID_SubSector.value());
}

EmpleadoPtr CapacidadPersonaSector::getEmpleado()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(*m_IDEmpleado.value());
}
