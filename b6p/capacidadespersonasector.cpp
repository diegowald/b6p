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
        if (*cap->IDEmpleado().value() == IDEmpleado)
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

    c->IDSector(NullableField<int>(record["IDSector"].toInt()));
    c->IDSubSector(NullableField<int>(record["IDSubSector"].toInt()));
    c->IDEmpleado(NullableField<int>(record["IDEmpleado"].toInt()));
    c->Capacidad(NullableField<int>(record["Capacidad"].toInt()));

    m_Capacidades.push_back(c);
}

void CapacidadesPersonaSector::saveData()
{
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

void CapacidadesPersonaSector::edit(QVariant ID)
{
}

void CapacidadesPersonaSector::deleteElement(QVariant ID)
{
}
