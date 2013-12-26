#include "reportefrancosplanificados.h"
#include "QsLog.h"
#include "dlgdaterangefilter.h"

ReporteFrancosPlanificados::ReporteFrancosPlanificados(QObject *parent) :
    BaseReport(tr("Planned Rest Report"), "Planned Rest Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
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
/*
    foreach(EmpleadoPtr emp, *emps)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, emp->Apellido().value());
        item->setData(0, Qt::UserRole, emp->IDEmpleado().value());
        item->setText(1, emp->Nombre().value());
        item->setText(2, emp->Legajo().value());
        item->setText(3, emp->FechaIngreso().value().toString(Qt::TextDate));
        tree.insertTopLevelItem(0, item);
    }*/
}

void ReporteFrancosPlanificados::filter()
{
    QLOG_TRACE_FN();
    DlgDateRangeFilter dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        refreshReport();
    }
}

void ReporteFrancosPlanificados::refreshReport()
{
    QLOG_TRACE_FN();
}
