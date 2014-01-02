#ifndef REPORTITEMCOLLECTION_H
#define REPORTITEMCOLLECTION_H

#include <QObject>
#include "reportitem.h"
#include "planificacionsubsector.h"


class ReportItemCollection : public QObject
{
    Q_OBJECT
public:
    explicit ReportItemCollection(const QDate& dateFrom, const QDate& dateTo,
                                  int IDSectorFilter, int IDSubSectorFilter, int IDEmpleadoFilter,
                                  bool summarizeDays, bool summarizeSectors, bool summarizeSubSectors, bool summarizeEmployee,
                                  QObject *parent = 0);

    virtual ~ReportItemCollection();
    void addPlanificacionSubSector(PlanificacionSubSectorPtr planificacion);
    void addPlanificacionSubSector(PlanificacionSubSectorLst ListPlanificacion);

    void clear();
    void setDateFrom(const QDate& dateFrom);
    void setDateTo(const QDate& dateTo);
    void setIDEmpleado(int idEmpleado);
    void setIDSector(int idSector);
    void setIDSubSector(int idSubSector);

    void SetSummarizeDays(bool value);
    void setSummarizeSectors(bool value);
    void setSummarizeSubSectors(bool value);
    void setSummarizeEmployee(bool value);

    QDate dateFrom() const;
    QDate dateTo() const;
    int idEmpleado() const;
    int idSector() const;
    int idSubSector() const;

    bool summarizeDays() const;
    bool summarizeSectors() const;
    bool summarizeSubSectors() const;
    bool summarizeEmployee() const;


    void refresh();

    QList<ReportItemPtr> items();

private:
    QString createIndex(PlanificacionSubSectorPtr planificacion);
    bool isValid(PlanificacionSubSectorPtr planificacion);
    bool doSummarizeDays;
    bool doSummarizeSectors;
    bool doSummarizeSubsectors;
    bool doSummarizeEmployee;

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
