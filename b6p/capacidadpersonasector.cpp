#include "capacidadpersonasector.h"
#include "datastore.h"

CapacidadPersonaSector::CapacidadPersonaSector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_ID_SubSector.setNull();
    m_IDEmpleado.setNull();
    m_Capacidad.setNull();

    m_IDSector.setParent(this);
    m_ID_SubSector.setParent(this);
    m_IDEmpleado.setParent(this);
    m_Capacidad.setParent(this);
}

RecordPtr CapacidadPersonaSector::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_ID_SubSector.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["Capacidad"] = m_Capacidad.toVariant();

    return res;
}

NullableField<int> &CapacidadPersonaSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> &CapacidadPersonaSector::ID_SubSector()
{
    return m_ID_SubSector;
}

NullableField<int> &CapacidadPersonaSector::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<int> &CapacidadPersonaSector::Capacidad()
{
    return m_Capacidad;
}

/*void CapacidadPersonaSector::IDSector(NullableField<int> value)
{
    m_IDSector.setValue(value);
}

void CapacidadPersonaSector::IDSubSector(NullableField<int> value)
{
    m_ID_SubSector.setValue(value);
}

void CapacidadPersonaSector::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado.setValue(value);
}

void CapacidadPersonaSector::Capacidad(NullableField<int> value)
{
    m_Capacidad.setValue(value);
}*/

SectorPtr CapacidadPersonaSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}

SubSectorPtr CapacidadPersonaSector::getSubSector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(m_ID_SubSector.value());
}
