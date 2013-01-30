#include "estimaciondia.h"

EstimacionDia::EstimacionDia(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_EstimacionHoras.setNull();

    m_Dia.reparent(this);
    m_EstimacionHoras.reparent(this);
}

RecordPtr EstimacionDia::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["EstimacionHoras"] = m_EstimacionHoras.toVariant();

    return res;
}

NullableField<QDate> EstimacionDia::Dia()
{
    return m_Dia;
}

NullableField<int> EstimacionDia::EstimacionHoras()
{
    return m_EstimacionHoras;
}

void EstimacionDia::Dia(NullableField<QDate> value)
{
    m_Dia = value;
    m_Dia.reparent(this);
}

void EstimacionDia::EstimacionHoras(NullableField<int> value)
{
    m_EstimacionHoras = value;
    m_EstimacionHoras.reparent(this);
}
