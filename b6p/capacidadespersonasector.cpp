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


void CapacidadesPersonaSector::loadData()
{
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
