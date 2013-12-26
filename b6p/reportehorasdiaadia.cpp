#include "reportehorasdiaadia.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"

ReporteHorasDiaADia::ReporteHorasDiaADia(QObject *parent) :
    BaseReport(tr("Daily Hours Report"), "Daily Hours Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    dateFrom = QDate::currentDate().addDays(-7);
    dateTo = QDate::currentDate();
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, dateTo, -1, -1, -1, this);
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
    dlg.setDateFrom(dateFrom);
    dlg.setDateTo(dateTo);
    if (dlg.exec() == QDialog::Accepted)
    {
        dateFrom = dlg.dateFrom();
        dateTo = dlg.dateTo();
        refreshReport();
    }
}

void ReporteHorasDiaADia::refreshReport()
{
    QLOG_TRACE_FN();
    reportData->clear();
    reportData->setDateFrom(dateFrom);
    reportData->setDateTo(dateTo);
    reportData->setIDEmpleado(-1);
    reportData->setIDSector(-1);
    reportData->setIDSubSector(-1);
    reportData->refresh();
}
