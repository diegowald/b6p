#include "reportehorassectorsubsector.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"

ReporteHorasSectorSubSector::ReporteHorasSectorSubSector(QObject *parent) :
    BaseReport(tr("Hours By Sector and Subsector Report"), "Hours By Sector and Subsector Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    QDate dateFrom = QDate::currentDate().addDays(-7);
    QDate dateTo = QDate::currentDate();
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, dateTo, 0, 0, 0,
                                                          true, true, true, false/*,
                                                          this*/);
    refreshReport();
}

ReporteHorasSectorSubSector::~ReporteHorasSectorSubSector()
{
    QLOG_TRACE_FN();
}

void ReporteHorasSectorSubSector::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    if (reportData->summarizeDays())
        list << tr("Date");
    if (reportData->summarizeSectors())
        list << tr("Sector");
    if (reportData->summarizeSubSectors())
        list << tr("Sub Sector");
    list << tr("Total Hours");
}

void ReporteHorasSectorSubSector::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();

    foreach (ReportItemPtr rpt, reportData->items())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        int column = 0;
        if (reportData->summarizeDays())
        {
            item->setText(column, rpt->date().value().toString(Qt::TextDate));
            column++;
        }
        if (reportData->summarizeSectors())
        {
            item->setText(column, rpt->sector()->Nombre().value());
            column++;
        }
        if (reportData->summarizeSubSectors())
        {
            if (rpt->subSector() == SubSectorPtr())
                item->setText(column, "");
            else
                item->setText(column, rpt->subSector()->Nombre().value());
            column++;
        }
        item->setText(column, QString::number(rpt->hours()));
        tree.addTopLevelItem(item);
    }
}

void ReporteHorasSectorSubSector::filter()
{
    QLOG_TRACE_FN();
    DlgQueryBuilder dlg;
    dlg.setDateFrom(reportData->dateFrom());
    dlg.setDateTo(reportData->dateTo());
    dlg.setSummarizeDays(reportData->summarizeDays());
    dlg.setSummarizeEmployee(reportData->summarizeEmployee());
    dlg.setSummarizeSectors(reportData->summarizeSectors());
    dlg.setSummarizeSubsectors(reportData->summarizeSubSectors());
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

void ReporteHorasSectorSubSector::refreshReport()
{
    QLOG_TRACE_FN();
    reportData->clear();
    reportData->refresh();
}
