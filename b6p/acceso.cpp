#include "acceso.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>

Acceso::Acceso(QObject *parent) : QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDSector.setNull();
    m_Feature.setNull();
    m_canRead.setNull();
    m_canCreate.setNull();
    m_canUpdate.setNull();
    m_canDelete.setNull();

    m_IDSector.setParent(this);
    m_Feature.setParent(this);
    m_canRead.setParent(this);
    m_canCreate.setParent(this);
    m_canUpdate.setParent(this);
    m_canDelete.setParent(this);
}

Acceso::~Acceso()
{
    QLOG_TRACE_FN();
}

RecordPtr Acceso::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["Feature"] = m_Feature.toVariant();
    (*res)["canRead"] = m_canRead.toVariant();
    (*res)["canCreate"] = m_canCreate.toVariant();
    (*res)["canUpdate"] = m_canUpdate.toVariant();
    (*res)["canDelete"] = m_canDelete.toVariant();

    return res;
}

NullableField<int> &Acceso::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<QString> &Acceso::Feature()
{
    QLOG_TRACE_FN();
    return m_Feature;
}

NullableField<bool> &Acceso::canRead()
{
    QLOG_TRACE_FN();
    return m_canRead;
}

NullableField<bool> &Acceso::canCreate()
{
    QLOG_TRACE_FN();
    return m_canCreate;
}

NullableField<bool> &Acceso::canUpdate()
{
    QLOG_TRACE_FN();
    return m_canUpdate;
}

NullableField<bool> &Acceso::canDelete()
{
    QLOG_TRACE_FN();
    return m_canDelete;
}


bool Acceso::CanRead()
{
    QLOG_TRACE_FN();
    return m_canRead.isNull() ? false : m_canRead.value();
}

bool Acceso::CanCreate()
{
    QLOG_TRACE_FN();
    return m_canCreate.isNull() ? false : m_canCreate.value();
}

bool Acceso::CanUpdate()
{
    QLOG_TRACE_FN();
    return m_canUpdate.isNull() ? false : m_canUpdate.value();
}

bool Acceso::CanDelete()
{
    QLOG_TRACE_FN();
    return m_canDelete.isNull() ? false : m_canDelete.value();
}
