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
#include "dlgsynchronization.h"
#include "ui_dlgsynchronization.h"
#include "datastore.h"
#include "SincroManager.h"
#include <QsLog.h>


DlgSynchronization::DlgSynchronization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSynchronization)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    sincro = QSharedPointer<SincroManager>::create(this);
    fillData();

    connect(sincro.data(), SIGNAL(startingSynchro()),
            this, SLOT(on_startingSynchro()));

    connect(sincro.data(), SIGNAL(getDataFromCentralDB(QString &Name)),
            this, SLOT(on_getDataFromCentralDB(QString&)));

    connect(sincro.data(), SIGNAL(applyingChanges(QString &)),
            this, SLOT(on_applyingChanges(QString&)));

    connect(sincro.data(), SIGNAL(checkingChanges(QString &)),
            this, SLOT(on_checkingChanges(QString&)));

    connect(sincro.data(), SIGNAL(sendingData(QString &)),
            this, SLOT(on_sendingData(QString&)));

    connect(sincro.data(), SIGNAL(SynchroEnded()),
            this, SLOT(on_SynchroEnded()));

}

DlgSynchronization::~DlgSynchronization()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgSynchronization::fillData()
{
    QLOG_TRACE_FN();
    ui->lblLastSynchronization->setText(DataStore::instance()->getParametros()->getValue(Parametros::LAST_SYNCHRO, ""));
    ui->lblServerName->setText(DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, ""));
    ui->lblDatabase->setText(DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, ""));
    ui->lblUser->setText(DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, ""));
    QStringList tables = sincro->getSincroTableNames();
    foreach(QString table, tables)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, table);
        item->setData(0, Qt::UserRole, table);
        ui->treeSyncrhonizationStatus->addTopLevelItem(item);
    }
}

void DlgSynchronization::on_btnStartSynchro_pressed()
{
    QLOG_TRACE_FN();
    ui->buttonBox->setEnabled(false);

    sincro->runSincro();

    ui->buttonBox->setEnabled(true);
}

void DlgSynchronization::on_startingSynchro()
{
    QLOG_TRACE_FN();
    for (int i = 0; i < ui->treeSyncrhonizationStatus->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treeSyncrhonizationStatus->topLevelItem(i);
        item->setText(1, tr("Starting..."));
    }
}

void DlgSynchronization::on_getDataFromCentralDB(QString &tableName)
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Getting data"));
    }
}

void DlgSynchronization::on_applyingChanges(QString &tableName)
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Applying changes"));
    }
}

void DlgSynchronization::on_checkingChanges(QString &tableName)
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Checking..."));
    }
}

void DlgSynchronization::on_sendingData(QString &tableName)
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Sending data"));
    }
}

void DlgSynchronization::on_SynchroEnded()
{
    QLOG_TRACE_FN();
    for (int i = 0; i < ui->treeSyncrhonizationStatus->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treeSyncrhonizationStatus->topLevelItem(i);
        item->setText(1, "");
    }
}
