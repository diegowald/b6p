#include "timeassignmentitemedit.h"
#include "ui_timeassignmentitemedit.h"
#include "datastore.h"
#include "days.h"

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


    DAYS Dia = Days::DayOfWeek2DAYS(date.dayOfWeek());

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

int TimeAssignmentItemEdit::IDSector()
{
    return ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
}

bool TimeAssignmentItemEdit::isSubSectorEmpty()
{
    return (ui->cboSubsectores->count() == 0);
}

int TimeAssignmentItemEdit::IDSubSector()
{
    return ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();
}

bool TimeAssignmentItemEdit::isEmpleadoEmpty()
{
    return (ui->cboEmpleado->count() == 0);
}

int TimeAssignmentItemEdit::IDEmpleado()
{
    return ui->cboEmpleado->itemData(ui->cboEmpleado->currentIndex(), Qt::UserRole).toInt();
}

QTime TimeAssignmentItemEdit::HoraInicio()
{
    return ui->timeInicio->time();
}

QTime TimeAssignmentItemEdit::HoraFin()
{
    return ui->timeFin->time();
}

void TimeAssignmentItemEdit::setDate(QDate value)
{
    date = value;
}

QDate TimeAssignmentItemEdit::Date()
{
    return date;
}

void TimeAssignmentItemEdit::setIDSector(int value)
{
    ui->cboSectores->setCurrentIndex(ui->cboSectores->findData(value, Qt::UserRole));
}

void TimeAssignmentItemEdit::setIDSectorNull()
{
    ui->cboSectores->setCurrentIndex(-1);
}

void TimeAssignmentItemEdit::setIDSubSector(int value)
{
    ui->cboSubsectores->setCurrentIndex(ui->cboSubsectores->findData(value, Qt::UserRole));
}

void TimeAssignmentItemEdit::setIDSubSectorNull()
{
    ui->cboSubsectores->setCurrentIndex(-1);
}

void TimeAssignmentItemEdit::setIDEmpleado(int value)
{
    ui->cboEmpleado->setCurrentIndex(ui->cboEmpleado->findData(value));
}

void TimeAssignmentItemEdit::setIDEmpleadoNull()
{
    ui->cboEmpleado->setCurrentIndex(-1);
}

void TimeAssignmentItemEdit::setHoraInicio(QTime value)
{
    ui->timeInicio->setTime(value);
}

void TimeAssignmentItemEdit::setHoraFin(QTime value)
{
    ui->timeFin->setTime(value);
}
