#include "capacidadespersonasector.h"

CapacidadesPersonaSector::CapacidadesPersonaSector(QObject *parent) :
    ACollection(tr("Employee capacity by Sector"),
                "Employee capacity by Sector", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
}

CapacidadPersonaSectorLst CapacidadesPersonaSector::getAll(int IDEmpleado, bool includeDeleted)
{
    CapacidadPersonaSectorLst res = boost::make_shared<QList<CapacidadPersonaSectorPtr> >();
    foreach(CapacidadPersonaSectorPtr cap, m_Capacidades)
    {
        if (cap->IDEmpleado().value() == IDEmpleado)
        {
            if (!cap->isDeleted())
                res->push_back(cap);
            else
                if (includeDeleted)
                    res->push_back(cap);
        }
    }
    return res;
}

CapacidadPersonaSectorPtr CapacidadesPersonaSector::get(int idEmpleado, int IDSector, int IDSubSector, bool includeDeleted)
{
    CapacidadPersonaSectorLst all = getAll(idEmpleado, includeDeleted);
    foreach(CapacidadPersonaSectorPtr c, *all)
    {
        if (c->canWork(IDSector, IDSubSector))
            return c;
    }
    return CapacidadPersonaSectorPtr();
}

QString CapacidadesPersonaSector::getSelectFromMainDB()
{
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad, LastUpdate from capacidadespersonassector "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString CapacidadesPersonaSector::getSqlString()
{
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad, sent from capacidadespersonassector ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString CapacidadesPersonaSector::getSQLExistsInMainDB()
{
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad from capacidadespersonassector "
                   " where IDSector = :IDSector and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;");
}

void CapacidadesPersonaSector::addRecord(RecordPtr record, bool setNew)
{
    CapacidadPersonaSectorPtr c = boost::make_shared<CapacidadPersonaSector>(this);

    c->IDSector().setValue((*record)["IDSector"].toInt());
    c->ID_SubSector().setValue((*record)["IDSubSector"].toInt());
    c->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    c->Capacidad().setValue((*record)["Capacidad"].toInt());
    c->setSentStatus((*record)["sent"].toInt() == 1);

    if (setNew)
        c->setNew();
    else
        c->setInitialized();

    m_Capacidades.push_back(c);
}

void CapacidadesPersonaSector::updateRecord(RecordPtr record)
{
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);

    c->Capacidad().setValue((*record)["Capacidad"].toInt());
}

void CapacidadesPersonaSector::deleteRecord(RecordPtr record)
{
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);

    m_Capacidades.removeOne(c);
}

bool CapacidadesPersonaSector::exists(RecordPtr record)
{
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return (c != CapacidadPersonaSectorPtr());
}

bool CapacidadesPersonaSector::isRecordUnsent(RecordPtr record)
{
    if (!exists(record))
        return false;
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return c->isUnSent();
}

RecordPtr CapacidadesPersonaSector::getLocalRecord(RecordPtr record)
{
    if (!exists(record))
        return RecordPtr();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return c->asRecordPtr();
}

QString CapacidadesPersonaSector::getDeleteStatement()
{
    return QString("update capacidadespersonassector set RecordStatus = %1 where IDSector = :IDSector "
                   " and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;").arg(RECORD_DELETED);
}

QString CapacidadesPersonaSector::getUpdateStatement()
{
    return QString("update capacidadespersonassector set "
                   " Capacidad = :Capacidad, RecordStatus = %1 "
                   " where "
                   " IDSector = :IDSector and IDSubSector = :IDSubSector "
                   " and IDEmpleado = :IDEmpleado;").arg(RECORD_MODIFIED);
}

QString CapacidadesPersonaSector::getInsertStatement(bool)
{
    return QString("insert into capacidadespersonassector "
                   " (IDSector, IDSubSector, IDEmpleado, Capacidad, RecordStatus) "
                   " values "
                   " (:IDSector, :IDSubSector, :IDEmpleado, :Capacidad, %1);").arg(RECORD_NEW);
}

RecordSet CapacidadesPersonaSector::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        switch (status)
        {
        case NEW:
            if (c->isNew())
                res->push_back(c->asRecordPtr());
            break;
        case MODIFIED:
            if (c->isModified())
                res->push_back(c->asRecordPtr());
            break;
        case DELETED:
            if (c->isDeleted())
                res->push_back(c->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet CapacidadesPersonaSector::getUnsent()
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        if (c->isUnSent())
            res->push_back(c->asRecordPtr());
    }
    return res;
}

void CapacidadesPersonaSector::defineHeaders(QStringList &)
{
}

boost::shared_ptr<QList<QStringList> > CapacidadesPersonaSector::getAll()
{
    return boost::make_shared<QList<QStringList> >();
}

void CapacidadesPersonaSector::fillData(QTreeWidget &)
{
}

bool CapacidadesPersonaSector::addNew()
{
    return false;
}

bool CapacidadesPersonaSector::edit(QVariant)
{
    return false;
}

bool CapacidadesPersonaSector::deleteElement(QVariant)
{
    return false;
}

bool CapacidadesPersonaSector::canBeDeleted(QVariant)
{
    return false;
}

void CapacidadesPersonaSector::updateCapacityfromData(CapacidadPersonaSectorLst dataFrom)
{
    if (dataFrom->count() > 0)
    {
        CapacidadPersonaSectorLst capsEmpleado = getAll(dataFrom->at(0)->IDEmpleado().value(), false);
        foreach (CapacidadPersonaSectorPtr nc, *dataFrom)
        {
            bool found = false;
            foreach (CapacidadPersonaSectorPtr c, *capsEmpleado)
            {
                if (c->EqualsTo(nc))
                {
                    c->updateWith(nc);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                m_Capacidades.push_back(nc);
                nc->setNew();
            }
        }
    }
}

void CapacidadesPersonaSector::setStatusToUnmodified(bool removeDeleted)
{
    QList<CapacidadPersonaSectorPtr> toDelete;
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        if (removeDeleted && c->isDeleted())
            toDelete.push_back(c);
        else
            c->setUnmodified();
    }
    foreach(CapacidadPersonaSectorPtr c, toDelete)
    {
        m_Capacidades.removeOne(c);
    }
}
