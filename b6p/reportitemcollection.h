#ifndef REPORTITEMCOLLECTION_H
#define REPORTITEMCOLLECTION_H

#include <QObject>
#include "reportitem.h"
#include "planificacionsubsector.h"


class ReportItemCollection : public QObject
{
    Q_OBJECT
public:
    explicit ReportItemCollection(const QDate& dateFrom, const QDate& dateTo, int IDSectorFilter, int IDSubSectorFilter, int IDEmpleadoFilter,  QObject *parent = 0);
    virtual ~ReportItemCollection();
    void addPlanificacionSubSector(PlanificacionSubSectorPtr planificacion);
    void addPlanificacionSubSector(PlanificacionSubSectorLst ListPlanificacion);

    void clear();
    void setDateFrom(const QDate& dateFrom);
    void setDateTo(const QDate& dateTo);
    void setIDEmpleado(int idEmpleado);
    void setIDSector(int idSector);
    void setIDSubSector(int idSubSector);
    void refresh();

    QList<ReportItemPtr> items();

private:
    QString createIndex(PlanificacionSubSectorPtr planificacion);
    bool isValid(PlanificacionSubSectorPtr planificacion);

signals:

public slots:

private:
    QMap<QString, ReportItemPtr> reportItems;
    int idSectorFilter;
    int idSubSectorFilter;
    int idEmpleadoFilter;
    QDate dateFromFilter;
    QDate dateToFilter;
};

typedef boost::shared_ptr<ReportItemCollection> ReportItemCollectionPtr;

#endif // REPORTITEMCOLLECTION_H
