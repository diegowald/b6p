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
#include "dlgmerge.h"
#include "ui_dlgmerge.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>

DlgMerge::DlgMerge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgMerge)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgMerge::~DlgMerge()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgMerge::setData(RecordPtr ServerRecord, RecordPtr localRecord, QStringList fieldsToShow)
{
    QLOG_TRACE_FN();
    local = localRecord;
    server = ServerRecord;
    foreach (QString key, ServerRecord->keys())
    {
        if (fieldsToShow.contains(key))
        {
            int rowNum = ui->tblData->rowCount();
            ui->tblData->insertRow(rowNum);

            // Field name
            QTableWidgetItem * item = new QTableWidgetItem();
            item->setText(key);
            ui->tblData->setItem(rowNum, 0, item);

            // Server data
            item = new QTableWidgetItem();
            item->setText((*ServerRecord)[key].toString());
            ui->tblData->setItem(rowNum, 1, item);

            // Local data
            item = new QTableWidgetItem();
            item->setText((*localRecord)[key].toString());
            ui->tblData->setItem(rowNum, 2, item);

            // Merged data (default = local data)
            item = new QTableWidgetItem();
            item->setText((*localRecord)[key].toString());
            ui->tblData->setItem(rowNum, 3, item);
        }
    }
}

RecordPtr DlgMerge::mergedRecord()
{
    QLOG_TRACE_FN();
    RecordPtr result = RecordPtr();

    foreach (QString key, server->keys()) {
        (*result)[key] = (*server)[key];
    }

    for (int row = 1; row < ui->tblData->rowCount(); ++row) {
        QString key = ui->tblData->item(row, 0)->text();

        if (ui->tblData->item(row, 1)->text() == ui->tblData->item(row, 3)->text())
            (*result)[key] = (*server)[key];
        else
            (*result)[key] = (*local)[key];

        qDebug() << key;
        qDebug() << (*server)[key];
        qDebug() << (*local)[key];

        qDebug() << (*result)[key];
    }

    return result;
}

void DlgMerge::on_tblData_cellClicked(int row, int column)
{
    QLOG_TRACE_FN();
    if ((column == 1) || (column == 2))
    {
        ui->tblData->item(row, 3)->setText(ui->tblData->item(row, column)->text());
    }
}
