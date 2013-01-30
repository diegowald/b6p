#include "sector.h"

Sector::Sector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();

    m_IDSector.reparent(this);
    m_Nombre.reparent(this);
    m_Descripcion.reparent(this);
}

NullableField<int> Sector::IDSector()
{
    return m_IDSector;
}

NullableField<QString> Sector::Nombre()
{
    return m_Nombre;
}

NullableField<QString> Sector::Descripcion()
{
    return m_Descripcion;
}

void Sector::IDSector(NullableField<int> value)
{
    m_IDSector = value;
}

void Sector::Nombre(NullableField<QString> value)
{
    m_Nombre = value;
}

void Sector::Descripcion(NullableField<QString> value)
{
    m_Descripcion = value;
}
