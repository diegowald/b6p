#include "capacidadespersonasector.h"

CapacidadesPersonaSector::CapacidadesPersonaSector(QObject *parent) :
    ACollection(tr("Employee capacity by Sector"),
                "Employee capacity by Sector", false, parent)
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

QString CapacidadesPersonaSector::getSqlString()
{
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad from capacidadespersonassector ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void CapacidadesPersonaSector::addRecord(Record &record)
{
    CapacidadPersonaSectorPtr c = boost::make_shared<CapacidadPersonaSector>(this);

    c->IDSector().setValue(record["IDSector"].toInt());
    c->ID_SubSector().setValue(record["IDSubSector"].toInt());
    c->IDEmpleado().setValue(record["IDEmpleado"].toInt());
    c->Capacidad().setValue(record["Capacidad"].toInt());
    c->setInitialized();
    m_Capacidades.push_back(c);
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

QString CapacidadesPersonaSector::getInsertStatement()
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

void CapacidadesPersonaSector::defineHeaders(QStringList &)
{
}

void CapacidadesPersonaSector::fillData(QTreeWidget &)
{
}

bool CapacidadesPersonaSector::addNew()
{
}

bool CapacidadesPersonaSector::edit(QVariant ID)
{
}

bool CapacidadesPersonaSector::deleteElement(QVariant ID)
{
}

bool CapacidadesPersonaSector::canBeDeleted(QVariant ID)
{
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
