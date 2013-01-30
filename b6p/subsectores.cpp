#include "subsectores.h"

SubSectores::SubSectores(QObject *parent) :
    ACollection(tr("SubSectors"), parent)
{
}

QString SubSectores::getSqlString()
{
    return "select ID, IDSector, Nombre, Descripcion from subsectores;";
}

void SubSectores::addRecord(Record &record)
{
    SubSectorPtr s(new SubSector(this));

    s->IDSubsector().setValue(record["ID"].toInt());
    s->IDSector().setValue(record["IDSector"].toInt());
    s->Nombre().setValue(record["Nombre"].toString());
    s->Descripcion().setValue(record["Descripcion"].toString());

    m_SubSectores[s->IDSubsector().value()] = s;
}

QString SubSectores::getDeleteStatement()
{
    return "delete from subsectores where ID = :ID;";
}

QString SubSectores::getUpdateStatement()
{
    return "update subsectores set IDSector = :IDSector, Nombre = :Nombre, Descripcion = :Descripcion where ID = :ID;";
}

QString SubSectores::getInsertStatement()
{
    return " insert into subsectores "
            " (IDSector, Nombre, Descripcion) "
            " values "
            " (:IDSector, :Nombre, :Descripcion);";
}

RecordSet SubSectores::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        switch (status)
        {
        case NEW:
            if (s->isNew())
                res->push_back(s->asRecordPtr());
            break;
        case MODIFIED:
            if (s->isModified())
                res->push_back(s->asRecordPtr());
            break;
        case DELETED:
            if (s->isDeleted())
                res->push_back(s->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
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
        if (subsector->IDSector().value() == IDSector)
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

bool SubSectores::edit(QVariant ID)
{
}

bool SubSectores::deleteElement(QVariant ID)
{
}
