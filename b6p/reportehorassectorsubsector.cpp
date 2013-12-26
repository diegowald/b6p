#include "reportehorassectorsubsector.h"
#include "QsLog.h"
#include "dlgquerybuilder.h"

ReporteHorasSectorSubSector::ReporteHorasSectorSubSector(QObject *parent) :
    BaseReport(tr("Hours By Sector and Subsector Report"), "Hours By Sector and Subsector Report", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
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
/*    EmpleadosLst emps = getAll(false);
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

void ReporteHorasSectorSubSector::filter()
{
    QLOG_TRACE_FN();
    DlgQueryBuilder dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        refreshReport();
    }
}


void ReporteHorasSectorSubSector::refreshReport()
{
    QLOG_TRACE_FN();
}
