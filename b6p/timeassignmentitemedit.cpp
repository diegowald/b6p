#include "timeassignmentitemedit.h"
#include "ui_timeassignmentitemedit.h"
#include "datastore.h"
#include "days.h"
#include <QMessageBox>


TimeAssignmentItemEdit::TimeAssignmentItemEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeAssignmentItemEdit)
{
    ui->setupUi(this);

    ui->timeInicio->SetSecondsVisibility(false);
    ui->timeFin->SetSecondsVisibility(false);

    ui->timeInicio->setValidRange(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                                  DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeFin->setValidRange(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                               DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeFin->setTime(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));


    connect(ui->timeInicio, SIGNAL(timeChanged(int)), this, SLOT(on_timeInicio_TimeChanged(int)));
    connect(ui->timeFin, SIGNAL(timeChanged(int)), this, SLOT(on_timeFin_TimeChanged(int)));

    ui->widget->setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    ui->widget->setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    loadingData = false;
    llenarSectores();
}

TimeAssignmentItemEdit::~TimeAssignmentItemEdit()
{
    delete ui;
}

void TimeAssignmentItemEdit::llenarSectores()
{
    ui->cboSectores->clear();
    SectorLst sectores = DataStore::instance()->getSectores()->getAll(true, false);
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
    SubSectoresLst ss = DataStore::instance()->getSubSectores()->getAll(IDSector, false);
    foreach(SubSectorPtr ssp, *ss)
    {
        ui->cboSubsectores->addItem(ssp->Nombre().value(), ssp->IDSubsector().value());
    }
}

void TimeAssignmentItemEdit::on_cboSubsectores_currentIndexChanged(int)
{
    llenarEmpleados();
}


void TimeAssignmentItemEdit::on_timeInicio_TimeChanged(int newTime)
{
    if (ui->timeFin->timeSeconds() < newTime)
        ui->timeFin->setTime(newTime);

    ui->widget->setStartAssignment(newTime);
    llenarEmpleados();
    emit AssignmentChanged(newTime, ui->timeFin->timeSeconds());
}

void TimeAssignmentItemEdit::on_timeFin_TimeChanged(int newTime)
{
    if (ui->timeInicio->timeSeconds() > newTime)
        ui->timeInicio->setTime(newTime);

    ui->widget->setEndAssignment(newTime);
    llenarEmpleados();
    emit AssignmentChanged(ui->timeInicio->timeSeconds(), newTime);
}

void TimeAssignmentItemEdit::llenarEmpleados()
{
    int IDSector = ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
    int IDSubSector = -1;
    if (ui->cboSubsectores->count() > 0)
        IDSubSector = ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();


    DAYS Dia = Days::DayOfWeek2DAYS(date.dayOfWeek());

    int HoraInicio = ui->timeInicio->timeSeconds();
    int HoraFin = ui->timeFin->timeSeconds();

    loadingData = true;
    emps = DataStore::instance()->getEmpleados()->getAll(IDSector, IDSubSector, Dia, HoraInicio, HoraFin, false);
    ui->cboEmpleado->clear();
    foreach(EmployeeCalculatedCapacityPtr e, *emps)
    {
        QString nombre = "%1, %2";
        nombre = nombre.arg(e->EmpleadoAsignado()->Apellido().value()).arg(e->EmpleadoAsignado()->Nombre().value());
        ui->cboEmpleado->addItem(nombre, e->EmpleadoAsignado()->IDEmpleado().value());
    }
    loadingData = false;
}

double TimeAssignmentItemEdit::CantidadHoras()
{
    int delta = ui->timeFin->timeSeconds() - ui->timeInicio->timeSeconds();
    double cantHoras = delta / 3600.0;
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

int TimeAssignmentItemEdit::HoraInicio()
{
    return ui->timeInicio->timeSeconds();
}

int TimeAssignmentItemEdit::HoraFin()
{
    return ui->timeFin->timeSeconds();
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
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(ui->cboEmpleado->findData(value));
    loadingData = true;
}

void TimeAssignmentItemEdit::setIDEmpleadoNull()
{
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(-1);
    loadingData = true;
}

void TimeAssignmentItemEdit::setHoraInicio(int value)
{
    ui->timeInicio->setTime(value);
}

void TimeAssignmentItemEdit::setHoraFin(int value)
{
    ui->timeFin->setTime(value);
}

void TimeAssignmentItemEdit::setData(QVariant data)
{
    m_Data = data;
}

QVariant TimeAssignmentItemEdit::data()
{
    return m_Data;
}

void TimeAssignmentItemEdit::on_cboEmpleado_currentIndexChanged(int index)
{
    if (loadingData)
        return;

    // Obtengo la capacidad calculada del empleado.
    EmployeeCalculatedCapacityPtr ec;
    foreach(ec, *emps)
    {
        if (ec->EmpleadoAsignado()->IDEmpleado().value() == ui->cboEmpleado->itemData(index, Qt::UserRole))
            break;
    }

    if (ec->hasWarnings())
    {
        if (QMessageBox::question(this,
                                  tr("Warning: overwork detected"),
                                  tr("Allow overwork?"),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No) == QMessageBox::No)
        {
            ui->widget->setAssignmentColor(Qt::red);
            return;
        }
    }

    if (ec->DiasPreviamenteTrabajados() > DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 365))
        ui->widget->setAssignmentColor(Qt::darkYellow);
    else if (ec->HorasPreviamenteTrabajadas() > 2)
        ui->widget->setAssignmentColor(Qt::yellow);
    else
        ui->widget->setAssignmentColor(Qt::darkGreen);
}
