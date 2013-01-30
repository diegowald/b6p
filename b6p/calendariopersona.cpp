#include "calendariopersona.h"
#include "datastore.h"

CalendarioPersona::CalendarioPersona(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_IDEmpleado.setNull();
    m_HoraIngreso.setNull();
    m_HoraEgreso.setNull();

    m_Dia.setParent(this);
    m_IDEmpleado.setParent(this);
    m_HoraIngreso.setParent(this);
    m_HoraEgreso.setParent(this);
}

RecordPtr CalendarioPersona::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["HoraIngreso"] = m_HoraIngreso.toVariant();
    (*res)["HoraEgreso"] = m_HoraEgreso.toVariant();

    return res;
}

NullableField<int> &CalendarioPersona::Dia()
{
    return m_Dia;
}

NullableField<int> &CalendarioPersona::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<QTime> &CalendarioPersona::HoraIngreso()
{
    return m_HoraIngreso;
}

NullableField<QTime> &CalendarioPersona::HoraEgreso()
{
    return m_HoraEgreso;
}

/*void CalendarioPersona::Dia(NullableField<int> value)
{
    m_Dia.setValue(value);
}

void CalendarioPersona::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado.setValue(value);
}

void CalendarioPersona::HoraIngreso(NullableField<QTime> value)
{
    m_HoraIngreso.setValue(value);
}

void CalendarioPersona::HoraEgreso(NullableField<QTime> value)
{
    m_HoraEgreso.setValue(value);
}*/
