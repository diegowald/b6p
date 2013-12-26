#include "reportehorasporempleado.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"


ReporteHorasPorEmpleado::ReporteHorasPorEmpleado(QObject *parent) :
    BaseReport(tr("Employee Hours Report"), "Employee Hours Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    dateFrom = QDate::currentDate().addDays(-7);
    dateTo = QDate::currentDate();
    reportData = boost::make_shared<ReportItemCollection>(dateFrom, dateTo, -1, -1, 0, this);
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
    dlg.setDateFrom(dateFrom);
    dlg.setDateTo(dateTo);
    if (dlg.exec() == QDialog::Accepted)
    {
        dateFrom = dlg.dateFrom();
        dateTo = dlg.dateTo();
        refreshReport();
    }
}

void ReporteHorasPorEmpleado::refreshReport()
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
