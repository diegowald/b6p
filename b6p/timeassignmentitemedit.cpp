/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "timeassignmentitemedit.h"
#include "ui_timeassignmentitemedit.h"
#include "datastore.h"
#include "days.h"
#include <QMessageBox>
#include <QsLog.h>

TimeAssignmentItemEdit::TimeAssignmentItemEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeAssignmentItemEdit),
    loadingData(true),
    allowOverWorking(false),
    previousSelectedEmployee(-1)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    allowOverWorking = false;

    ui->timeInicio->setbeyondThisDayVisibility(false);

    ui->timeInicio->setValidRange(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                                  DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeInicio->setTime(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    ui->timeFin->setValidRange(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                               DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeFin->setTime(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));


    connect(ui->timeInicio, SIGNAL(timeChanged(int)), this, SLOT(on_timeInicio_TimeChanged(int)));
    connect(ui->timeFin, SIGNAL(timeChanged(int)), this, SLOT(on_timeFin_TimeChanged(int)));

    ui->widget->setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    ui->widget->setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));

    currentAssignment.startAssignment = DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0);
    currentAssignment.endAssignment = DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400);

    ui->widget->clearAssignments();
    ui->widget->addAssignment(currentAssignment);

    loadingData = true;
    llenarSectores();
}

TimeAssignmentItemEdit::~TimeAssignmentItemEdit()
{
    QLOG_TRACE_FN();
    delete ui;
}

void TimeAssignmentItemEdit::llenarSectores()
{
    QLOG_TRACE_FN();
    ui->cboSectores->clear();
    SectorLst sectores = DataStore::instance()->getSectores()->getAll(true, false);
    foreach(SectorPtr s, *sectores)
    {
        ui->cboSectores->addItem(s->Nombre().value(), s->IDSector().value());
    }
}

void TimeAssignmentItemEdit::on_cboSectores_currentIndexChanged(int index)
{
    QLOG_TRACE_FN();
    llenarSubSectores(ui->cboSectores->itemData(index, Qt::UserRole).toInt());
    llenarEmpleados();
    setIDEmpleadoNull();
    emit sectorChanged(ui->cboSectores->currentText());
}

void TimeAssignmentItemEdit::llenarSubSectores(int IDSector)
{
    QLOG_TRACE_FN();
    ui->cboSubsectores->clear();
    SubSectoresLst ss = DataStore::instance()->getSubSectores()->getAll(IDSector, false);
    foreach(SubSectorPtr ssp, *ss)
    {
        ui->cboSubsectores->addItem(ssp->Nombre().value(), ssp->IDSubsector().value());
    }
}

void TimeAssignmentItemEdit::on_cboSubsectores_currentIndexChanged(int)
{
    QLOG_TRACE_FN();
    llenarEmpleados();
    setIDEmpleadoNull();
    emit subSectorChanged(ui->cboSubsectores->currentText());
}


void TimeAssignmentItemEdit::on_timeInicio_TimeChanged(int newTime)
{
    QLOG_TRACE_FN();
    if (ui->timeFin->timeSeconds() < newTime)
        ui->timeFin->setTime(newTime);

    currentAssignment.startAssignment = newTime;
    ui->widget->clearAssignments();
    ui->widget->addAssignment(currentAssignment);
    llenarEmpleados();
    setIDEmpleadoNull();
    emit AssignmentChanged(newTime, ui->timeFin->timeSeconds());
}

void TimeAssignmentItemEdit::on_timeFin_TimeChanged(int newTime)
{
    QLOG_TRACE_FN();
    if (ui->timeInicio->timeSeconds() > newTime)
        ui->timeInicio->setTime(newTime);

    currentAssignment.endAssignment = newTime;
    ui->widget->clearAssignments();
    ui->widget->addAssignment(currentAssignment);
    llenarEmpleados();
    setIDEmpleadoNull();
    emit AssignmentChanged(ui->timeInicio->timeSeconds(), newTime);
}

void TimeAssignmentItemEdit::recalculateAvailableEmployees()
{
    QLOG_TRACE_FN();
    int previouslySelectedEmployee = IDEmpleado();
    llenarEmpleados();
    setIDEmpleado(previouslySelectedEmployee);
}

