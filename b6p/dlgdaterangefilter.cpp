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
#include "dlgdaterangefilter.h"
#include "ui_dlgdaterangefilter.h"
#include "QsLog.h"


DlgDateRangeFilter::DlgDateRangeFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgDateRangeFilter)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    ui->dateFrom->setDate(QDate::currentDate().addDays(-7));
    ui->dateTo->setDate(QDate::currentDate());
}

DlgDateRangeFilter::~DlgDateRangeFilter()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgDateRangeFilter::setDateFrom(const QDate &from)
{
    QLOG_TRACE_FN();
    ui->dateFrom->setDate(from);
}


void DlgDateRangeFilter::setDateTo(const QDate &to)
{
    QLOG_TRACE_FN();
    ui->dateTo->setDate(to);
}

QDate DlgDateRangeFilter::dateFrom()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgDateRangeFilter::dateTo()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}
