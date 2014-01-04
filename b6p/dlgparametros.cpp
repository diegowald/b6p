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
#include "dlgparametros.h"
#include "ui_dlgparametros.h"
#include "datastore.h"
#include "sqlhandler.h"
#include <QsLog.h>


DlgParametros::DlgParametros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgParametros)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    ui->timeOpen->setbeyondThisDayVisibility(false);
    ui->timeOpen->setValidRange(0, 0, 0, 24, 0, 0);
    ui->timeClose->setValidRange(0, 0, 0, 36, 0, 0);
    ui->timeOpen->setTime(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    ui->timeClose->setTime(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 24 * 3600));
    ui->MinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MIN_WORKING_HOURS, 4)));
    ui->employeeMinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MIN_HOURS, 4)));
    ui->employeeMaxWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MAX_HOURS, 8)));
    ui->employeeDaysBetweenFreeDay->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 6)));

    ui->txtServer->setText(DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, ""));
    ui->txtDatabase->setText(DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, "b6p"));
    ui->txtUser->setText(DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, ""));
    ui->txtPassword->setText(DataStore::instance()->getParametros()->getValue(Parametros::PASSWORD, ""));
    ui->lblConnectionResult->clear();
    connect(ui->timeOpen, SIGNAL(IncorrectTime(QString)), this, SLOT(TimeInvalid(QString)));
    connect(ui->timeClose, SIGNAL(IncorrectTime(QString)), this, SLOT(TimeInvalid(QString)));
    ui->lblMessage->clear();

    llenarFrancos();
    llenarLoggingLevels();
}

DlgParametros::~DlgParametros()
{
    QLOG_TRACE_FN();
    delete ui;
}

int DlgParametros::getCloseTime()
{
    QLOG_TRACE_FN();
    int timeClose = ui->timeClose->timeSeconds();
    return timeClose;
}

void DlgParametros::accept()
{
    QLOG_TRACE_FN();
    DataStore::instance()->getParametros()->setValue(Parametros::OPEN_STORE, ui->timeOpen->timeSeconds());
    DataStore::instance()->getParametros()->setValue(Parametros::CLOSE_STORE, getCloseTime());
    DataStore::instance()->getParametros()->setValue(Parametros::MIN_WORKING_HOURS, ui->MinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MIN_HOURS, ui->employeeMinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MAX_HOURS, ui->employeeMaxWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, ui->employeeDaysBetweenFreeDay->text().toInt());

    DataStore::instance()->getParametros()->setValue(Parametros::SERVER_NAME, ui->txtServer->text());
    DataStore::instance()->getParametros()->setValue(Parametros::DATABASE_NAME, ui->txtDatabase->text());
    DataStore::instance()->getParametros()->setValue(Parametros::USER_NAME, ui->txtUser->text());
    DataStore::instance()->getParametros()->setValue(Parametros::PASSWORD, ui->txtPassword->text());

    DataStore::instance()->getParametros()->setValue(Parametros::FRANCO_TYPE, ui->cboWeeklyRestType->currentText());
    DataStore::instance()->getParametros()->setValue(Parametros::LOG_LEVEL, ui->cboLoggingLevel->itemData(ui->cboLoggingLevel->currentIndex()).toInt());

    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel((QsLogging::Level)ui->cboLoggingLevel->itemData(ui->cboLoggingLevel->currentIndex()).toInt());

    QDialog::accept();
}

void DlgParametros::on_pushButton_pressed()
{
    QLOG_TRACE_FN();
    QString sql = "SELECT 1;";
    SQLHandler h(ui->txtServer->text(), ui->txtDatabase->text(), ui->txtUser->text(), ui->txtPassword->text());
    RecordSet rs = h.getAll(sql);
    if (rs->count() == 1)
        ui->lblConnectionResult->setText(tr("Connection OK"));
    else
        ui->lblConnectionResult->setText(tr("Please check connection parameters"));
}

void DlgParametros::TimeInvalid(const QString &cause)
{
    QLOG_TRACE_FN();
    ui->lblMessage->setText(cause);
}

void DlgParametros::llenarFrancos()
{
    QLOG_TRACE_FN();
    ui->cboWeeklyRestType->clear();

    ui->cboWeeklyRestType->addItems(DataStore::instance()->getLicencias()->getDistinctLicenceType());

    ui->cboWeeklyRestType->setCurrentText(DataStore::instance()->getParametros()->getFrancoType());
}

void DlgParametros::llenarLoggingLevels()
{
    QLOG_TRACE_FN();
    ui->cboLoggingLevel->clear();

    ui->cboLoggingLevel->addItem(tr("Trace"), QsLogging::TraceLevel);
    ui->cboLoggingLevel->addItem(tr("Debug"), QsLogging::DebugLevel);
    ui->cboLoggingLevel->addItem(tr("Information"), QsLogging::InfoLevel);
    ui->cboLoggingLevel->addItem(tr("Warning"), QsLogging::WarnLevel);
    ui->cboLoggingLevel->addItem(tr("Error"), QsLogging::ErrorLevel);
    ui->cboLoggingLevel->addItem(tr("Fatal"), QsLogging::FatalLevel);
    ui->cboLoggingLevel->addItem(tr("Off"), QsLogging::OffLevel);

    ui->cboLoggingLevel->setCurrentIndex(
                ui->cboLoggingLevel->findData(
                    DataStore::instance()->getParametros()->getLoggingLevel()));
}
