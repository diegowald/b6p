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
#include "dlglicencia.h"
#include "ui_dlglicencia.h"
#include "empleado.h"
#include "datastore.h"
#include "QsLog.h"

DlgLicencia::DlgLicencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLicencia)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    llenarComboConTiposLicencia();
    ui->dateFrom->setDate(QDate::currentDate());
    ui->dateTo->setDate(QDate::currentDate());
}

DlgLicencia::~DlgLicencia()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgLicencia::llenarComboConTiposLicencia()
{
    QLOG_TRACE_FN();
    QStringList tipos = DataStore::instance()->getLicencias()->getDistinctLicenceType();
    ui->cboType->clear();
    ui->cboType->clearEditText();
    foreach (QString tipo, tipos)
    {
        ui->cboType->addItem(tipo, tipo);
    }
}

void DlgLicencia::setData(LicenciaEmpleadoPtr licencia)
{
    QLOG_TRACE_FN();
    EmpleadoPtr empleado = DataStore::instance()->getEmpleados()->getEmpleado(licencia->IDEmpleado().value(), false);
    idEmpleado = empleado->IDEmpleado().value();
    ui->lblEmployee->setText(QString("%1, %2").arg(empleado->Apellido().value(), empleado->Nombre().value()));
    if (!licencia->FechaDesde().isNull())
        ui->dateFrom->setDate(licencia->FechaDesde().value());
    if (!licencia->FechaHasta().isNull())
        ui->dateTo->setDate(licencia->FechaHasta().value());
    ui->cboType->setCurrentText(licencia->TipoLicencia().isNull() ? "" : licencia->TipoLicencia().value());
    ui->txtNotes->setText(licencia->Descripcion().isNull() ? "" : licencia->Descripcion().value());
}

int DlgLicencia::IDEmpleado()
{
    QLOG_TRACE_FN();
    return idEmpleado;
}

QDate DlgLicencia::FechaDesde()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgLicencia::FechaHasta()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}

QString DlgLicencia::TipoLicencia()
{
    QLOG_TRACE_FN();
    QLOG_TRACE() << ui->cboType->currentText();
    return ui->cboType->currentText();
}

QString DlgLicencia::Descripcion()
{
    QLOG_TRACE_FN();
    QLOG_TRACE() << ui->txtNotes->text();
    return ui->txtNotes->text();
}
