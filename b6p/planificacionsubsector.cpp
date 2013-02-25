#include "planificacionsubsector.h"
#include "datastore.h"

PlanificacionSubSector::PlanificacionSubSector(QObject *parent) :
    QObject(parent)
{
    m_IDRecord.setNull();
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

    (*res)["IDRecord"] = m_IDRecord.toVariant();
    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_IDSubSector.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["HoraInicio"] = m_HoraInicio.toVariant();
    (*res)["HoraFin"] = m_HoraFin.toVariant();

    (*res)[RECORD_ID] = m_IDRecord.toVariant();

    return res;
}

NullableField<int> &PlanificacionSubSector::IDRecord()
{
    return m_IDRecord;
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

NullableField<int> &PlanificacionSubSector::HoraInicio()
{
    return m_HoraInicio;
}

NullableField<int> &PlanificacionSubSector::HoraFin()
{
    return m_HoraFin;
}

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
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDEmpleado.value(), false);
}

double PlanificacionSubSector::CantidadHoras()
{
    if (m_HoraFin.isNull())
        return 0;
    if (m_HoraInicio.isNull())
        return 0;
    return m_HoraFin.value() - m_HoraInicio.value();
}

bool PlanificacionSubSector::isEqualsTo(PlanificacionSubSectorPtr other)
{
    return (m_IDRecord.value() == other->IDRecord().value());
}

void PlanificacionSubSector::updateWith(PlanificacionSubSectorPtr other)
{
    if (other->Dia().isNull())
        m_Dia.setNull();
    else
        m_Dia.setValue(other->Dia().value());

    if (other->IDSector().isNull())
        m_IDSector.setNull();
    else
        m_IDSector.setValue(other->IDSector().value());

    if (other->IDSubSector().isNull())
        m_IDSubSector.setNull();
    else
        m_IDSubSector.setValue(other->IDSubSector().value());

    if (other->IDEmpleado().isNull())
        m_IDEmpleado.setNull();
    else
        m_IDEmpleado.setValue(other->IDEmpleado().value());

    if (other->HoraInicio().isNull())
        m_HoraInicio.setNull();
    else
        m_HoraInicio.setValue(other->HoraInicio().value());

    if (other->HoraFin().isNull())
        m_HoraFin.setNull();
    else
        m_HoraFin.setValue(other->HoraFin().value());
//    setNew();
}

void PlanificacionSubSector::updateID(int newID)
{
    m_IDRecord.setValue(newID);
    setUnmodified();
}
