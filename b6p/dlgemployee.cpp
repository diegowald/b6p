#include "dlgemployee.h"
#include "ui_dlgemployee.h"

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
