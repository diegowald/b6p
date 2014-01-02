#ifndef REPORTEHORASPOREMPLEADO_H
#define REPORTEHORASPOREMPLEADO_H

#include <qobject.h>
#include <boost/shared_ptr.hpp>
#include "basereport.h"
#include "reportitemcollection.h"

class ReporteHorasPorEmpleado : public BaseReport
{
    Q_OBJECT
public:
    ReporteHorasPorEmpleado(QObject *parent = 0);
    virtual ~ReporteHorasPorEmpleado();

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);


    virtual void refreshReport();

public slots:
    virtual void filter();

private:
    ReportItemCollectionPtr reportData;
};

typedef boost::shared_ptr<ReporteHorasPorEmpleado> ReporteHorasPorEmpleadoPtr;

#endif // REPORTEHORASPOREMPLEADO_H
