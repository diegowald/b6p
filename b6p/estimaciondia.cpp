#include "estimaciondia.h"
#include "datastore.h"

EstimacionDia::EstimacionDia(bool isNew, QObject *parent) :
    QObject(parent)
{
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
    RecordPtr res(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["HorasEstimadas"] = m_EstimacionHoras.toVariant();

    return res;
}

NullableField<QDate> &EstimacionDia::Dia()
{
    return m_Dia;
}

NullableField<int> &EstimacionDia::EstimacionHoras()
{
    return m_EstimacionHoras;
}

/*void EstimacionDia::Dia(NullableField<QDate> value)
{
    m_Dia.setValue(value);
}

void EstimacionDia::EstimacionHoras(NullableField<int> value)
{
    m_EstimacionHoras.setValue(value);
}
*/

bool EstimacionDia::isPlanned()
{
    return (DataStore::instance()->getPlanificacionesDias()->getByDay(m_Dia.value()) != PlanificacionDiaPtr());
}
