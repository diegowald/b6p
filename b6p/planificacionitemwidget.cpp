#include "planificacionitemwidget.h"
#include "datastore.h"

PlanificacionItemWidget::PlanificacionItemWidget(TimeAssignmentItemEdit *timeItem, QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    parent->setItemWidget(this, 3, timeItem);

    connect(timeItem, SIGNAL(employeeChanged(const QString &)), this, SLOT(onEmployeeChanged(const QString &)));
    connect(timeItem, SIGNAL(sectorChanged(const QString &)), this, SLOT(onSectorChanged(const QString &)));
    connect(timeItem, SIGNAL(subsectorChanged(const QString &)), this, SLOT(onSubsectorChanged(const QString &)));

    if (timeItem->IDEmpleado() != -1)
    {
        EmpleadoPtr emp = DataStore::instance()->getEmpleados()->getEmpleado(timeItem->IDEmpleado(), true);
        if (emp.isNull())
        {
            setText(0, "");
        }
        else
        {
            QString e = "%1, %2";
            QString apellido = emp->Apellido().isNull() ? "" : emp->Apellido().value();
            QString nombre = emp->Nombre().isNull() ? "" : emp->Nombre().value();
            setText(0, e.arg(apellido).arg(nombre));
        }
    }
    else
    {
        setText(0, QString(""));
    }

    if (timeItem->IDSector() != -1)
    {
        SectorPtr sec = DataStore::instance()->getSectores()->getSector(timeItem->IDSector());
        if (sec.isNull())
        {
            setText(1, "");
        }
        else
        {
            QString s = sec->Nombre().isNull() ? "" : sec->Nombre().value();
            setText(1, s);
        }
    }
    else
    {
        setText(1, "");
    }

    if (timeItem->IDSubSector() != -1)
    {
        SubSectorPtr ssec = DataStore::instance()->getSubSectores()->getSubSector(timeItem->IDSubSector());
        if (ssec.isNull())
        {
            setText(2, "");
        }
        else
        {
            QString ss = ssec->Nombre().isNull() ? "" : ssec->Nombre().value();
            setText(2, ss);
        }
    }
    else
    {
        setText(2, "");
    }
}

void PlanificacionItemWidget::onEmployeeChanged(const QString &empleado)
{
    setText(0, empleado);
}

void PlanificacionItemWidget::onSectorChanged(const QString &sector)
{
    setText(1, sector);
}

void PlanificacionItemWidget::onSubsectorChanged(const QString &subSector)
{
    setText(2, subSector);
}

