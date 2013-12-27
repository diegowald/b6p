#ifndef REPORTEHORASSECTORSUBSECTOR_H
#define REPORTEHORASSECTORSUBSECTOR_H

#include <QObject>

#include <boost/shared_ptr.hpp>
#include "basereport.h"
#include "reportitemcollection.h"

class ReporteHorasSectorSubSector : public BaseReport
{
    Q_OBJECT
public:
    ReporteHorasSectorSubSector(QObject *parent = 0);
    virtual ~ReporteHorasSectorSubSector();

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);


    virtual void refreshReport();

public slots:
    virtual void filter();

private:
    QDate dateFrom;
    QDate dateTo;
    ReportItemCollectionPtr reportData;
};

typedef boost::shared_ptr<ReporteHorasSectorSubSector> ReporteHorasSectorSubSectorPtr;

#endif // REPORTEHORASSECTORSUBSECTOR_H
