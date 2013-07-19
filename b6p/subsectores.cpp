#include "subsectores.h"
#include <QsLog.h>


SubSectores::SubSectores(QObject *parent) :
    ACollection(tr("SubSectors"),
                "SubSectors", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE() << "SubSectores::SubSectores(QObject *parent)";
}

QString SubSectores::getSelectFromMainDB()
{
    QLOG_TRACE() << "QString SubSectores::getSelectFromMainDB()";
    return QString("select ID, IDSector, Nombre, Descripcion, LastUpdate from subsectores "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString SubSectores::getSqlString()
{
    QLOG_TRACE() << "QString SubSectores::getSqlString()";
    return QString("select ID, IDSector, Nombre, Descripcion, sent from subsectores ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString SubSectores::getSQLExistsInMainDB()
{
    QLOG_TRACE() << "QString SubSectores::getSQLExistsInMainDB()";
    return QString("select ID, IDSector, Nombre, Descripcion from subsectores "
                   " where ID = :IDSubSector;");
}

void SubSectores::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE() << "void SubSectores::addRecord(RecordPtr record, bool setNew)";
    SubSectorPtr s = boost::make_shared<SubSector>(this);

    s->IDSubsector().setValue((*record)["ID"].toInt());
    s->IDSector().setValue((*record)["IDSector"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    s->setSentStatus((*record)["sent"].toInt() == 1);
    if (setNew)
        s->setNew();
    else
        s->setInitialized();

    m_SubSectores[s->IDSubsector().value()] = s;
}

void SubSectores::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE() << "void SubSectores::updateRecord(RecordPtr record)";
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());

    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    s->setSentStatus(isFromSincro);
}

void SubSectores::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE() << "void SubSectores::deleteRecord(RecordPtr record)";
    m_SubSectores.remove((*record)["ID"].toInt());
}

bool SubSectores::exists(RecordPtr record)
{
    QLOG_TRACE() << "bool SubSectores::exists(RecordPtr record)";
    return (getSubSector((*record)["ID"].toInt()) != SubSectorPtr());
}

bool SubSectores::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE() << "bool SubSectores::localRecordIsEqualsTo(RecordPtr record)";
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
    QLOG_TRACE() << "bool SubSectores::isRecordUnsent(RecordPtr record)";
    if (!exists(record))
        return false;
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());
    return s->isUnSent();
}

RecordPtr SubSectores::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE() << "RecordPtr SubSectores::getLocalRecord(RecordPtr record)";
    if (!exists(record))
        return RecordPtr();
    SubSectorPtr s = getSubSector((*record)["ID"].toInt());
    return s->asRecordPtr();
}

QString SubSectores::getDeleteStatement()
{
    QLOG_TRACE() << "QString SubSectores::getDeleteStatement()";
    return "delete from subsectores where ID = :ID;";
}

QString SubSectores::getUpdateStatement()
{
    QLOG_TRACE() << "QString SubSectores::getUpdateStatement()";
    return "update subsectores set IDSector = :IDSector, Nombre = :Nombre, Descripcion = :Descripcion, sent = 0 where ID = :ID;";
}

QString SubSectores::getInsertStatement(bool IncludeIDs)
{
    QLOG_TRACE() << "QString SubSectores::getInsertStatement(bool IncludeIDs)";
    if (IncludeIDs)
        return "insert into subsectores "
                " (ID, IDSector, Nombre, Descripcion, sent) "
                " values "
                " (:RECORD_ID, :IDSector, :Nombre, :Descripcion, 0 );";
    else
        return " insert into subsectores "
                " (IDSector, Nombre, Descripcion, sent) "
                " values "
                " (:IDSector, :Nombre, :Descripcion, 0 );";
}

RecordSet SubSectores::getRecords(RecordStatus status)
{
    QLOG_TRACE() << "RecordSet SubSectores::getRecords(RecordStatus status)";
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

RecordSet SubSectores::getUnsent()
{
    QLOG_TRACE() << "RecordSet SubSectores::getUnsent()";
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
    QLOG_TRACE() << "SubSectorPtr SubSectores::getSubSector(int idSubSector)";
    if (m_SubSectores.find(idSubSector) == m_SubSectores.end())
        return SubSectorPtr();
    else
        return m_SubSectores[idSubSector];
}

SubSectorPtr SubSectores::getSubSector(int idSector, QString SubSectorName)
{
    QLOG_TRACE() << "SubSectorPtr SubSectores::getSubSector(int idSubSector)";
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
    QLOG_TRACE() << "SubSectoresLst SubSectores::getAll(bool includeDeleted)";
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
    QLOG_TRACE() << "SubSectoresLst SubSectores::getAll(int IDSector, bool includeDeleted)";
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

void SubSectores::defineHeaders(QStringList &)
{
    QLOG_TRACE() << "void SubSectores::defineHeaders(QStringList &)";
}

boost::shared_ptr<QList<QStringList> > SubSectores::getAll()
{
    QLOG_TRACE() << "boost::shared_ptr<QList<QStringList> > SubSectores::getAll()";
    return boost::make_shared<QList<QStringList> >();
}

void SubSectores::fillData(QTreeWidget &)
{
    QLOG_TRACE() << "void SubSectores::fillData(QTreeWidget &)";
}

bool SubSectores::addNew()
{
    QLOG_TRACE() << "bool SubSectores::addNew()";
    return false;
}

bool SubSectores::edit(QVariant)
{
    QLOG_TRACE() << "bool SubSectores::edit(QVariant)";
    return false;
}

bool SubSectores::deleteElement(QVariant)
{
    QLOG_TRACE() << "bool SubSectores::deleteElement(QVariant)";
    return false;
}

bool SubSectores::canBeDeleted(QVariant)
{
    QLOG_TRACE() << "bool SubSectores::canBeDeleted(QVariant)";
    return false;
}

void SubSectores::setStatusToUnmodified(bool removeDeleted)
{
    QLOG_TRACE() << "void SubSectores::setStatusToUnmodified(bool removeDeleted)";
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
