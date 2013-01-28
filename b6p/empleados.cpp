#include "empleados.h"

Empleados::Empleados(QObject *parent) :
    ACollection(tr("Employees"), parent)
{
}

void Empleados::loadData()
{
}

void Empleados::saveData()
{
}

EmpleadoPtr Empleados::getEmpleado(int idEmpleado)
{
    if (m_Empleados.find(idEmpleado) == m_Empleados.end())
        return EmpleadoPtr();
    else
        return m_Empleados[idEmpleado];
}
