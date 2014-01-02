#include "reportehorasdiaadia.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"

ReporteHorasDiaADia::ReporteHorasDiaADia(QObject *parent) :
    BaseReport(tr("Daily Hours Report"), "Daily Hours Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    QDate dateFrom = QDate::currentDate().addDays(-7);
    QDate dateTo = QDate::currentDate();
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, dateTo, -1, -1, -1,
                                                          true, true, true, false/*,
                                                          this*/);
    refreshReport();
}

ReporteHorasDiaADia::~ReporteHorasDiaADia()
{
    QLOG_TRACE_FN();
}

void ReporteHorasDiaADia::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Date")
         << tr("Total Hours");
}

void ReporteHorasDiaADia::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();

    foreach (ReportItemPtr rpt, reportData->items())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, rpt->date().value().toString(Qt::TextDate));
        item->setText(1, QString::number(rpt->hours()));
        tree.addTopLevelItem(item);
    }
}

void ReporteHorasDiaADia::filter()
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
    dlg.setDateEnabled(false);

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

void ReporteHorasDiaADia::refreshReport()
{
    QLOG_TRACE_FN();
    reportData->clear();
    reportData->refresh();
}
