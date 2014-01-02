#include "reportehorasporempleado.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"


ReporteHorasPorEmpleado::ReporteHorasPorEmpleado(QObject *parent) :
    BaseReport(tr("Employee Hours Report"), "Employee Hours Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    QDate dateFrom = QDate::currentDate().addDays(-7);
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, QDate::currentDate(), -1, -1, 0,
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
    list << tr("Date")
         << tr("Employee")
         << tr("Total Hours");
}

void ReporteHorasPorEmpleado::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    foreach (ReportItemPtr rpt, reportData->items())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, rpt->date().value().toString(Qt::TextDate));
        if (rpt->employee() == EmpleadoPtr())
            item->setText(1, "");
        else
            item->setText(1, QString("%1, %2").arg(rpt->employee()->Apellido().value()).arg(rpt->employee()->Nombre().value()));
        item->setText(2, QString::number(rpt->hours()));
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
