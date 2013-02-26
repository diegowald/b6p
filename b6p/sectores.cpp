#include "sectores.h"

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"), false, parent)
{
}

QString Sectores::getSqlString()
{
    return QString("select ID, Nombre, Descripcion from sectores ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void Sectores::addRecord(Record &record)
{
    SectorPtr s = boost::make_shared<Sector>(this);

    s->IDSector().setValue(record["ID"].toInt());
    s->Nombre().setValue(record["Nombre"].toString());
    s->Descripcion().setValue(record["Descripcion"].toString());
    s->setInitialized();

    m_Sectores[s->IDSector().value()] = s;
}

QString Sectores::getDeleteStatement()
{
    return "delete from sectores where ID = :ID;";
}

QString Sectores::getUpdateStatement()
{
    return "update sectores set Nombre = :Nombre, Descripcion = :Descripcion where ID = :ID;";
}

QString Sectores::getInsertStatement()
{
    return "insert into sectores "
            " (Nombre, Descripcion) "
            " values "
            " (:Nombre, :Descripcion);";
}

RecordSet Sectores::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
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

SectorPtr Sectores::getSector(int IDSector)
{
    if (m_Sectores.find(IDSector) == m_Sectores.end())
        return SectorPtr();
    else
        return m_Sectores[IDSector];
}

SectorPtr Sectores::getSector(QString SectorName)
{
    foreach (SectorPtr s, m_Sectores.values())
    {
        if (s->Nombre().value() == SectorName)
            return s;
    }

    return SectorPtr();
}

SectorLst Sectores::getAll(bool includeDeleted)
{
    SectorLst res = boost::make_shared<QList<SectorPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
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

void Sectores::defineHeaders(QStringList &list)
{
}

void Sectores::fillData(QTreeWidget &tree)
{
}

bool Sectores::addNew()
{
}

bool Sectores::edit(QVariant ID)
{
}

bool Sectores::deleteElement(QVariant ID)
{
}

bool Sectores::canBeDeleted(QVariant ID)
{
}

void Sectores::setStatusToUnmodified(bool removeDeleted)
{
    QList<int> toDelete;
    foreach(SectorPtr s, m_Sectores.values())
    {
        if (removeDeleted && s->isDeleted())
            toDelete.push_back(s->IDSector().value());
        else
            s->setUnmodified();
    }
    foreach(int id, toDelete)
    {
        m_Sectores.remove(id);
    }
}
