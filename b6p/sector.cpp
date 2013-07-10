#include "sector.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>


Sector::Sector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE() << "Sector::Sector(QObject *parent)";
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
    QLOG_TRACE() << "RecordPtr Sector::asRecordPtr()";
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["Nombre"] = m_Nombre.toVariant();
    (*res)["Descripcion"] = m_Descripcion.toVariant();
    (*res)["showInPlanification"] = m_ShowInPlanification.toVariant();

    (*res)[RECORD_ID] = m_IDSector.toVariant();

    return res;
}

bool Sector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE() << "bool Sector::isEqualsTo(RecordPtr record)";
    bool res = ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["Nombre"] == m_Nombre.toVariant())
            && ((*record)["Descripcion"] == m_Descripcion.toVariant())
            && ((*record)["showInPlanification"] == m_ShowInPlanification.toVariant());
    return res;
}

NullableField<int> &Sector::IDSector()
{
    QLOG_TRACE() << "NullableField<int> &Sector::IDSector()";
    return m_IDSector;
}

NullableField<QString> &Sector::Nombre()
{
    QLOG_TRACE() << "NullableField<QString> &Sector::Nombre()";
    return m_Nombre;
}

NullableField<QString> &Sector::Descripcion()
{
    QLOG_TRACE() << "NullableField<QString> &Sector::Descripcion()";
    return m_Descripcion;
}

NullableField<bool> &Sector::ShowInPlanification()
{
    QLOG_TRACE() << "NullableField<bool> &Sector::ShowInPlanification()";
    return m_ShowInPlanification;
}
