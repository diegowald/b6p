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
#include "reportefrancosplanificados.h"
#include "QsLog.h"
#include "dlgdaterangefilter.h"
#include "datastore.h"

ReporteFrancosPlanificados::ReporteFrancosPlanificados(QObject *parent) :
    BaseReport(tr("Planned Rest Report"), "Planned Rest Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    dateFrom = QDate::currentDate().addDays(-7);
    dateTo = QDate::currentDate();
    refreshReport();
}

ReporteFrancosPlanificados::~ReporteFrancosPlanificados()
{
    QLOG_TRACE_FN();
}

void ReporteFrancosPlanificados::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Employee")
         << tr("From")
         << tr("To")
         << tr("Type")
         << tr("Notes");
}

void ReporteFrancosPlanificados::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();

    foreach (LicenciaEmpleadoPtr licencia, *reportData)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        EmpleadoPtr empleado  = DataStore::instance()->getEmpleados()->getEmpleado(licencia->IDEmpleado().value(), true);
        item->setText(0, empleado->Apellido().value() + ", " + empleado->Nombre().value());
        item->setText(1, licencia->FechaDesde().value().toString(Qt::TextDate));
        item->setText(2, licencia->FechaHasta().value().toString(Qt::TextDate));
        item->setText(3, licencia->TipoLicencia().value());
        item->setText(4, licencia->Descripcion().value());
        tree.addTopLevelItem(item);
    }
}

void ReporteFrancosPlanificados::filter()
{
    QLOG_TRACE_FN();
    DlgDateRangeFilter dlg;
    dlg.setDateFrom(dateFrom);
    dlg.setDateTo(dateTo);
    if (dlg.exec() == QDialog::Accepted)
    {
        dateFrom = dlg.dateFrom();
        dateTo = dlg.dateTo();
        refreshReport();
    }
}

void ReporteFrancosPlanificados::refreshReport()
{
    QLOG_TRACE_FN();
    reportData = DataStore::instance()->getLicencias()->getAllLicencias(dateFrom, dateTo);
}

