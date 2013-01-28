#include "calendariopersona.h"
#include "datastore.h"

CalendarioPersona::CalendarioPersona(QObject *parent) :
    QObject(parent)
{
    m_Dia.setNull();
    m_IDEmpleado.setNull();
    m_HoraIngreso.setNull();
    m_HoraEgreso.setNull();
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
}

void CalendarioPersona::IDEmpleado(NullableField<int> value)
{
    m_IDEmpleado = value;
}

void CalendarioPersona::HoraIngreso(NullableField<QTime> value)
{
    m_HoraIngreso = value;
}

void CalendarioPersona::HoraEgreso(NullableField<QTime> value)
{
    m_HoraEgreso = value;
}

EmpleadoPtr CalendarioPersona::getEmpleado()
{
    return DataStore::instance()->getEmpleados()->getEmpleado(*m_IDEmpleado.value());
}
