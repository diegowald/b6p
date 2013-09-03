#include "sectores.h"
#include <QsLog.h>

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"),
                "Sectors", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

QString Sectores::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, Nombre, Descripcion, ShowInPlanification, LastUpdate from sectores "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString Sectores::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select ID, Nombre, Descripcion, ShowInPlanification, sent, RecordStatus from sectores ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString Sectores::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, Nombre, Descripcion, ShowInPlanification from sectores "
                   " where ID = :IDSector;");
}

void Sectores::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    SectorPtr s = boost::make_shared<Sector>(this);

    s->IDSector().setValue((*record)["ID"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    if ((*record)["ShowInPlanification"].toLongLong() == 0)
        s->ShowInPlanification().setValue(false);
    else
        s->ShowInPlanification().setValue(true);
    s->setLocalRecordStatus((RecordStatus)(*record)["RecordStatus"].toInt());

    if (setNew)
        s->setNew();
    else
        s->setInitialized();

    m_Sectores[s->IDSector().value()] = s;
}

void Sectores::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    SectorPtr s = getSector((*record)["ID"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    if ((*record)["ShowInPlanification"].toLongLong() == 0)
        s->ShowInPlanification().setValue(false);
    else
        s->ShowInPlanification().setValue(true);

    if (isFromSincro)
    {
        s->setInMemoryRecordStatus(UNMODIFIED);
        s->setLocalRecordStatus(UNMODIFIED);
    }
}

void Sectores::deleteRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    SectorPtr s = getSector((*record)["ID"].toInt());
    if (isFromSincro)
    {
        s->setInMemoryRecordStatus(UNMODIFIED);
        s->setLocalRecordStatus(UNMODIFIED);
    }
}

bool Sectores::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    SectorPtr s = getSector((*record)["ID"].toInt());
    return (s.get() != NULL);
}

bool Sectores::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    SectorPtr s = getSector((*record)["ID"].toInt());
    if (NULL != s.get())
    {
        return s->isEqualsTo(record);
    }
    else
        return false;
}

bool Sectores::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    SectorPtr s = getSector((*record)["ID"].toInt());
    return s->isUnSent();
}

RecordPtr Sectores::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    SectorPtr s = getSector((*record)["ID"].toInt());
    return s->asRecordPtr();
}

QString Sectores::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from sectores where ID = :ID;";
}

QString Sectores::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from sectores where ID = :ID;";
}

QString Sectores::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update sectores set Nombre = :Nombre, Descripcion = :Descripcion, showInPlanification = :showInPlanification, sent = 0 where ID = :RECORD_ID;";
}

QString Sectores::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update sectores set Nombre = :Nombre, Descripcion = :Descripcion, showInPlanification = :showInPlanification, sent = 0 where ID = :RECORD_ID;";
}

QString Sectores::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return "insert into sectores "
            " (Nombre, Descripcion, showInPlanification, sent) "
            " values "
            " (:Nombre, :Descripcion, :showInPlanification, 0);";
}

QString Sectores::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return "insert into sectores "
            " (ID, Nombre, Descripcion, showInPlanification, sent) "
            " values "
            " (:RECORD_ID, :Nombre, :Descripcion, :showInPlanification, 0);";
}

RecordSet Sectores::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
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

RecordSet Sectores::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
    {
        if (s->isUnSent())
            res->push_back(s->asRecordPtr());
    }
    return res;
}

SectorPtr Sectores::getSector(int IDSector)
{
    QLOG_TRACE_FN();
    if (m_Sectores.find(IDSector) == m_Sectores.end())
        return SectorPtr();
    else
        return m_Sectores[IDSector];
}

SectorPtr Sectores::getSector(QString SectorName)
{
    QLOG_TRACE_FN();
    foreach (SectorPtr s, m_Sectores.values())
    {
        if (s->Nombre().value() == SectorName)
            return s;
    }

    return SectorPtr();
}

SectorLst Sectores::getAll(bool onlyShowInPlanification, bool includeDeleted)
{
    QLOG_TRACE_FN();
    SectorLst res = boost::make_shared<QList<SectorPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
    {
        bool add = false;
        add = (s->isDeleted(true) ? (includeDeleted ? true : false) : true);
        if (onlyShowInPlanification)
            add &= s->ShowInPlanification().value();

        if (add)
            res->push_back(s);
    }
    return res;
}

void Sectores::defineHeaders(QStringList &)
{
    QLOG_TRACE_FN();
}

boost::shared_ptr<QList<QStringList> > Sectores::getAll()
{
    QLOG_TRACE_FN();
    return boost::make_shared<QList<QStringList> >();
}

void Sectores::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool Sectores::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool Sectores::edit(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool Sectores::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool Sectores::canBeDeleted(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

void Sectores::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach(SectorPtr s, m_Sectores.values())
    {
        if (removeDeleted && s->isDeleted(true))
            toDelete.push_back(s->IDSector().value());
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
        m_Sectores.remove(id);
    }
}
