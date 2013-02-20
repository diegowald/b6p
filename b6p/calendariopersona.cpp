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

NullableField<int> &CalendarioPersona::HoraIngreso()
{
    return m_HoraIngreso;
}

NullableField<int> &CalendarioPersona::HoraEgreso()
{
    return m_HoraEgreso;
}

bool CalendarioPersona::EqualsTo(CalendarioPersonaPtr other)
{
    return ((m_Dia.value() == other->Dia().value())
            && m_IDEmpleado.value() == other->IDEmpleado().value());
}

void CalendarioPersona::updateWith(CalendarioPersonaPtr other)
{
    if (other->HoraIngreso().isNull())
        m_HoraIngreso.setNull();
    else
        m_HoraIngreso.setValue(other->HoraIngreso().value());

    if (other->HoraEgreso().isNull())
        m_HoraEgreso.setNull();
    else
        m_HoraEgreso.setValue(other->HoraEgreso().value());
}

void CalendarioPersona::updateIDEmpleado(int newId)
{
    m_IDEmpleado.setValue(newId);
}

bool CalendarioPersona::canWork(int Dia, int HoraInicio, int HoraFin)
{
    if (m_Dia.value() != Dia)
        return false;

    if (HoraInicio < m_HoraIngreso.value())
        return false;

    if (HoraFin > m_HoraEgreso.value())
        return false;

    return true;
}
