#include "subsectores.h"

SubSectores::SubSectores(QObject *parent) :
    ACollection(tr("SubSectors"), false, parent)
{
}

QString SubSectores::getSqlString()
{
    return QString("select ID, IDSector, Nombre, Descripcion from subsectores ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void SubSectores::addRecord(Record &record)
{
    SubSectorPtr s = boost::make_shared<SubSector>(this);

    s->IDSubsector().setValue(record["ID"].toInt());
    s->IDSector().setValue(record["IDSector"].toInt());
    s->Nombre().setValue(record["Nombre"].toString());
    s->Descripcion().setValue(record["Descripcion"].toString());
    s->setInitialized();

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
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
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

SubSectorPtr SubSectores::getSubSector(int idSector, QString SubSectorName)
{
    SubSectoresLst ss = getAll(idSector);
    foreach (SubSectorPtr s, *ss)
    {
        if (s->Nombre().value() == SubSectorName)
            return s;
    }
    return SubSectorPtr();
}

SubSectoresLst SubSectores::getAll(bool includeDeleted)
{
    SubSectoresLst res = boost::make_shared<QList<SubSectorPtr> >();
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        if (!s->isDeleted())
            res->push_back(s);
        else
        {
            if (includeDeleted)
                res->push_back(s);
        }
    }

    return res;
}

SubSectoresLst SubSectores::getAll(int IDSector, bool includeDeleted)
{
    SubSectoresLst res = boost::make_shared<QList<SubSectorPtr> >();
    foreach(SubSectorPtr subsector, m_SubSectores.values())
    {
        if (subsector->IDSector().value() == IDSector)
        {
            if (!subsector->isDeleted())
                res->push_back(subsector);
            else
                if (includeDeleted)
                    res->push_back(subsector);
        }
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

bool SubSectores::canBeDeleted(QVariant ID)
{
}

void SubSectores::setStatusToUnmodified(bool removeDeleted)
{
    QList<int> toDelete;
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        if (removeDeleted && s->isDeleted())
            toDelete.push_back(s->IDSubsector().value());
        else
            s->setUnmodified();
    }
    foreach(int id, toDelete)
    {
        m_SubSectores.remove(id);
    }
}
