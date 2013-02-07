#include "subsector.h"
#include "datastore.h"

SubSector::SubSector(QObject *parent) :
    QObject(parent)
{
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();

    m_IDSector.setParent(this);
    m_IDSubSector.setParent(this);
    m_Nombre.setParent(this);
    m_Descripcion.setParent(this);

}

RecordPtr SubSector::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["ID"] = m_IDSubSector.toVariant();
    (*res)["Nombre"] = m_Nombre.toVariant();
    (*res)["Descripcion"] = m_Descripcion.toVariant();

    return res;
}

NullableField<int> &SubSector::IDSector()
{
    return m_IDSector;
}

NullableField<int> &SubSector::IDSubsector()
{
    return m_IDSubSector;
}

NullableField<QString> &SubSector::Nombre()
{
    return m_Nombre;
}

NullableField<QString> &SubSector::Descripcion()
{
    return m_Descripcion;
}

SectorPtr SubSector::getSector()
{
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}
