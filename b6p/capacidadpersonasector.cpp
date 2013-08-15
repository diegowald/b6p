#include "capacidadpersonasector.h"
#include "datastore.h"
#include <QsLog.h>


CapacidadPersonaSector::CapacidadPersonaSector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_ID_SubSector.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["Capacidad"] = m_Capacidad.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();

    return res;
}

bool CapacidadPersonaSector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["IDSubSector"] == m_ID_SubSector.toVariant())
            && ((*record)["IDEmpleado"] == m_IDEmpleado.toVariant())
            && ((*record)["Capacidad"] == m_Capacidad.toVariant());
    return res;
}

NullableField<int> &CapacidadPersonaSector::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<int> &CapacidadPersonaSector::ID_SubSector()
{
    QLOG_TRACE_FN();
    return m_ID_SubSector;
}

NullableField<int> &CapacidadPersonaSector::IDEmpleado()
{
    QLOG_TRACE_FN();
    return m_IDEmpleado;
}

NullableField<int> &CapacidadPersonaSector::Capacidad()
{
    QLOG_TRACE_FN();
    return m_Capacidad;
}

SectorPtr CapacidadPersonaSector::getSector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}

SubSectorPtr CapacidadPersonaSector::getSubSector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSubSectores()->getSubSector(m_ID_SubSector.value());
}

bool CapacidadPersonaSector::EqualsTo(CapacidadPersonaSectorPtr other)
{
    QLOG_TRACE_FN();
    return ((m_IDEmpleado.value() == other->IDEmpleado().value())
            && (m_IDSector.value() == other->IDSector().value())
            && (m_ID_SubSector.value() == other->ID_SubSector().value()));
}

void CapacidadPersonaSector::updateWith(CapacidadPersonaSectorPtr other)
{
    QLOG_TRACE_FN();
    if (other->Capacidad().isNull())
        m_Capacidad.setNull();
    else
        m_Capacidad.setValue(other->Capacidad().value());
}

void CapacidadPersonaSector::updateIDEmpleado(int newId)
{
    QLOG_TRACE_FN();
    m_IDEmpleado.setValue(newId);
}

bool CapacidadPersonaSector::canWork(int IDSector, int IDSubSector)
{
    QLOG_TRACE_FN();
    if (m_IDSector.value() != IDSector)
        return false;

    if ((IDSubSector == -1) && (m_ID_SubSector.isNull() || m_ID_SubSector.value() == 0))
        return true;

    return m_ID_SubSector.value() == IDSubSector;
}
