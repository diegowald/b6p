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
#include "days.h"
#include <QObject>
#include <QsLog.h>


QString Days::Days2String(DAYS day)
{
    QLOG_TRACE_FN();
    switch (day)
    {
    case Sunday:
        return QObject::tr("Sunday");
        break;
    case Monday:
        return QObject::tr("Monday");
        break;
    case Tuesday:
        return QObject::tr("Tuesday");
        break;
    case Wednesday:
        return QObject::tr("Wednesday");
        break;
    case Thursday:
        return QObject::tr("Thursday");
        break;
    case Friday:
        return QObject::tr("Friday");
        break;
    case Saturday:
        return QObject::tr("Saturday");
        break;
    default:
        return "";
        break;
    }
}

DAYS Days::String2Day(QString day)
{
    QLOG_TRACE_FN();
    if (day == QObject::tr("Sunday"))
        return Sunday;
    else if(day == QObject::tr("Monday"))
        return Monday;
    else if(day == QObject::tr("Tuesday"))
        return Tuesday;
    else if(day == QObject::tr("Wednesday"))
        return Wednesday;
    else if(day == QObject::tr("Thursday"))
        return Thursday;
    else if(day == QObject::tr("Friday"))
        return Friday;
    else if(day == QObject::tr("Saturday"))
        return Saturday;
    else
        return Sunday;
}

DAYS Days::DayOfWeek2DAYS(int dayOfWeek)
{
    QLOG_TRACE_FN();
    switch(dayOfWeek)
    {
    case 1:
        return Monday;
        break;
    case 2:
        return Tuesday;
        break;
    case 3:
        return Wednesday;
        break;
    case 4:
        return Thursday;
        break;
    case 5:
        return Friday;
        break;
    case 6:
        return Saturday;
        break;
    case 7:
    default:
        return Sunday;
        break;
    }
}
