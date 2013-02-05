#include "dlgemployee.h"
#include "ui_dlgemployee.h"
#include "capacitywidget.h"
#include "datastore.h"

DlgEmployee::DlgEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEmployee)
{
    ui->setupUi(this);
    setupScreen();
}

DlgEmployee::~DlgEmployee()
{
    delete ui;
}

void DlgEmployee::setData(EmpleadoPtr empleado)
{
    m_Empleado = empleado;
    // Informacion basica
    if (empleado->Legajo().isNull())
        ui->txtID->clear();
    else
        ui->txtID->setText(empleado->Legajo().value());

    if(empleado->Apellido().isNull())
        ui->txtLastName->clear();
    else
        ui->txtLastName->setText(empleado->Apellido().value());

    if (empleado->Nombre().isNull())
        ui->txtNames->clear();
    else
        ui->txtNames->setText(empleado->Nombre().value());

    if (empleado->FechaIngreso().isNull())
        ui->dateStart->clear();
    else
        ui->dateStart->setDate(empleado->FechaIngreso().value());

    // Sectores, subsectores y capacidades
    CapacidadPersonaSectorLst caps = empleado->Capacities();
    foreach (CapacidadPersonaSectorPtr cap, *caps.get())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        ui->treeCapacities->addTopLevelItem(item);
        CapacityWidget *w = new CapacityWidget();
        w->setSector(cap->getSector()->Nombre().value());
        w->setSubSector(cap->getSubSector()->Nombre().value());
        w->setCapacity(cap->Capacidad().value());
        ui->treeCapacities->setItemWidget(item, 0, w);
    }

    // Disponibilidad de horarios
    CalendarioPersonaLst cals = empleado->Disponibilidades();
    foreach (CalendarioPersonaPtr cal, *cals.get())
    {
        AvailabilityWidget *w = NULL;
        w->setDay(cal->Dia().value());
        switch (cal->Dia().value())
        {
        case 0:
            w = ui->TimeSunday;
            break;
        case 1:
            w = ui->TimeMonday;
            break;
        case 2:
            w = ui->TimeTuesday;
            break;
        case 3:
            w = ui->TimeWednesday;
            break;
        case 4:
            w = ui->TimeThrursday;
            break;
        case 5:
            w = ui->TimeFriday;
            break;
        case 6:
        default:
            w = ui->TimeSaturday;
            break;
        }
        w->setFrom(cal->HoraIngreso().value());
        w->setTo(cal->HoraEgreso().value());
    }
}

void DlgEmployee::setupAssignment(AvailabilityWidget *w, int day)
{
    w->setDay(day);
    QDateTime dt;
    dt.setDate(QDate::currentDate());
    dt.setTime(QTime(9, 0, 0, 0));
    w->setFrom(dt);
    dt.setTime(QTime(18, 0, 0, 0));
    w->setTo(dt);
}

void DlgEmployee::setupScreen()
{
    ui->txtID->setText("");
    ui->txtLastName->setText("");
    ui->txtNames->setText("");
    setupAssignment(ui->TimeFriday, 5);
    setupAssignment(ui->TimeMonday, 1);
    setupAssignment(ui->TimeSaturday, 6);
    setupAssignment(ui->TimeSunday, 0);
    setupAssignment(ui->TimeThrursday, 4);
    setupAssignment(ui->TimeTuesday, 2);
    setupAssignment(ui->TimeWednesday, 3);
}


QString DlgEmployee::Apellido()
{
    return ui->txtLastName->text();
}

QString DlgEmployee::Nombres()
{
    return ui->txtNames->text();
}

QDate DlgEmployee::FechaIngreso()
{
    return ui->dateStart->date();
}

QString DlgEmployee::Legajo()
{
    return ui->txtID->text();
}

CapacidadPersonaSectorLst DlgEmployee::Capacities()
{
    CapacidadPersonaSectorLst res(new QList<CapacidadPersonaSectorPtr>());

    for (int i = 0; i < ui->treeCapacities->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *treeitem = ui->treeCapacities->topLevelItem(i);
        CapacityWidget * w = qobject_cast<CapacityWidget *>(ui->treeCapacities->itemWidget(treeitem, 0));
        CapacidadPersonaSectorPtr p(new CapacidadPersonaSector());
        p->IDEmpleado().setValue(m_Empleado->IDEmpleado());
        p->IDSector().setValue(DataStore::instance()->getSectores()->getSector(w->Sector())->IDSector().value());
        p->ID_SubSector().setValue(DataStore::instance()->getSubSectores()->getSubSector(p->IDSector().value(), w->SubSector())->IDSubsector().value());
        p->Capacidad().setValue(w->Capacity());
        res->push_back(p);
    }

    return res;
}

CalendarioPersonaPtr DlgEmployee::getAssignment(AvailabilityWidget *w)
{
    CalendarioPersonaPtr p(new CalendarioPersona());

    p->IDEmpleado().setValue(m_Empleado->IDEmpleado().value());

    p->HoraIngreso().setValue(w->FromTime().time());
    p->HoraEgreso().setValue(w->ToTime().time());
    p->Dia().setValue(w->Day());

    return p;
}

CalendarioPersonaLst DlgEmployee::Disponibilidades()
{
    CalendarioPersonaLst res(new QList<CalendarioPersonaPtr>());

    res->push_back(getAssignment(ui->TimeSunday));
    res->push_back(getAssignment(ui->TimeMonday));
    res->push_back(getAssignment(ui->TimeTuesday));
    res->push_back(getAssignment(ui->TimeWednesday));
    res->push_back(getAssignment(ui->TimeThrursday));
    res->push_back(getAssignment(ui->TimeFriday));
    res->push_back(getAssignment(ui->TimeSaturday));

    return res;
}
