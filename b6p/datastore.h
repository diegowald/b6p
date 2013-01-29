#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "empleados.h"
#include "parametros.h"
#include "estimacionesdias.h"
#include "planificacionesdias.h"
#include "planificacionesdiassubsectores.h"
#include "sectores.h"
#include "subsectores.h"
#include "calendariopersonas.h"
#include "capacidadespersonasector.h"

class DataStore : public QObject
{
    Q_OBJECT
public:
    virtual ~DataStore();
    static DataStore* instance();
    void initialize(QObject *parent);

    ParametrosPtr getParametros();
    EmpleadosPtr getEmpleados();
    EstimacionesDiasPtr getEstimacionesDias();
    PlanificacionesDiasPtr getPlanificacionesDias();
    PlanificacionesSubSectoresPtr getPlanificacionesSubSectores();
    SectoresPtr getSectores();
    SubSectoresPtr getSubSectores();
    CalendarioPersonasPtr getCalendarios();
    CapacidadesPersonaSectorPtr getCapacidades();

protected:
    explicit DataStore(QObject *parent = 0);
    
signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);

public slots:
    
protected:
    void addElement(QString name, ACollection *newMember);
private:
    QMap<QString, boost::shared_ptr<ACollection> > m_DataCollection;
    static DataStore* m_Instance;
};

#endif // DATASTORE_H
