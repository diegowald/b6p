#include "sectores.h"

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"), parent)
{
}

QString Sectores::getSqlString()
{
    return "select ID, Nombre, Descripcion from sectores;";
}

void Sectores::addRecord(Record &record)
{
    SectorPtr s(new Sector(this));

    s->IDSector(NullableField<int>(record["ID"].toInt()));
    s->Nombre(NullableField<QString>(record["Nombre"].toString()));
    s->Descripcion(NullableField<QString>(record["Descripcion"].toString()));

    m_Sectores[*s->IDSector().value()] = s;
}

void Sectores::saveData()
{
}

SectorPtr Sectores::getSector(int IDSector)
{
    if (m_Sectores.find(IDSector) == m_Sectores.end())
        return SectorPtr();
    else
        return m_Sectores[IDSector];
}

void Sectores::defineHeaders(QStringList &list)
{
}

void Sectores::fillData(QTreeWidget &tree)
{
}

bool Sectores::addNew()
{
}

void Sectores::edit(QVariant ID)
{
}

void Sectores::deleteElement(QVariant ID)
{
}
