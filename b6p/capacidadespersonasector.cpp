#include "capacidadespersonasector.h"

CapacidadesPersonaSector::CapacidadesPersonaSector(QObject *parent) :
    ACollection(tr("Employee capacity by Sector"), parent)
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


QString CapacidadesPersonaSector::getSqlString()
{
    return "select IDSector, IDSubSector, IDEmpleado, Capacidad from capacidadespersonasector;";
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
    return "delete from capacidadespersonasector where IDSector = :IDSector "
            " and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;";
}

QString CapacidadesPersonaSector::getUpdateStatement()
{
    return "update capacidadespersonasector set "
            " Capacidad = :Capacidad "
            " where "
            " IDSector = :IDSector and IDSubSector = :IDSubSector "
            " and IDEmpleado = :IDEmpleado;";
}

QString CapacidadesPersonaSector::getInsertStatement()
{
    return "insert into capacidadespersonasector "
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

void CapacidadesPersonaSector::defineHeaders(QStringList &list)
{
}

void CapacidadesPersonaSector::fillData(QTreeWidget &tree)
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

void CapacidadesPersonaSector::updateCapacityfromData(CapacidadPersonaSectorPtr dataFrom)
{
    foreach (CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        if (c->EqualsTo(dataFrom))
        {
            c->updateWith(dataFrom);
            return;
        }
    }
}
