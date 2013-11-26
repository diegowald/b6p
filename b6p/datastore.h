#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "accesos.h"
#include "empleados.h"
#include "parametros.h"
#include "estimacionesdias.h"
#include "planificacionesdias.h"
#include "planificacionesdiassubsectores.h"
#include "sectores.h"
#include "subsectores.h"
#include "calendariopersonas.h"
#include "capacidadespersonasector.h"
#include "licenciasempleados.h"

class DataStore : public QObject
{
    Q_OBJECT
public:
    virtual ~DataStore();
    static DataStore* instance();
    void initialize(QObject *parent);

    AccesosPtr getAccesos();
    ParametrosPtr getParametros();
    EmpleadosPtr getEmpleados();
    EstimacionesDiasPtr getEstimacionesDias();
    PlanificacionesDiasPtr getPlanificacionesDias();
    PlanificacionesSubSectoresPtr getPlanificacionesSubSectores();
    SectoresPtr getSectores();
    SubSectoresPtr getSubSectores();
    CalendarioPersonasPtr getCalendarios();
    CapacidadesPersonaSectorPtr getCapacidades();
    LicenciasEmpleadosPtr getLicencias();
protected:
    explicit DataStore(QObject *parent = 0);
    
signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);

public slots:
    
protected:
    void establishConnections(ACollection *newMember);
private:

    AccesosPtr accessosPtr;
    ParametrosPtr parametrosPtr;
    EmpleadosPtr empleadosPtr;
    EstimacionesDiasPtr estimacionesDiasPtr;
    PlanificacionesDiasPtr planificacionesDiasPtr;
    PlanificacionesSubSectoresPtr planificacionesSubSectoresPtr;
    SectoresPtr sectoresPtr;
    SubSectoresPtr subSectoresPtr;
    CalendarioPersonasPtr calendariosPtr;
    CapacidadesPersonaSectorPtr capacidadesPtr;
    LicenciasEmpleadosPtr licenciasEmpleadosPtr;

    bool accesosCreated;
    bool parametrosCreated;
    bool empleadosCreated;
    bool estimacionesDiasCreated;
    bool planificacionesDiasCreated;
    bool planificacionesSubSectoresCreated;
    bool sectoresCreated;
    bool subSectoresCreated;
    bool calendariosCreated;
    bool capacidadesCreated;
    bool licenciasEmpleadosCreated;

    static DataStore* m_Instance;
};

#endif // DATASTORE_H
