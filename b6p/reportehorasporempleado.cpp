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
#include "reportehorasporempleado.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"


ReporteHorasPorEmpleado::ReporteHorasPorEmpleado(const QString &dbName, QObject *parent) :
    BaseReport(tr("Employee Hours Report"), "Employee Hours Report", false, ACollection::MERGE_KEEP_LOCAL, dbName, parent)
{
    QLOG_TRACE_FN();
    QDate dateFrom = QDate::currentDate().addDays(-7);
    reportData = ReportItemCollectionPtr::create(dateFrom, QDate::currentDate(), -1, -1, 0,
                                                          true, true, true, false/*,
                                                          this*/);
    refreshReport();
}

ReporteHorasPorEmpleado::~ReporteHorasPorEmpleado()
{
    QLOG_TRACE_FN();
}

void ReporteHorasPorEmpleado::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Employee")
         << tr("Total Hours");
}

void ReporteHorasPorEmpleado::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    foreach (ReportItemPtr rpt, reportData->items())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        if (rpt->employee() == EmpleadoPtr())
            item->setText(0, "");
        else
            item->setText(0, QString("%1, %2").arg(rpt->employee()->Apellido().value()).arg(rpt->employee()->Nombre().value()));
        item->setText(1, QString::number(rpt->hours()));
        tree.addTopLevelItem(item);
    }
}

void ReporteHorasPorEmpleado::filter()
{
    QLOG_TRACE_FN();
    DlgQueryBuilder dlg;
    dlg.setDateFrom(reportData->dateFrom());
    dlg.setDateTo(reportData->dateTo());
    dlg.setSummarizeDays(reportData->summarizeDays());
    dlg.setSummarizeEmployee(reportData->summarizeEmployee());
    dlg.setSummarizeSectors(reportData->summarizeSectors());
    dlg.setSummarizeSubsectors(reportData->summarizeEmployee());
    dlg.setIDSector(reportData->idSector());
    dlg.setIDSubSector(reportData->idSubSector());
    dlg.setIDEmployee(reportData->idEmpleado());
    dlg.setEmployeeEnabled(false);
    dlg.setSectorEnabled(false);
    dlg.setSubSectorEnabled(false);
    dlg.setDateEnabled(true);

    if (dlg.exec() == QDialog::Accepted)
    {
        reportData->setDateFrom(dlg.dateFrom());
        reportData->setDateTo(dlg.dateTo());
        reportData->SetSummarizeDays(dlg.summarizeDays());
        reportData->setSummarizeSectors(dlg.summarizeSectors());
        reportData->setSummarizeSubSectors(dlg.summarizeSubsectors());
        reportData->setSummarizeEmployee(dlg.summarizeEmployee());
        reportData->setIDSector(dlg.idSector());
        reportData->setIDSubSector(dlg.idSubSector());
        reportData->setIDEmpleado(dlg.idEmployee());
        refreshReport();
    }
}

void ReporteHorasPorEmpleado::refreshReport()
{
    QLOG_TRACE_FN();
    reportData->clear();
    reportData->refresh();
}

QSharedPointer<QList<QStringList> > ReporteHorasPorEmpleado::getAll()
{
    QLOG_TRACE_FN();
    QSharedPointer<QList<QStringList> > res = QSharedPointer<QList<QStringList>>::create();

    foreach (ReportItemPtr item, reportData->items())
    {
        QStringList r;
        if (item->employee() == EmpleadoPtr())
            r << "";
        else
            r << QString("%1, %2").arg(item->employee()->Apellido().value(), item->employee()->Nombre().value());
        r << QString::number(item->hours());
        res->push_back(r);
    }

    return res;
}
