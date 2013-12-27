#ifndef REPORTEFRANCOSPLANIFICADOS_H
#define REPORTEFRANCOSPLANIFICADOS_H

#include <boost/shared_ptr.hpp>
#include "basereport.h"
#include <QObject>
#include "licenciaempleado.h"

class ReporteFrancosPlanificados : public BaseReport
{
    Q_OBJECT
public:
    ReporteFrancosPlanificados(QObject *parent = 0);
    virtual ~ReporteFrancosPlanificados();

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);

    virtual void refreshReport();
public slots:
    virtual void filter();

private:
    QDate dateFrom;
    QDate dateTo;
    LicenciasEmpleadosLst reportData;
};

typedef boost::shared_ptr<ReporteFrancosPlanificados> ReporteFrancosPlanificadosPtr;


#endif // REPORTEFRANCOSPLANIFICADOS_H
