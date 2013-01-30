#include "calendariopersona.h"
#include "datastore.h"

CalendarioPersona::CalendarioPersona(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_IDEmpleado.setNull();
    m_HoraIngreso.setNull();
    m_HoraEgreso.setNull();

    m_Dia.reparent(this);
    m_IDEmpleado.reparent(this);
    m_HoraIngreso.reparent(this);
    m_HoraEgreso.reparent(this);
}

NullableField<int> CalendarioPersona::Dia()
{
    return m_Dia;
}

NullableField<int> CalendarioPersona::IDEmpleado()
{
    return m_IDEmpleado;
}

NullableField<QTime> CalendarioPersona::HoraIngreso()
{
    return m_HoraIngreso;
}

NullableField<QTime> CalendarioPersona::HoraEgreso()
{
    return m_HoraEgreso;
}

void CalendarioPersona::Dia(NullableField<int> value)
{
    m_Dia = value;
    m_Dia.reparent(this);
}

void CalendarioPersona::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado = value;
    m_IDEmpleado.reparent(this);
}

void CalendarioPersona::HoraIngreso(NullableField<QTime> value)
{
    m_HoraIngreso = value;
    m_HoraIngreso.reparent(this);
}

void CalendarioPersona::HoraEgreso(NullableField<QTime> value)
{
    m_HoraEgreso = value;
    m_HoraEgreso.reparent(this);
}
