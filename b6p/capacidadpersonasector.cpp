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

SectorPtr CapacidadPersonaSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}

SubSectorPtr CapacidadPersonaSector::getSubSector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(m_ID_SubSector.value());
}

bool CapacidadPersonaSector::EqualsTo(CapacidadPersonaSectorPtr other)
{
    return ((m_IDEmpleado.value() == other->IDEmpleado().value())
            && (m_IDSector.value() == other->IDSector().value())
            && (m_ID_SubSector.value() == other->ID_SubSector().value()));
}

void CapacidadPersonaSector::updateWith(CapacidadPersonaSectorPtr other)
{
    if (other->Capacidad().isNull())
        m_Capacidad.setNull();
    else
        m_Capacidad.setValue(other->Capacidad().value());
}

void CapacidadPersonaSector::updateIDEmpleado(int newId)
{
    m_IDEmpleado.setValue(newId);
}

bool CapacidadPersonaSector::canWork(int IDSector, int IDSubSector)
{
    if (m_IDSector.value() != IDSector)
        return false;

    if ((IDSubSector == -1) && m_ID_SubSector.isNull())
        return true;

    return m_ID_SubSector.value() == IDSubSector;
}
