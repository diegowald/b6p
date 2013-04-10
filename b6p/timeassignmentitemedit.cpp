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
    allowOverWorking = false;

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
    loadingData = true;
    llenarSectores();
    loadingData = true;
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
    setIDEmpleadoNull();
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
    setIDEmpleadoNull();
}


void TimeAssignmentItemEdit::on_timeInicio_TimeChanged(int newTime)
{
    if (ui->timeFin->timeSeconds() < newTime)
        ui->timeFin->setTime(newTime);

    ui->widget->setStartAssignment(newTime);
    llenarEmpleados();
    setIDEmpleadoNull();
    emit AssignmentChanged(newTime, ui->timeFin->timeSeconds());
}

void TimeAssignmentItemEdit::on_timeFin_TimeChanged(int newTime)
{
    if (ui->timeInicio->timeSeconds() > newTime)
        ui->timeInicio->setTime(newTime);

    ui->widget->setEndAssignment(newTime);
    llenarEmpleados();
    setIDEmpleadoNull();
    emit AssignmentChanged(ui->timeInicio->timeSeconds(), newTime);
}

void TimeAssignmentItemEdit::llenarEmpleados()
{
    int IDSector = ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
    int IDSubSector = -1;
    if (ui->cboSubsectores->count() > 0)
        IDSubSector = ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();

    int HoraInicio = ui->timeInicio->timeSeconds();
    int HoraFin = ui->timeFin->timeSeconds();

    emps = DataStore::instance()->getEmpleados()->getAll(IDSector, IDSubSector, date, HoraInicio, HoraFin, false);
    ui->cboEmpleado->clear();
    ui->cboEmpleado->setCurrentIndex(-1);
    foreach(EmployeeCalculatedCapacityPtr e, *emps)
    {
        connect(e.get(), SIGNAL(calcularHorasPreviamenteTrabajadas(int, int &)), this, SLOT(on_calcularHorasPreviamenteTrabajadas(int,int&)));
        QString nombre = "%1, %2";
        nombre = nombre.arg(e->EmpleadoAsignado()->Apellido().value()).arg(e->EmpleadoAsignado()->Nombre().value());
        ui->cboEmpleado->addItem(nombre, e->EmpleadoAsignado()->IDEmpleado().value());
    }
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
    qDebug() << ui->cboEmpleado->currentIndex();
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
    loadingData = true;
    ui->cboSectores->setCurrentIndex(ui->cboSectores->findData(value, Qt::UserRole));
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSectorNull()
{
    loadingData = true;
    ui->cboSectores->setCurrentIndex(-1);
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSubSector(int value)
{
    loadingData = true;
    ui->cboSubsectores->setCurrentIndex(ui->cboSubsectores->findData(value, Qt::UserRole));
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSubSectorNull()
{
    loadingData = true;
    ui->cboSubsectores->setCurrentIndex(-1);
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDEmpleado(int value)
{
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(ui->cboEmpleado->findData(value));
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDEmpleadoNull()
{
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(-1);
    loadingData = false;
}

void TimeAssignmentItemEdit::setHoraInicio(int value)
{
    loadingData = true;
    ui->timeInicio->setTime(value);
    loadingData = false;
}

void TimeAssignmentItemEdit::setHoraFin(int value)
{
    loadingData = true;
    ui->timeFin->setTime(value);
    loadingData = false;
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
    // Obtengo la capacidad calculada del empleado.
    EmployeeCalculatedCapacityPtr ec;
    foreach(ec, *emps)
    {
        if (ec->EmpleadoAsignado()->IDEmpleado().value() == ui->cboEmpleado->itemData(index, Qt::UserRole))
            break;
    }

    bool warningHoras = false;
    bool warningDias = false;

    if (ec.get())
    {
        warningHoras = ec->hasWarningsHoras();
        warningDias = ec->hasWarningsDias();
    }
    bool warnings = warningDias || warningHoras;
    if (!loadingData && warnings && !allowOverWorking)
    {
        QString message;
        if (warningHoras)
            message = tr("Allow the employee to have less than minimum of hours assigned?");
        else if (warningDias)
            message = tr("Allow overwork?");
        allowOverWorking = !(QMessageBox::question(this,
                                                   tr("Warning: Detected problem with hours or days"),
                                                   message,
                                                   QMessageBox::Yes | QMessageBox::No,
                                                   QMessageBox::No) == QMessageBox::No);
    }

    if (ec.get())
        emit refreshColorAssignments(ec->EmpleadoAsignado()->IDEmpleado().value());
    QColor color;

    if (!allowOverWorking && warnings)
        color = Qt::red;
    else if (warningDias)
        color = Qt::darkYellow;
    else if (warningHoras)
        color = Qt::yellow;
    else
        color = Qt::darkGreen;

    ui->widget->setAssignmentColor(color);
}

void TimeAssignmentItemEdit::recalculateColorAssignments(int IDEmpleado)
{
    if (ui->cboEmpleado->itemData(ui->cboEmpleado->currentIndex(), Qt::UserRole) != IDEmpleado)
        return;

    EmployeeCalculatedCapacityPtr ec;
    foreach(ec, *emps)
    {
        if (ec->EmpleadoAsignado()->IDEmpleado().value() == IDEmpleado)
            break;
    }
    bool warningHoras = ec->hasWarningsHoras();
    bool warningDias = ec->hasWarningsDias();
    bool warnings = warningDias || warningHoras;
    QColor color;

    if (!allowOverWorking && warnings)
        color = Qt::red;
    else if (warningDias)
        color = Qt::darkYellow;
    else if (warningHoras)
        color = Qt::yellow;
    else
        color = Qt::darkGreen;

    ui->widget->setAssignmentColor(color);
}

void TimeAssignmentItemEdit::on_calcularHorasPreviamenteTrabajadas(int IDEmpleado, int &horas)
{
    emit calcularHoras(IDEmpleado, horas);
    if (horas == 0)
        horas = (HoraFin() - HoraInicio()) / 3600;
}

void TimeAssignmentItemEdit::setAllowOverWorking(bool value)
{
    allowOverWorking = value;
}

bool TimeAssignmentItemEdit::AllowOverWorking()
{
    return allowOverWorking;
}