void TimeAssignmentItemEdit::llenarEmpleados()
{
    QLOG_TRACE_FN();
    allowOverWorking = false;
    int IDSector = ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
    int IDSubSector = -1;
    if (ui->cboSubsectores->count() > 0)
        IDSubSector = ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();

    int HoraInicio = ui->timeInicio->timeSeconds();
    int HoraFin = ui->timeFin->timeSeconds();

    emps = DataStore::instance()->getEmpleados()->getAll(IDSector, IDSubSector, date, HoraInicio, HoraFin, false);
    ui->cboEmpleado->clear();
    ui->cboEmpleado->addItem("", -1);
    ui->cboEmpleado->setCurrentIndex(-1);
    foreach(EmployeeCalculatedCapacityPtr e, *emps)
    {
        connect(e.data(), SIGNAL(calcularHorasPreviamenteTrabajadas(int, int &)), this, SLOT(on_calcularHorasPreviamenteTrabajadas(int,int&)));
        QString nombre = "%1, %2";
        nombre = nombre.arg(e->EmpleadoAsignado()->Apellido().value()).arg(e->EmpleadoAsignado()->Nombre().value());
        ui->cboEmpleado->addItem(nombre, e->EmpleadoAsignado()->IDEmpleado().value());
    }
}

double TimeAssignmentItemEdit::CantidadHoras()
{
    QLOG_TRACE_FN();
    int delta = ui->timeFin->timeSeconds() - ui->timeInicio->timeSeconds();
    double cantHoras = delta / 3600.0;
    return cantHoras;
}

int TimeAssignmentItemEdit::IDSector()
{
    QLOG_TRACE_FN();
    return ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
}

bool TimeAssignmentItemEdit::isSubSectorEmpty()
{
    QLOG_TRACE_FN();
    return (ui->cboSubsectores->count() == 0);
}

int TimeAssignmentItemEdit::IDSubSector()
{
    QLOG_TRACE_FN();
    return ui->cboSubsectores->itemData(ui->cboSubsectores->currentIndex(), Qt::UserRole).toInt();
}

bool TimeAssignmentItemEdit::isEmpleadoEmpty()
{
    QLOG_TRACE_FN();
    return (ui->cboEmpleado->count() == 0);
}

int TimeAssignmentItemEdit::IDEmpleado()
{
    QLOG_TRACE_FN();
    return ui->cboEmpleado->itemData(ui->cboEmpleado->currentIndex(), Qt::UserRole).toInt();
}

int TimeAssignmentItemEdit::HoraInicio()
{
    QLOG_TRACE_FN();
    return ui->timeInicio->timeSeconds();
}

int TimeAssignmentItemEdit::HoraFin()
{
    QLOG_TRACE_FN();
    return ui->timeFin->timeSeconds();
}

void TimeAssignmentItemEdit::setDate(QDate value)
{
    QLOG_TRACE_FN();
    date = value;
}

QDate TimeAssignmentItemEdit::Date()
{
    QLOG_TRACE_FN();
    return date;
}

void TimeAssignmentItemEdit::setIDSector(int value)
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboSectores->setCurrentIndex(ui->cboSectores->findData(value, Qt::UserRole));
    recalculateColorAssignments(ui->cboEmpleado->itemData(ui->cboEmpleado->currentIndex(), Qt::UserRole).toInt());
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSectorNull()
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboSectores->setCurrentIndex(-1);
    emit sectorChanged("");
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSubSector(int value)
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboSubsectores->setCurrentIndex(ui->cboSubsectores->findData(value, Qt::UserRole));
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDSubSectorNull()
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboSubsectores->setCurrentIndex(-1);
    emit subSectorChanged("");
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDEmpleado(int value)
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(ui->cboEmpleado->findData(value));
    recalculateColorAssignments(value);
    loadingData = false;
}

void TimeAssignmentItemEdit::setIDEmpleadoNull()
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->cboEmpleado->setCurrentIndex(-1);
    emit employeeChanged("");
    loadingData = false;
}

void TimeAssignmentItemEdit::setHoraInicio(int value)
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->timeInicio->setTime(value);
    loadingData = false;
}

void TimeAssignmentItemEdit::setHoraFin(int value)
{
    QLOG_TRACE_FN();
    loadingData = true;
    ui->timeFin->setTime(value);
    loadingData = false;
}

void TimeAssignmentItemEdit::setData(QVariant data)
{
    QLOG_TRACE_FN();
    m_Data = data;
}

QVariant TimeAssignmentItemEdit::data()
{
    QLOG_TRACE_FN();
    return m_Data;
}

