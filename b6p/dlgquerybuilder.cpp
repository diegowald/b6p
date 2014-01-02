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
#include "dlgquerybuilder.h"
#include "ui_dlgquerybuilder.h"
#include "QsLog.h"
#include "datastore.h"

DlgQueryBuilder::DlgQueryBuilder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgQueryBuilder)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    fillSectores();
    fillEmployees();
}

DlgQueryBuilder::~DlgQueryBuilder()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgQueryBuilder::fillEmployees()
{
    QLOG_TRACE_FN();
    ui->cboEmployee->clear();
    EmpleadosLst empleados = DataStore::instance()->getEmpleados()->getAll(true);
    ui->cboEmployee->addItem(tr("all"), -1);
    foreach(EmpleadoPtr empleado, *empleados)
    {
        ui->cboEmployee->addItem(empleado->Apellido().value() +
                                 empleado->Nombre().value(),
                                 empleado->IDEmpleado().value());
    }
}

void DlgQueryBuilder::fillSectores()
{
    QLOG_TRACE_FN();
    ui->cboSector->clear();
    SectorLst sectores = DataStore::instance()->getSectores()->getAll(true, true);
    ui->cboSector->addItem(tr("all"), -1);
    foreach (SectorPtr sector, *sectores)
    {
        ui->cboSector->addItem(sector->Nombre().value(),
                               sector->IDSector().value());
    }
}

void DlgQueryBuilder::fillSubSectores(int IDSector)
{
    QLOG_TRACE_FN();
    ui->cboSubSector->clear();
    SubSectoresLst subsectores = DataStore::instance()->getSubSectores()->getAll(IDSector, true);
    ui->cboSubSector->addItem(tr("all"), -1);
    foreach (SubSectorPtr subsector, *subsectores)
    {
        ui->cboSubSector->addItem(subsector->Nombre().value(),
                                  subsector->IDSubsector().value());
    }
}


void DlgQueryBuilder::on_cboSector_currentIndexChanged(int)
{
    QLOG_TRACE_FN();
    fillSubSectores(ui->cboSector->itemData(ui->cboSector->currentIndex()).toInt());
}


void DlgQueryBuilder::setDateFrom(const QDate &from)
{
    QLOG_TRACE_FN();
    ui->dateFrom->setDate(from);
}

void DlgQueryBuilder::setDateTo(const QDate &to)
{
    QLOG_TRACE_FN();
    ui->dateTo->setDate(to);
}

void DlgQueryBuilder::setIDSector(int id)
{
    QLOG_TRACE_FN();
    ui->cboSector->setCurrentIndex(ui->cboSector->findData(id));
}

void DlgQueryBuilder::setIDSubSector(int id)
{
    QLOG_TRACE_FN();
    ui->cboSubSector->setCurrentIndex(ui->cboSubSector->findData(id));
}

void DlgQueryBuilder::setIDEmployee(int id)
{
    QLOG_TRACE_FN();
    ui->cboEmployee->setCurrentIndex(ui->cboEmployee->findData(id));
}


QDate DlgQueryBuilder::dateFrom()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgQueryBuilder::dateTo()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}

int DlgQueryBuilder::idSector()
{
    QLOG_TRACE_FN();
    return ui->cboSector->itemData(ui->cboSector->currentIndex()).toInt();
}

int DlgQueryBuilder::idSubSector()
{
    QLOG_TRACE_FN();
    return ui->cboSubSector->itemData(ui->cboSubSector->currentIndex()).toInt();
}


int DlgQueryBuilder::idEmployee()
{
    QLOG_TRACE_FN();
    return ui->cboEmployee->itemData(ui->cboEmployee->currentIndex()).toInt();
}

void DlgQueryBuilder::setSummarizeDays(bool value)
{
    QLOG_TRACE_FN();
    ui->chkDays->setChecked(value);
}

void DlgQueryBuilder::setSummarizeSectors(bool value)
{
    QLOG_TRACE_FN();
    ui->chkSectors->setChecked(value);
}

void DlgQueryBuilder::setSummarizeSubsectors(bool value)
{
    QLOG_TRACE_FN();
    ui->chkSubSectors->setChecked(value);
}

void DlgQueryBuilder::setSummarizeEmployee(bool value)
{
    QLOG_TRACE_FN();
    ui->chkEmployees->setChecked(value);
}

bool DlgQueryBuilder::summarizeDays() const
{
    QLOG_TRACE_FN();
    return ui->chkDays->checkState() == Qt::Checked;
}

bool DlgQueryBuilder::summarizeSectors() const
{
    QLOG_TRACE_FN();
    return ui->chkSectors->checkState() == Qt::Checked;
}

bool DlgQueryBuilder::summarizeSubsectors() const
{
    QLOG_TRACE_FN();
    return ui->chkSubSectors->checkState() == Qt::Checked;
}

bool DlgQueryBuilder::summarizeEmployee() const
{
    QLOG_TRACE_FN();
    return ui->chkEmployees->checkState() == Qt::Checked;
}

void DlgQueryBuilder::setEmployeeEnabled(bool enabled)
{
    QLOG_TRACE_FN();
    ui->cboEmployee->setEnabled(enabled);
    ui->chkEmployees->setEnabled(enabled);
}

void DlgQueryBuilder::setSectorEnabled(bool enabled)
{
    QLOG_TRACE_FN();
    ui->cboSector->setEnabled(enabled);
    ui->chkSectors->setEnabled(enabled);
}

void DlgQueryBuilder::setSubSectorEnabled(bool enabled)
{
    QLOG_TRACE_FN();
    ui->cboSubSector->setEnabled(enabled);
    ui->chkSubSectors->setEnabled(enabled);
}

void DlgQueryBuilder::setDateEnabled(bool enabled)
{
    QLOG_TRACE_FN();
    ui->chkDays->setEnabled(enabled);
}
