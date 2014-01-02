#ifndef REPORTEHORASDIAADIA_H
#define REPORTEHORASDIAADIA_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "basereport.h"
#include "reportitemcollection.h"

class ReporteHorasDiaADia : public BaseReport
{
    Q_OBJECT
public:
    ReporteHorasDiaADia(QObject *parent = 0);
    virtual ~ReporteHorasDiaADia();

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);

    virtual void refreshReport();

public slots:
    virtual void filter();

private:
    ReportItemCollectionPtr reportData;
};

typedef boost::shared_ptr<ReporteHorasDiaADia> ReporteHorasDiaADiaPtr;
#endif // REPORTEHORASDIAADIA_H
