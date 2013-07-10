#include "estimaciondia.h"
#include "datastore.h"
#include <QsLog.h>

EstimacionDia::EstimacionDia(bool isNew, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE() << "EstimacionDia::EstimacionDia(bool isNew, QObject *parent)";
    m_Dia.setNull();
    m_EstimacionHoras.setNull();

    m_Dia.setParent(this);
    m_EstimacionHoras.setParent(this);

    if (isNew)
    {
        m_Dia.setValue(QDateTime::fromMSecsSinceEpoch(0).date());
        m_EstimacionHoras.setValue(0);
        setNew();
    }
}

RecordPtr EstimacionDia::asRecordPtr()
{
    QLOG_TRACE() << "RecordPtr EstimacionDia::asRecordPtr()";
    RecordPtr res = boost::make_shared<Record>();

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["HorasEstimadas"] = m_EstimacionHoras.toVariant();

    return res;
}

bool EstimacionDia::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE() << "bool EstimacionDia::isEqualsTo(RecordPtr record)";
    bool res = ((*record)["Dia"] == m_Dia.toVariant())
            && ((*record)["HorasEstimadas"] == m_EstimacionHoras.toVariant());
    return res;
}

NullableField<QDate> &EstimacionDia::Dia()
{
    QLOG_TRACE() << "NullableField<QDate> &EstimacionDia::Dia()";
    return m_Dia;
}

NullableField<int> &EstimacionDia::EstimacionHoras()
{
    QLOG_TRACE() << "NullableField<int> &EstimacionDia::EstimacionHoras()";
    return m_EstimacionHoras;
}

bool EstimacionDia::isPlanned()
{
    QLOG_TRACE() << "bool EstimacionDia::isPlanned()";
    return (DataStore::instance()->getPlanificacionesDias()->getByDay(m_Dia.value(), false) != PlanificacionDiaPtr());
}

bool EstimacionDia::canBeDeleted()
{
    QLOG_TRACE() << "bool EstimacionDia::canBeDeleted()";
    return true;
}