void TimeAssignmentItemEdit::on_cboEmpleado_currentIndexChanged(int index)
{
    QLOG_TRACE_FN();
    if (previousSelectedEmployee != ui->cboEmpleado->itemData(index, Qt::UserRole))
        allowOverWorking = false;
    previousSelectedEmployee = ui->cboEmpleado->itemData(index, Qt::UserRole).toInt();
    // Obtengo la capacidad calculada del empleado.
    EmployeeCalculatedCapacityPtr emp;
    foreach(EmployeeCalculatedCapacityPtr ec, *emps)
    {
        if (ec->EmpleadoAsignado()->IDEmpleado().value() == ui->cboEmpleado->itemData(index, Qt::UserRole))
        {
            emp = ec;
            break;
        }
    }

    bool warningHorasUnderwork = false;
    bool warningHorasOverwork = false;
    bool warningDias = false;

    if (emp.data())
    {
        warningHorasUnderwork = emp->hasWarningsHorasMenorAMinimo();
        warningHorasOverwork = emp->hasWarningsHorasMayorAMaximo();
        warningDias = emp->hasWarningsDias();
    }
    bool warnings = warningDias || warningHorasUnderwork || warningHorasOverwork;

    if (!loadingData && warnings && !allowOverWorking)
    {
        QString message;
        if (warningHorasUnderwork)
            message = tr("Allow the employee to have less than minimum of hours assigned?");
        else if (warningHorasOverwork)
            message = tr("Allow the employee to do extra hours?");
        else if (warningDias)
            message = tr("Allow overwork?");
        allowOverWorking = !(QMessageBox::question(this,
                                                   tr("Warning: Detected problem with hours or days"),
                                                   message,
                                                   QMessageBox::Yes | QMessageBox::No,
                                                   QMessageBox::No) == QMessageBox::No);
        if (allowOverWorking)
            emit AllowOverWorkingForEmployee(emp->EmpleadoAsignado()->IDEmpleado().value());
    }

    emit refreshColorAssignments();
    emit employeeChanged(ui->cboEmpleado->currentText());
}

void TimeAssignmentItemEdit::recalculateColorAssignments(int IDEmpleado)
{
    QLOG_TRACE_FN();
    if (ui->cboEmpleado->itemData(ui->cboEmpleado->currentIndex(), Qt::UserRole) != IDEmpleado)
        return;

    EmployeeCalculatedCapacityPtr emp;
    foreach(EmployeeCalculatedCapacityPtr ec, *emps)
    {
        if (ec->EmpleadoAsignado()->IDEmpleado().value() == IDEmpleado)
        {
            emp = ec;
            break;
        }
    }
    bool warningHorasUnderWork = false;
    bool warningHorasOverWork = false;
    bool warningDias = false;
    if (emp.data())
    {
        warningHorasUnderWork = emp->hasWarningsHorasMenorAMinimo();
        warningHorasOverWork = emp->hasWarningsHorasMayorAMaximo();
        warningDias = emp->hasWarningsDias();
    }

    bool warnings = warningDias || warningHorasUnderWork || warningHorasOverWork;
    QColor color;

    if (!allowOverWorking && warnings)
        color = Qt::red;
    else if (warningDias)
        color = Qt::darkYellow;
    else if (warningHorasUnderWork)
        color = Qt::yellow;
    else if (warningHorasOverWork)
        color = Qt::yellow;
    else if (emp.data())
    {
        color = Qt::darkGreen;
        allowOverWorking = false; // Si esta pintado de verde -> no es necesario el overworking
    }
    else
        color = Qt::darkRed;

    ui->widget_2->setLedColor(color);

    currentAssignment.idSector = ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();

    ui->widget->clearAssignments();
    ui->widget->addAssignment(currentAssignment);
}

void TimeAssignmentItemEdit::on_calcularHorasPreviamenteTrabajadas(int IDEmpleado, int &horas)
{
    QLOG_TRACE_FN();
    emit calcularHoras(IDEmpleado, horas);
    if (horas == 0)
        horas = (HoraFin() - HoraInicio()) / 3600;
}

void TimeAssignmentItemEdit::setAllowOverWorking(bool value)
{
    QLOG_TRACE_FN();
    allowOverWorking = value;
}

bool TimeAssignmentItemEdit::AllowOverWorking()
{
    QLOG_TRACE_FN();
    return allowOverWorking;
}
