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

double PlanificacionSubSector::CantidadHoras()
{
    if (m_HoraFin.isNull())
        return 0;
    if (m_HoraInicio.isNull())
        return 0;
    QDateTime inicio(QDateTime::currentDateTime().date(), m_HoraInicio.value());
    QDateTime fin(QDateTime::currentDateTime().date(), m_HoraFin.value());
    qlonglong delta = fin.toMSecsSinceEpoch() - inicio.toMSecsSinceEpoch();
    double cantHoras = delta / 1000.0 / 3600.0;
    return cantHoras;
}

bool PlanificacionSubSector::isEqualsTo(PlanificacionSubSectorPtr other)
{
    if (m_Dia.value() != other->Dia().value())
        return false;

    if (m_IDSector.value() != other->IDSector().value())
        return false;

    if (m_IDSubSector.value() != other->IDSubSector().value())
        return false;

    return true;
}

void PlanificacionSubSector::updateWith(PlanificacionSubSectorPtr other)
{
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
}
