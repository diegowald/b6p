#include "subsectores.h"
#include <QsLog.h>


SubSectores::SubSectores(QObject *parent) :
    ACollection(tr("SubSectors"),
                "SubSectors", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

QString SubSectores::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, IDSector, Nombre, Descripcion, LastUpdate from subsectores "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString SubSectores::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select ID, IDSector, Nombre, Descripcion, sent, RecordStatus from subsectores ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString SubSectores::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, IDSector, Nombre, Descripcion from subsectores "
                   " where ID = :IDSubSector;");
}

void SubSectores::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    SubSectorPtr s = boost::make_shared<SubSector>(this);

    s->IDSubsector().setValue((*record)["ID"].toInt());
    s->IDSector().setValue((*record)["IDSector"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    s->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));
    if (setNew)
        s->setNew();
    else
        s->setInitialized();

    m_SubSectores[s->IDSubsector().value()] = s;
}

void SubSectores::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());

    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    if (isFromSincro)
    {
        s->setInMemoryRecordStatus(UNMODIFIED);
        s->setLocalRecordStatus(UNMODIFIED);
    }
}

void SubSectores::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    m_SubSectores.remove((*record)["ID"].toInt());
}

bool SubSectores::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    return (getSubSector((*record)["ID"].toInt()) != SubSectorPtr());
}

bool SubSectores::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());
    if (SubSectorPtr() != s)
    {
        return s->isEqualsTo(record);
    }
    else
        return false;
}

bool SubSectores::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());
    return s->isUnSent();
}

RecordPtr SubSectores::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());
    return s->asRecordPtr();
}

QString SubSectores::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from subsectores where ID = :ID;";
}

QString SubSectores::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from subsectores where ID = :ID;";
}

QString SubSectores::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update subsectores set IDSector = :IDSector, Nombre = :Nombre, Descripcion = :Descripcion, sent = 0 where ID = :ID;";
}

QString SubSectores::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update subsectores set IDSector = :IDSector, Nombre = :Nombre, Descripcion = :Descripcion, sent = 0 where ID = :ID;";
}

QString SubSectores::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return " insert into subsectores "
            " (IDSector, Nombre, Descripcion, sent) "
            " values "
            " (:IDSector, :Nombre, :Descripcion, 0 );";
}

QString SubSectores::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return "insert into subsectores "
            " (ID, IDSector, Nombre, Descripcion, sent) "
            " values "
            " (:RECORD_ID, :IDSector, :Nombre, :Descripcion, 0 );";
}

RecordSet SubSectores::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        switch (status)
        {
        case NEW:
            if (s->isNew(fromMemory))
                res->push_back(s->asRecordPtr());
            break;
        case MODIFIED:
        {
            if (s->isModified(fromMemory))
                res->push_back(s->asRecordPtr());
            break;
        }
        case DELETED:
            if (s->isDeleted(fromMemory))
                res->push_back(s->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet SubSectores::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        if (s->isUnSent())
            res->push_back(s->asRecordPtr());
    }
    return res;
}

SubSectorPtr SubSectores::getSubSector(int idSubSector)
{
    QLOG_TRACE_FN();
    if (m_SubSectores.find(idSubSector) == m_SubSectores.end())
        return SubSectorPtr();
    else
        return m_SubSectores[idSubSector];
}

SubSectorPtr SubSectores::getSubSector(int idSector, QString SubSectorName)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    SubSectoresLst res = boost::make_shared<QList<SubSectorPtr> >();
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        if (!s->isDeleted(true))
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
    QLOG_TRACE_FN();
    SubSectoresLst res = boost::make_shared<QList<SubSectorPtr> >();
    foreach(SubSectorPtr subsector, m_SubSectores.values())
    {
        if (subsector->IDSector().value() == IDSector)
        {
            if (!subsector->isDeleted(true))
                res->push_back(subsector);
            else
                if (includeDeleted)
                    res->push_back(subsector);
        }
    }
    return res;
}

void SubSectores::defineHeaders(QStringList &)
{
    QLOG_TRACE_FN();
}

boost::shared_ptr<QList<QStringList> > SubSectores::getAll()
{
    QLOG_TRACE_FN();
    return boost::make_shared<QList<QStringList> >();
}

void SubSectores::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool SubSectores::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool SubSectores::edit(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool SubSectores::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool SubSectores::canBeDeleted(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

void SubSectores::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach(SubSectorPtr s, m_SubSectores.values())
    {
        if (removeDeleted && s->isDeleted(true))
            toDelete.push_back(s->IDSubsector().value());
        else
        {
            if (impactInMemmory)
                s->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                s->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(int id, toDelete)
    {
        m_SubSectores.remove(id);
    }
}
