#include "capacidadespersonasector.h"

CapacidadesPersonaSector::CapacidadesPersonaSector(QObject *parent) :
    ACollection(tr("Employee capacity by Sector"), false, parent)
{
}

CapacidadPersonaSectorLst CapacidadesPersonaSector::getAll(int IDEmpleado)
{
    CapacidadPersonaSectorLst res(new QList<CapacidadPersonaSectorPtr>());
    foreach(CapacidadPersonaSectorPtr cap, m_Capacidades)
    {
        if (cap->IDEmpleado().value() == IDEmpleado)
            res->push_back(cap);
    }
    return res;
}

CapacidadPersonaSectorPtr CapacidadesPersonaSector::get(int idEmpleado, int IDSector, int IDSubSector)
{
    CapacidadPersonaSectorLst all = getAll(idEmpleado);
    foreach(CapacidadPersonaSectorPtr c, *all)
    {
        if (c->canWork(IDSector, IDSubSector))
            return c;
    }
    return CapacidadPersonaSectorPtr();
}

QString CapacidadesPersonaSector::getSqlString()
{
    return "select IDSector, IDSubSector, IDEmpleado, Capacidad from capacidadespersonassector;";
}

void CapacidadesPersonaSector::addRecord(Record &record)
{
    CapacidadPersonaSectorPtr c(new CapacidadPersonaSector(this));

    c->IDSector().setValue(record["IDSector"].toInt());
    c->ID_SubSector().setValue(record["IDSubSector"].toInt());
    c->IDEmpleado().setValue(record["IDEmpleado"].toInt());
    c->Capacidad().setValue(record["Capacidad"].toInt());
    c->setInitialized();
    m_Capacidades.push_back(c);
}

QString CapacidadesPersonaSector::getDeleteStatement()
{
    return "delete from capacidadespersonassector where IDSector = :IDSector "
            " and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;";
}

QString CapacidadesPersonaSector::getUpdateStatement()
{
    return "update capacidadespersonassector set "
            " Capacidad = :Capacidad "
            " where "
            " IDSector = :IDSector and IDSubSector = :IDSubSector "
            " and IDEmpleado = :IDEmpleado;";
}

QString CapacidadesPersonaSector::getInsertStatement()
{
    return "insert into capacidadespersonassector "
            " (IDSector, IDSubSector, IDEmpleado, Capacidad) "
            " values "
            " (:IDSector, :IDSubSector, :IDEmpleado, :Capacidad);";
}

RecordSet CapacidadesPersonaSector::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
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

void CapacidadesPersonaSector::updateCapacityfromData(CapacidadPersonaSectorLst dataFrom)
{
    if (dataFrom->count() > 0)
    {
        CapacidadPersonaSectorLst capsEmpleado = getAll(dataFrom->at(0)->IDEmpleado().value());
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

void CapacidadesPersonaSector::setStatusToUnmodified()
{
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        c->setUnmodified();
    }
}
