#include "subsector.h"
#include "datastore.h"
#include <QsLog.h>


SubSector::SubSector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();

    m_IDSector.setParent(this);
    m_IDSubSector.setParent(this);
    m_Nombre.setParent(this);
    m_Descripcion.setParent(this);

}

RecordPtr SubSector::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_IDSubSector.toVariant();
    (*res)["Nombre"] = m_Nombre.toVariant();
    (*res)["Descripcion"] = m_Descripcion.toVariant();

    (*res)[RECORD_ID] = m_IDSubSector.toVariant();
    return res;
}

bool SubSector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["IDSubSector"] == m_IDSubSector.toVariant())
            && ((*record)["Nombre"] == m_Nombre.toVariant())
            && ((*record)["Descripcion"] == m_Descripcion.toVariant());
    return res;
}

NullableField<int> &SubSector::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<int> &SubSector::IDSubsector()
{
    QLOG_TRACE_FN();
    return m_IDSubSector;
}

NullableField<QString> &SubSector::Nombre()
{
    QLOG_TRACE_FN();
    return m_Nombre;
}

NullableField<QString> &SubSector::Descripcion()
{
    QLOG_TRACE_FN();
    return m_Descripcion;
}

SectorPtr SubSector::getSector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}
