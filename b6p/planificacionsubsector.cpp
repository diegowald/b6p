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

    m_Dia.setParent(this);
    m_IDSector.setParent(this);
    m_IDSubSector.setParent(this);
    m_IDEmpleado.setParent(this);
    m_HoraInicio.setParent(this);
    m_HoraFin.setParent(this);
}

RecordPtr PlanificacionSubSector::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_IDSubSector.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["HoraInicio"] = m_HoraInicio.toVariant();
    (*res)["HoraFin"] = m_HoraFin.toVariant();

    return res;
}

NullableField<QDate> &PlanificacionSubSector::Dia()
{
    return m_Dia;
}

NullableField<int> &PlanificacionSubSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> &PlanificacionSubSector::IDSubSector()
{
    return m_IDSubSector;
}

NullableField<int> &PlanificacionSubSector::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<QTime> &PlanificacionSubSector::HoraInicio()
{
    return m_HoraInicio;
}

NullableField<QTime> &PlanificacionSubSector::HoraFin()
{
    return m_HoraFin;
}

/*void PlanificacionSubSector::Dia(NullableField<QDate> value)
{
    m_Dia.setValue(value);
}

void PlanificacionSubSector::IDSector(NullableField<int> value)
{
    m_IDSector.setValue(value);
}

void PlanificacionSubSector::IDSubSector(NullableField<int> value)
{
    m_IDSubSector.setValue(value);
}

void PlanificacionSubSector::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado.setValue(value);
}

void PlanificacionSubSector::HoraInicio(NullableField<QTime> value)
{
    m_HoraInicio.setValue(value);
}

void PlanificacionSubSector::HoraFin(NullableField<QTime> value)
{
    m_HoraFin.setValue(value);
}*/

SectorPtr PlanificacionSubSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}

SubSectorPtr PlanificacionSubSector::getSubsector()
{
    return DataStore::instance()->getSubSectores()->getSubSector(m_IDSubSector.value());
}

EmpleadoPtr PlanificacionSubSector::getEmpleado()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDEmpleado.value());
}
