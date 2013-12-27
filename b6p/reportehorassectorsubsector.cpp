#include "reportehorassectorsubsector.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"

ReporteHorasSectorSubSector::ReporteHorasSectorSubSector(QObject *parent) :
    BaseReport(tr("Hours By Sector and Subsector Report"), "Hours By Sector and Subsector Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    dateFrom = QDate::currentDate().addDays(-7);
    dateTo = QDate::currentDate();
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, dateTo, 0, 0, 0, this);
    refreshReport();
}

ReporteHorasSectorSubSector::~ReporteHorasSectorSubSector()
{
    QLOG_TRACE_FN();
}

void ReporteHorasSectorSubSector::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Date")
         << tr("Sector")
         << tr("Sub Sector")
         << tr("Total Hours");
}

void ReporteHorasSectorSubSector::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();

    foreach (ReportItemPtr rpt, reportData->items())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, rpt->date().value().toString(Qt::TextDate));
        item->setText(1, rpt->sector()->Nombre().value());
        if (rpt->subSector() == SubSectorPtr())
            item->setText(2, "");
        else
            item->setText(2, rpt->subSector()->Nombre().value());
        item->setText(3, QString::number(rpt->hours()));
        tree.addTopLevelItem(item);
    }
}

void ReporteHorasSectorSubSector::filter()
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

void ReporteHorasSectorSubSector::refreshReport()
{
    QLOG_TRACE_FN();
    reportData->clear();
    reportData->setDateFrom(dateFrom);
    reportData->setDateTo(dateTo);
    reportData->setIDEmpleado(0);
    reportData->setIDSector(-1);
    reportData->setIDSubSector(-1);
    reportData->refresh();
}
