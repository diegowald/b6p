#include "sectores.h"
#include <QsLog.h>

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"),
                "Sectors", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE() << "Sectores::Sectores(QObject *parent)";
}

QString Sectores::getSelectFromMainDB()
{
    QLOG_TRACE() << "QString Sectores::getSelectFromMainDB()";
    return QString("select ID, Nombre, Descripcion, ShowInPlanification, LastUpdate from sectores "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString Sectores::getSqlString()
{
    QLOG_TRACE() << "QString Sectores::getSqlString()";
    return QString("select ID, Nombre, Descripcion, ShowInPlanification, sent from sectores ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString Sectores::getSQLExistsInMainDB()
{
    QLOG_TRACE() << "QString Sectores::getSQLExistsInMainDB()";
    return QString("select ID, Nombre, Descripcion, ShowInPlanification from sectores "
                   " where ID = :IDSector;");
}

void Sectores::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE() << "void Sectores::addRecord(RecordPtr record, bool setNew)";
    SectorPtr s = boost::make_shared<Sector>(this);

    s->IDSector().setValue((*record)["ID"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    if ((*record)["ShowInPlanification"].toLongLong() == 0)
        s->ShowInPlanification().setValue(false);
    else
        s->ShowInPlanification().setValue(true);
    s->setSentStatus((*record)["sent"].toInt() == 1);

    if (setNew)
        s->setNew();
    else
        s->setInitialized();

    m_Sectores[s->IDSector().value()] = s;
}

void Sectores::updateRecord(RecordPtr record)
{
    QLOG_TRACE() << "void Sectores::updateRecord(RecordPtr record)";
    SectorPtr s = getSector((*record)["ID"].toInt());
    s->Nombre().setValue((*record)["Nombre"].toString());
    s->Descripcion().setValue((*record)["Descripcion"].toString());
    if ((*record)["ShowInPlanification"].toLongLong() == 0)
        s->ShowInPlanification().setValue(false);
    else
        s->ShowInPlanification().setValue(true);
}

void Sectores::deleteRecord(RecordPtr record)
{
    QLOG_TRACE() << "void Sectores::deleteRecord(RecordPtr record)";
    SectorPtr s = getSector((*record)["ID"].toInt());
}

bool Sectores::exists(RecordPtr record)
{
    QLOG_TRACE() << "bool Sectores::exists(RecordPtr record)";
    SectorPtr s = getSector((*record)["ID"].toInt());
    return (s.get() != NULL);
}

bool Sectores::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE() << "bool Sectores::isRecordUnsent(RecordPtr record)";
    if (!exists(record))
        return false;
    SectorPtr s = getSector((*record)["ID"].toInt());
    return s->isUnSent();
}

RecordPtr Sectores::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE() << "RecordPtr Sectores::getLocalRecord(RecordPtr record)";
    if (!exists(record))
        return RecordPtr();
    SectorPtr s = getSector((*record)["ID"].toInt());
    return s->asRecordPtr();
}

QString Sectores::getDeleteStatement()
{
    QLOG_TRACE() << "QString Sectores::getDeleteStatement()";
    return "delete from sectores where ID = :ID;";
}

QString Sectores::getUpdateStatement()
{
    QLOG_TRACE() << "QString Sectores::getUpdateStatement()";
    return "update sectores set Nombre = :Nombre, Descripcion = :Descripcion, showInPlanification = :showInPlanification where ID = :RECORD_ID;";
}

QString Sectores::getInsertStatement(bool IncludeIDs)
{
    QLOG_TRACE() << "QString Sectores::getInsertStatement(bool IncludeIDs)";
    if (IncludeIDs)
        return "insert into sectores "
                " (ID, Nombre, Descripcion, showInPlanification) "
                " values "
                " (:RECORD_ID, :Nombre, :Descripcion, :showInPlanification);";
    else
        return "insert into sectores "
            " (Nombre, Descripcion, showInPlanification) "
            " values "
            " (:Nombre, :Descripcion, :showInPlanification);";
}

RecordSet Sectores::getRecords(RecordStatus status)
{
    QLOG_TRACE() << "RecordSet Sectores::getRecords(RecordStatus status)";
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

RecordSet Sectores::getUnsent()
{
    QLOG_TRACE() << "RecordSet Sectores::getUnsent()";
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
    QLOG_TRACE() << "SectorPtr Sectores::getSector(int IDSector)";
    if (m_Sectores.find(IDSector) == m_Sectores.end())
        return SectorPtr();
    else
        return m_Sectores[IDSector];
}

SectorPtr Sectores::getSector(QString SectorName)
{
    QLOG_TRACE() << "|SectorPtr Sectores::getSector(QString SectorName)";
    foreach (SectorPtr s, m_Sectores.values())
    {
        if (s->Nombre().value() == SectorName)
            return s;
    }

    return SectorPtr();
}

SectorLst Sectores::getAll(bool onlyShowInPlanification, bool includeDeleted)
{
    QLOG_TRACE() << "SectorLst Sectores::getAll(bool onlyShowInPlanification, bool includeDeleted)";
    SectorLst res = boost::make_shared<QList<SectorPtr> >();
    foreach(SectorPtr s, m_Sectores.values())
    {
        bool add = false;
        add = (s->isDeleted() ? (includeDeleted ? true : false) : true);
        if (onlyShowInPlanification)
            add &= s->ShowInPlanification().value();

        if (add)
            res->push_back(s);
    }
    return res;
}

void Sectores::defineHeaders(QStringList &)
{
    QLOG_TRACE() << "void Sectores::defineHeaders(QStringList &)";
}

boost::shared_ptr<QList<QStringList> > Sectores::getAll()
{
    QLOG_TRACE() << "boost::shared_ptr<QList<QStringList> > Sectores::getAll()";
    return boost::make_shared<QList<QStringList> >();
}

void Sectores::fillData(QTreeWidget &)
{
    QLOG_TRACE() << "void Sectores::fillData(QTreeWidget &)";
}

bool Sectores::addNew()
{
    QLOG_TRACE() << "bool Sectores::addNew()";
    return false;
}

bool Sectores::edit(QVariant)
{
    QLOG_TRACE() << "bool Sectores::edit(QVariant)";
    return false;
}

bool Sectores::deleteElement(QVariant)
{
    QLOG_TRACE() << "bool Sectores::deleteElement(QVariant)";
    return false;
}

bool Sectores::canBeDeleted(QVariant)
{
    QLOG_TRACE() << "bool Sectores::canBeDeleted(QVariant)";
    return false;
}

void Sectores::setStatusToUnmodified(bool removeDeleted)
{
    QLOG_TRACE() << "void Sectores::setStatusToUnmodified(bool removeDeleted)";
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
