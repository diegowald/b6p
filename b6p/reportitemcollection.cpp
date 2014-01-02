#include "reportitemcollection.h"
#include "QsLog.h"
#include "datastore.h"
// ID == -1 no tener en cuenta
// ID == 0, tener en cuenta pero no eliminar
// ID > 0, filtrar

ReportItemCollection::ReportItemCollection(const QDate& dateFrom, const QDate& dateTo,
                                           int idSector, int idSubSector, int idEmpleado,
                                           bool summarizeDays,
                                           bool summarizeSectors,
                                           bool summarizeSubSectors,
                                           bool summarizeEmployee,
                                           QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();\
    dateFromFilter = dateFrom;
    dateToFilter = dateTo;
    idSectorFilter = idSector;
    idSubSectorFilter = idSubSector;
    idEmpleadoFilter = idEmpleado;
    doSummarizeDays = summarizeDays;
    doSummarizeSectors = summarizeSectors;
    doSummarizeSubsectors = summarizeSubSectors;
    doSummarizeEmployee = summarizeEmployee;
    reportItems.clear();
}

ReportItemCollection::~ReportItemCollection()
{
    QLOG_TRACE_FN();
}

void ReportItemCollection::addPlanificacionSubSector(PlanificacionSubSectorPtr planificacion)
{
    QLOG_TRACE_FN();
    if (isValid(planificacion))
    {
        QString index = createIndex(planificacion);
        ReportItemPtr item;
        if (reportItems.find(index) == reportItems.end())
        {
            item = boost::make_shared<ReportItem>(this);
        }
        else
        {
            item = reportItems[index];
        }
        item->addReference(planificacion);
        reportItems[index] = item;
    }
}

void ReportItemCollection::addPlanificacionSubSector(PlanificacionSubSectorLst ListPlanificacion)
{
    QLOG_TRACE_FN();
    foreach (PlanificacionSubSectorPtr planificacion, *ListPlanificacion)
    {
        addPlanificacionSubSector(planificacion);
    }
}

QString ReportItemCollection::createIndex(PlanificacionSubSectorPtr planificacion)
{
    QLOG_TRACE_FN();
    QString index;
    if (doSummarizeDays)
        index = planificacion->Dia().value().toString(Qt::TextDate);
    if (doSummarizeSectors)
    {
        if (idSectorFilter != -1)
            index += "," + QString::number(planificacion->IDSector().value());
    }

    if (doSummarizeSubsectors)
    {
        if (idSubSectorFilter != -1)
            index += "," + QString::number(planificacion->IDSubSector().value());
    }

    if (doSummarizeEmployee)
    {
        if (idEmpleadoFilter != -1)
            index += "," + QString::number(planificacion->IDEmpleado().value());
    }

    return index;
}

bool ReportItemCollection::isValid(PlanificacionSubSectorPtr planificacion)
{
    if (idSectorFilter > 0)
    {
        if (planificacion->IDSector().value() != idSectorFilter)
            return false;
    }

    if (idSubSectorFilter > 0)
    {
        if (planificacion->IDSubSector().value() != idSubSectorFilter)
            return false;
    }

    if (idEmpleadoFilter > 0)
    {
        if (planificacion->IDEmpleado().value() != idEmpleadoFilter)
            return false;
    }

    return true;
}

void ReportItemCollection::clear()
{
    QLOG_TRACE_FN();
    reportItems.clear();
}

void ReportItemCollection::setDateFrom(const QDate& dateFrom)
{
    QLOG_TRACE_FN();
    dateFromFilter = dateFrom;
}

void ReportItemCollection::setDateTo(const QDate& dateTo)
{
    QLOG_TRACE_FN();
    dateToFilter = dateTo;
}

void ReportItemCollection::setIDEmpleado(int idEmpleado)
{
    QLOG_TRACE_FN();
    this->idEmpleadoFilter = idEmpleado;
}

void ReportItemCollection::setIDSector(int idSector)
{
    QLOG_TRACE_FN();
    this->idSectorFilter = idSector;
}

void ReportItemCollection::setIDSubSector(int idSubSector)
{
    QLOG_TRACE_FN();
    this->idSubSectorFilter = idSubSector;
}

void ReportItemCollection::refresh()
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst planificaciones = DataStore::instance()->getPlanificacionesSubSectores()->getAll(dateFromFilter, dateToFilter);
    addPlanificacionSubSector(planificaciones);
}

QList<ReportItemPtr> ReportItemCollection::items()
{
    return reportItems.values();
}

void ReportItemCollection::SetSummarizeDays(bool value)
{
    QLOG_TRACE_FN();
    doSummarizeDays = value;
}

void ReportItemCollection::setSummarizeSectors(bool value)
{
    QLOG_TRACE_FN();
    doSummarizeSectors = value;
}

void ReportItemCollection::setSummarizeSubSectors(bool value)
{
    QLOG_TRACE_FN();
    doSummarizeSubsectors = value;
}

void ReportItemCollection::setSummarizeEmployee(bool value)
{
    QLOG_TRACE_FN();
    doSummarizeEmployee = value;
}

QDate ReportItemCollection::dateFrom() const
{
    QLOG_TRACE_FN();
    return dateFromFilter;
}

QDate ReportItemCollection::dateTo() const
{
    QLOG_TRACE_FN();
    return dateToFilter;
}

int ReportItemCollection::idEmpleado() const
{
    QLOG_TRACE_FN();
    return idEmpleadoFilter;
}

int ReportItemCollection::idSector() const
{
    QLOG_TRACE_FN();
    return idSectorFilter;
}

int ReportItemCollection::idSubSector() const
{
    QLOG_TRACE_FN();
    return idSubSectorFilter;
}

bool ReportItemCollection::summarizeDays() const
{
    QLOG_TRACE_FN();
    return doSummarizeDays;
}

bool ReportItemCollection::summarizeSectors() const
{
    QLOG_TRACE_FN();
    return doSummarizeSectors;
}

bool ReportItemCollection::summarizeSubSectors() const
{
    QLOG_TRACE_FN();
    return doSummarizeSubsectors;
}

bool ReportItemCollection::summarizeEmployee() const
{
    QLOG_TRACE_FN();
    return doSummarizeEmployee;
}


