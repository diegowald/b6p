#include "subsectores.h"

SubSectores::SubSectores(QObject *parent) :
    ACollection(tr("SubSectors"), parent)
{
}

void SubSectores::loadData()
{
}

void SubSectores::saveData()
{
}

SubSectorPtr SubSectores::getSubSector(int idSubSector)
{
    if (m_SubSectores.find(idSubSector) == m_SubSectores.end())
        return SubSectorPtr();
    else
        return m_SubSectores[idSubSector];
}

SubSectoresLst SubSectores::getAll()
{
    SubSectoresLst res(new QList<SubSectorPtr>(m_SubSectores.values()));
    return res;
}

SubSectoresLst SubSectores::getAll(int IDSector)
{
    SubSectoresLst res(new QList<SubSectorPtr>());
    foreach(SubSectorPtr subsector, m_SubSectores.values())
    {
        if (*subsector->IDSector().value() == IDSector)
            res->push_back(subsector);
    }
    return res;
}

void SubSectores::defineHeaders(QStringList &list)
{
}

void SubSectores::fillData(QTreeWidget &tree)
{
}

bool SubSectores::addNew()
{
}

void SubSectores::edit(QVariant ID)
{
}

void SubSectores::deleteElement(QVariant ID)
{
}
