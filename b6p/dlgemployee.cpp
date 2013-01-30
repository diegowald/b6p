#include "dlgemployee.h"
#include "ui_dlgemployee.h"
#include "capacitywidget.h"

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
    // Informacion basica
    ui->txtID->setText(empleado->Legajo().value());
    ui->txtLastName->setText(empleado->Apellido().value());
    ui->txtNames->setText(empleado->Nombre().value());
    ui->dateStart->setDate(empleado->FechaIngreso().value());

    // Sectores, subsectores y capacidades
    CapacidadPersonaSectorLst caps = empleado->getCapacities();
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
    CalendarioPersonaLst cals = empleado->getDisponibilidad();
    foreach (CalendarioPersonaPtr cal, *cals.get())
    {
        AvailabilityWidget *w = NULL;
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

EmpleadoPtr DlgEmployee::getData()
{
}

void DlgEmployee::setupAssignment(AvailabilityWidget *w, QString label)
{
    w->setLabel(label);
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
    setupAssignment(ui->TimeFriday, tr("Friday"));
    setupAssignment(ui->TimeMonday, tr("Monday"));
    setupAssignment(ui->TimeSaturday, tr("Saturday"));
    setupAssignment(ui->TimeSunday, tr("Sunday"));
    setupAssignment(ui->TimeThrursday, tr("Thursday"));
    setupAssignment(ui->TimeTuesday, tr("Tuesday"));
    setupAssignment(ui->TimeWednesday, tr("Wednesday"));
}
