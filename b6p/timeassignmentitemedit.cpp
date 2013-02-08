#include "timeassignmentitemedit.h"
#include "ui_timeassignmentitemedit.h"
#include "datastore.h"

TimeAssignmentItemEdit::TimeAssignmentItemEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeAssignmentItemEdit)
{
    ui->setupUi(this);


    ui->widget->setInitialTimeline(QDateTime(QDate::currentDate(),
                                             QTime(0, 0, 0, 0)));
    ui->widget->setFinalTimeline(QDateTime(QDate::currentDate(),
                                           QTime(23, 59, 59, 999)));

    ui->timeInicio->setDate(QDate::currentDate());
    ui->timeFin->setDate(QDate::currentDate());

    llenarSectores();
}

TimeAssignmentItemEdit::~TimeAssignmentItemEdit()
{
    delete ui;
}

void TimeAssignmentItemEdit::llenarSectores()
{
    ui->cboSectores->clear();
    SectorLst sectores = DataStore::instance()->getSectores()->getAll();
    foreach(SectorPtr s, *sectores)
    {
        ui->cboSectores->addItem(s->Nombre().value(), s->IDSector().value());
    }
}

void TimeAssignmentItemEdit::on_cboSectores_currentIndexChanged(int index)
{
    llenarSubSectores(ui->cboSectores->itemData(index, Qt::UserRole).toInt());
    llenarEmpleados();
}

void TimeAssignmentItemEdit::llenarSubSectores(int IDSector)
{
    ui->cboSubsectores->clear();
    SubSectoresLst ss = DataStore::instance()->getSubSectores()->getAll(IDSector);
    foreach(SubSectorPtr ssp, *ss)
    {
        ui->cboSubsectores->addItem(ssp->Nombre().value(), ssp->IDSubsector().value());
    }
}

void TimeAssignmentItemEdit::on_cboSubsectores_currentIndexChanged(int)
{
    llenarEmpleados();
}
void TimeAssignmentItemEdit::on_timeInicio_dateTimeChanged(const QDateTime &dateTime)
{
    if (ui->timeFin->dateTime().toMSecsSinceEpoch() < dateTime.toMSecsSinceEpoch())
        ui->timeFin->setDateTime(dateTime);

    ui->widget->setStartAssignment(dateTime);
    llenarEmpleados();
    emit AssignmentChanged(dateTime, ui->timeFin->dateTime());
}

void TimeAssignmentItemEdit::on_timeFin_dateTimeChanged(const QDateTime &dateTime)
{
    if (ui->timeInicio->dateTime().toMSecsSinceEpoch() > dateTime.toMSecsSinceEpoch())
        ui->timeInicio->setDateTime(dateTime);

    ui->widget->setEndAssignment(dateTime);
    llenarEmpleados();
    emit AssignmentChanged(ui->timeInicio->dateTime(), dateTime);
}

void TimeAssignmentItemEdit::llenarEmpleados()
{
    int IDSector = ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
    int IDSubSector = -1;
    if (ui->cboSubsectores->count() > 0)
        IDSubSector = ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();
    int Dia = 0;
    QTime HoraInicio = ui->timeInicio->time();
    QTime HoraFin = ui->timeFin->time();

    EmpleadosLst emps = DataStore::instance()->getEmpleados()->getAll(IDSector, IDSubSector, Dia, HoraInicio, HoraFin);
    ui->cboEmpleado->clear();
    foreach(EmpleadoPtr e, *emps)
    {
        QString nombre = "%1, %2";
        nombre = nombre.arg(e->Apellido().value()).arg(e->Nombre().value());
        ui->cboEmpleado->addItem(nombre, e->IDEmpleado().value());
    }
}

double TimeAssignmentItemEdit::CantidadHoras()
{
    qlonglong delta = ui->timeFin->dateTime().toMSecsSinceEpoch() - ui->timeInicio->dateTime().toMSecsSinceEpoch();
    double cantHoras = delta / 1000.0 / 3600.0;
    return cantHoras;
}
