#include "sectores.h"

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"), parent)
{
}

void Sectores::loadData()
{
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
