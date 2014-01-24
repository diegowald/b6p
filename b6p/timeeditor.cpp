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
#include "timeeditor.h"
#include "ui_timeeditor.h"
#include <QDebug>
#include <QIntValidator>

#include <QsLog.h>


TimeEditor::TimeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeEditor)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    setDefaultValues();
}

TimeEditor::~TimeEditor()
{
    QLOG_TRACE_FN();
    delete ui;
}

void TimeEditor::onValueChanged(QLineEdit *, int)
{
    QLOG_TRACE_FN();
    if (checkTime(ui->lineTime->text()))
    {
        currentTime = HHMMSS2Seconds(ui->lineTime->text(), true);
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::black);
        ui->lineTime->setPalette(*palette);
        emit timeChanged(currentTime);
    }
    else
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        ui->lineTime->setPalette(*palette);
        emit IncorrectTime(tr("Time is incorrect"));
    }
}
void TimeEditor::setTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    setTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setTime(int seconds)
{
    QLOG_TRACE_FN();
    int secondsOnSameDay = seconds % 86400;
    ui->chkBeyondThisDay->setChecked(seconds != secondsOnSameDay);
    if (checkTime(seconds))
    {
        currentTime = seconds;
        previouslySelectedHour = getHours(secondsOnSameDay);
        QString aux = "%1:%2";
        aux = aux.arg(QString::number(previouslySelectedHour), 2, '0').arg(QString::number(getMinutes(secondsOnSameDay)), 2, '0');
        ui->lineTime->setText(aux);
        emit timeChanged(currentTime);
    }
}

int TimeEditor::timeSeconds()
{
    QLOG_TRACE_FN();
    return currentTime;
}

void TimeEditor::setMinTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    setMinTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMinTime(int seconds)
{
    QLOG_TRACE_FN();
    minValue = seconds;
}

int TimeEditor::minTimeSeconds()
{
    QLOG_TRACE_FN();
    return minValue;
}

void TimeEditor::setMaxTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    setMaxTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMaxTime(int seconds)
{
    QLOG_TRACE_FN();
    maxValue = seconds;
    maxTimeBeyondThisDay = (maxValue > 86400);
}

int TimeEditor::maxTimeSeconds()
{
    QLOG_TRACE_FN();
    return maxValue;
}

void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)
{
    QLOG_TRACE_FN();
    setMinTime(hh1, mm1, ss1);
    setMaxTime(hh2, mm2, ss2);
}

void TimeEditor::setValidRange(int secondsFrom, int secondsTo)
{
    QLOG_TRACE_FN();
    setMinTime(secondsFrom);
    setMaxTime(secondsTo);
}

int TimeEditor::HHMMSS2Seconds(const QString &time, bool canBeBeyondThisDay)
{
    QLOG_TRACE_FN();
    QString aux = time;
    aux = aux.replace(".", ":");
    QStringList numbers = aux.split(":");
    int hours = numbers.at(0).toInt();
    int minutes = numbers.at(1).toInt();
    return HHMMSS2Seconds(hours, minutes, 0, canBeBeyondThisDay);
}

int TimeEditor::HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay)
{
    QLOG_TRACE_FN();
    int seconds = ss;
    seconds += mm * 60;
    seconds += hh * 3600;
    if (canBeBeyondThisDay && ui->chkBeyondThisDay->isChecked())
        seconds += 86400;
    return seconds;
}

bool TimeEditor::checkTime(const QString &time)
{
    QLOG_TRACE_FN();
    QString aux = time;
    aux = aux.replace(".", ":");
    QStringList numbers = aux.split(":");
    if (numbers.count() != 2)
    {
        return false;
    }

    int hours = numbers.at(0).toInt();
    int minutes = numbers.at(1).toInt();
    return checkTime(hours, minutes, 0);
}

bool TimeEditor::checkTime(int seconds)
{
    QLOG_TRACE_FN();
    qDebug() << "minValue: " << minValue;
    qDebug() << "seconds: " << seconds;
    qDebug() << "maxValue: " << maxValue;
    return (minValue <= seconds) && (seconds <= maxValue);
}

bool TimeEditor::checkTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    return checkTime(HHMMSS2Seconds(hh, mm, ss, true));
}

int TimeEditor::getHours(int seconds)
{
    QLOG_TRACE_FN();
    return seconds / 3600;
}

int TimeEditor::getMinutes(int seconds)
{
    QLOG_TRACE_FN();
    int hh = getHours(seconds);
    return (seconds - hh * 3600) / 60;
}

int TimeEditor::getSeconds(int seconds)
{
    QLOG_TRACE_FN();
    return seconds % 60;
}

void TimeEditor::setDefaultValues()
{
    QLOG_TRACE_FN();
    currentTime = 0;
    previouslySelectedHour = 0;
    minValue = 0;
    maxValue = 24 * 3600;
    ui->chkBeyondThisDay->setChecked(false);
    maxTimeBeyondThisDay = false;
    QRegExp regExp("^([0-9]|0[0-9]|1[0-9]|2[0-3])[:.][0-5][0-9]$");
    QRegExpValidator *v = new QRegExpValidator(regExp, this);
    ui->lineTime->setValidator(v);
}

bool TimeEditor::isBeyondThisDay() const
{
    QLOG_TRACE_FN();
    return ui->chkBeyondThisDay->isChecked();
}

void TimeEditor::setbeyondThisDayVisibility(bool value)
{
    QLOG_TRACE_FN();
    ui->chkBeyondThisDay->setVisible(value);
}


bool TimeEditor::beyondThisDayVisibility()
{
    QLOG_TRACE_FN();
    return ui->chkBeyondThisDay->isVisible();
}

void TimeEditor::on_chkBeyondThisDay_clicked(bool)
{
    QLOG_TRACE_FN();
    onValueChanged(NULL, 0);
}

void TimeEditor::on_lineTime_textChanged(const QString &arg1)
{
    QLOG_TRACE_FN();
    onValueChanged(ui->lineTime, arg1.toInt());
}
