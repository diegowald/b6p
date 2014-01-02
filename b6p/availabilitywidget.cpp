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
#include "availabilitywidget.h"
#include "ui_availabilitywidget.h"
#include "datastore.h"
#include <QsLog.h>


AvailabilityWidget::AvailabilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailabilityWidget)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    connect(ui->timeFrom, SIGNAL(timeChanged(int)), ui->widget, SLOT(setStartAssignment(int)));
    connect(ui->timeTo, SIGNAL(timeChanged(int)),ui->widget, SLOT(setEndAssignment(int)));
    connect(ui->timeFrom2, SIGNAL(timeChanged(int)), ui->widget, SLOT(setStartAssignment2(int)));
    connect(ui->timeTo2, SIGNAL(timeChanged(int)), ui->widget, SLOT(setEndAssignment2(int)));

    ui->timeFrom->setbeyondThisDayVisibility(false);

    ui->timeFrom->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeTo->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));

    ui->timeFrom2->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeTo2->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));


    ui->widget->setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));

    ui->widget->setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
}

AvailabilityWidget::~AvailabilityWidget()
{
    QLOG_TRACE_FN();
    delete ui;
}

void AvailabilityWidget::setLabel(QString value)
{
    QLOG_TRACE_FN();
    ui->lblDay->setText(value);
}

void AvailabilityWidget::setFrom1(int value)
{
    QLOG_TRACE_FN();
    ui->timeFrom->setTime(value);
}

void AvailabilityWidget::setTo1(int value)
{
    QLOG_TRACE_FN();
    ui->timeTo->setTime(value);
}

void AvailabilityWidget::setFrom2(int value)
{
    QLOG_TRACE_FN();
    ui->timeFrom2->setTime(value);
}

void AvailabilityWidget::setTo2(int value)
{
    QLOG_TRACE_FN();
    ui->timeTo2->setTime(value);
}

void AvailabilityWidget::setDay(int day)
{
    QLOG_TRACE_FN();
    QString lbl;
    switch(day)
    {
    case 0:
        lbl = tr("Sunday");
        break;
    case 1:
        lbl = tr("Monday");
        break;
    case 2:
        lbl = tr("Tuesday");
        break;
    case 3:
        lbl = tr("Wednesday");
        break;
    case 4:
        lbl = tr("Thursday");
        break;
    case 5:
        lbl = tr("Friday");
        break;
    case 6:
    default:
        lbl = tr("Saturday");
        break;
    }
    ui->lblDay->setText(lbl);
    m_day = day;
}

int AvailabilityWidget::Day()
{
    QLOG_TRACE_FN();
    return m_day;
}

int AvailabilityWidget::FromTime1()
{
    QLOG_TRACE_FN();
    return ui->timeFrom->timeSeconds();
}

int AvailabilityWidget::ToTime1()
{
    QLOG_TRACE_FN();
    return ui->timeTo->timeSeconds();
}

int AvailabilityWidget::FromTime2()
{
    QLOG_TRACE_FN();
    return ui->timeFrom2->timeSeconds();
}

int AvailabilityWidget::ToTime2()
{
    QLOG_TRACE_FN();
    return ui->timeTo2->timeSeconds();
}

