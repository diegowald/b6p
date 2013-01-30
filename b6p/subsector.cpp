#include "subsector.h"
#include "datastore.h"

SubSector::SubSector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();

    m_IDSector.reparent(this);
    m_IDSubSector.reparent(this);
    m_Nombre.reparent(this);
    m_Descripcion.reparent(this);

}

NullableField<int> SubSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> SubSector::IDSubsector()
{
    return m_IDSubSector;
}

NullableField<QString> SubSector::Nombre()
{
    return m_Nombre;
}

NullableField<QString> SubSector::Descripcion()
{
    return m_Descripcion;
}

void SubSector::IDSector(NullableField<int> value)
{
    m_IDSector = value;
}

void SubSector::IDSubsector(NullableField<int> value)
{
    m_IDSubSector = value;
}

void SubSector::Nombre(NullableField<QString> value)
{
    m_Nombre = value;
}

void SubSector::Descripcion(NullableField<QString> value)
{
    m_Descripcion = value;
}


SectorPtr SubSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(*m_IDSector.value());
}
