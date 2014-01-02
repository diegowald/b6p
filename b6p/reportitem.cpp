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
#include "reportitem.h"
#include "QsLog.h"
#include "datastore.h"

ReportItem::ReportItem(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    references.clear();
}

ReportItem::~ReportItem()
{
    QLOG_TRACE_FN();
}

void ReportItem::addReference(PlanificacionSubSectorPtr reference)
{
    QLOG_TRACE_FN();
    references.push_back(reference);
}

NullableField<QDate> ReportItem::date()
{
    QLOG_TRACE_FN();
    NullableField<QDate> field;
    if (references.count() == 0)
        field.setNull();
    else
        field.setValue(references.at(0)->Dia());
    return field;
}

double ReportItem::hours()
{
    QLOG_TRACE_FN();
    double totalHours = 0;
    foreach (PlanificacionSubSectorPtr planificacion, references)
    {
        totalHours += planificacion->CantidadHoras();
    }
    return totalHours;
}

EmpleadoPtr ReportItem::employee()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return EmpleadoPtr();
    else
        return DataStore::instance()->getEmpleados()->getEmpleado(references.at(0)->IDEmpleado().value(), true);
}

SectorPtr ReportItem::sector()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return SectorPtr();
    else
        return DataStore::instance()->getSectores()->getSector(references.at(0)->IDSector().value());
}

SubSectorPtr ReportItem::subSector()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return SubSectorPtr();
    else
        return DataStore::instance()->getSubSectores()->getSubSector(references.at(0)->IDSubSector().value());
}
