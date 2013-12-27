#include "reportitem.h"
#include "QsLog.h"
#include "datastore.h"

ReportItem::ReportItem(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    references.clear();
}

ReportItem::~ReportItem()
{
    QLOG_TRACE_FN();
}

void ReportItem::addReference(PlanificacionSubSectorPtr reference)
{
    QLOG_TRACE_FN();
    references.push_back(reference);
}

NullableField<QDate> ReportItem::date()
{
    QLOG_TRACE_FN();
    NullableField<QDate> field;
    if (references.count() == 0)
        field.setNull();
    else
        field.setValue(references.at(0)->Dia());
    return field;
}

double ReportItem::hours()
{
    QLOG_TRACE_FN();
    double totalHours = 0;
    foreach (PlanificacionSubSectorPtr planificacion, references)
    {
        totalHours += planificacion->CantidadHoras();
    }
    return totalHours;
}

EmpleadoPtr ReportItem::employee()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return EmpleadoPtr();
    else
        return DataStore::instance()->getEmpleados()->getEmpleado(references.at(0)->IDEmpleado().value(), true);
}

SectorPtr ReportItem::sector()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return SectorPtr();
    else
        return DataStore::instance()->getSectores()->getSector(references.at(0)->IDSector().value());
}

SubSectorPtr ReportItem::subSector()
{
    QLOG_TRACE_FN();
    if (references.count() == 0)
        return SubSectorPtr();
    else
        return DataStore::instance()->getSubSectores()->getSubSector(references.at(0)->IDSubSector().value());
}
