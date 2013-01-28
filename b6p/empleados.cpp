#include "empleados.h"
#include "genericlist.h"
#include "dlgemployee.h"

Empleados::Empleados(QObject *parent) :
    ACollection(tr("Employees"), parent)
{
}

Empleados::~Empleados()
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

EmpleadosLst Empleados::getAll()
{
    EmpleadosLst res(new QList<EmpleadoPtr>(m_Empleados.values()));
    return res;
}

void Empleados::defineHeaders(QStringList &list)
{
    list << tr("Lastname")
            << tr("Firstname")
            << tr("ID")
            << tr("Start");
}

void Empleados::fillData(QTreeWidget &tree)
{
    foreach(EmpleadoPtr emp, m_Empleados)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, *emp->Apellido().value());
        item->setText(1, *emp->Nombre().value());
        item->setText(2, *emp->Legajo().value());
        item->setText(3, emp->FechaIngreso().value()->toString(Qt::TextDate));
        tree.insertTopLevelItem(0, item);
    }
}

bool Empleados::addNew()
{
    DlgEmployee dlg;
    dlg.exec();
    return false;
}

void Empleados::edit(QVariant ID)
{
}

void Empleados::deleteElement(QVariant ID)
{
}
