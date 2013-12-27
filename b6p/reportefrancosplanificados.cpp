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

