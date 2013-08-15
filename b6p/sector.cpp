#include "sector.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>


Sector::Sector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();
    m_ShowInPlanification.setNull();

    m_IDSector.setParent(this);
    m_Nombre.setParent(this);
    m_Descripcion.setParent(this);
    m_ShowInPlanification.setParent(this);
}

RecordPtr Sector::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["Nombre"] = m_Nombre.toVariant();
    (*res)["Descripcion"] = m_Descripcion.toVariant();
    (*res)["showInPlanification"] = m_ShowInPlanification.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();

    (*res)[RECORD_ID] = m_IDSector.toVariant();

    return res;
}

bool Sector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["Nombre"] == m_Nombre.toVariant())
            && ((*record)["Descripcion"] == m_Descripcion.toVariant())
            && ((*record)["showInPlanification"] == m_ShowInPlanification.toVariant());
    return res;
}

NullableField<int> &Sector::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<QString> &Sector::Nombre()
{
    QLOG_TRACE_FN();
    return m_Nombre;
}

NullableField<QString> &Sector::Descripcion()
{
    QLOG_TRACE_FN();
    return m_Descripcion;
}

NullableField<bool> &Sector::ShowInPlanification()
{
    QLOG_TRACE_FN();
    return m_ShowInPlanification;
}
