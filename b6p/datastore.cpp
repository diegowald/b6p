#include "datastore.h"
#include <QsLog.h>


DataStore* DataStore::m_Instance = NULL;

DataStore* DataStore::instance()
{
    QLOG_TRACE_FN();
    if (m_Instance == NULL)
        m_Instance = new DataStore();
    return m_Instance;
}

void DataStore::initialize(QObject *parent)
{
    QLOG_TRACE_FN();
    setParent(parent);
}


DataStore::DataStore(QObject *parent) :
    QObject(parent), parametrosCreated(false),
    empleadosCreated(false), estimacionesDiasCreated(false),
    planificacionesDiasCreated(false), planificacionesSubSectoresCreated(false),
    sectoresCreated(false), subSectoresCreated(false),
    calendariosCreated(false), capacidadesCreated(false)
{
    QLOG_TRACE_FN();
}

DataStore::~DataStore()
{
    QLOG_TRACE_FN();
}

void DataStore::establishConnections(ACollection* newMember)
{
    QLOG_TRACE_FN();
    connect(newMember, SIGNAL(loaded(QString)), this, SIGNAL(loaded(QString)));
    connect(newMember, SIGNAL(loading(QString)), this, SIGNAL(loading(QString)));
    connect(newMember, SIGNAL(saved(QString)), this, SIGNAL(saved(QString)));
    connect(newMember, SIGNAL(saving(QString)), this, SIGNAL(saving(QString)));
    newMember->load();
}

AccesosPtr DataStore::getAccesos()
{
    QLOG_TRACE_FN();
    if (!accesosCreated)
    {
        accessosPtr = boost::make_shared<Accesos>(this);
        establishConnections(accessosPtr.get());
        accesosCreated = true;
    }
    return accessosPtr;
}


ParametrosPtr DataStore::getParametros()
{
    QLOG_TRACE_FN();
    if (!parametrosCreated)
    {
        parametrosPtr = boost::make_shared<Parametros>(this);
        establishConnections(parametrosPtr.get());
        parametrosCreated = true;
    }
    return parametrosPtr;
}


EmpleadosPtr DataStore::getEmpleados()
{
    QLOG_TRACE_FN();
    if (!empleadosCreated)
    {
        empleadosPtr = boost::make_shared<Empleados>(this);
        establishConnections(empleadosPtr.get());
        empleadosCreated = true;
    }
    return empleadosPtr;
}

EstimacionesDiasPtr DataStore::getEstimacionesDias()
{
    QLOG_TRACE_FN();
    if (!estimacionesDiasCreated)
    {
        estimacionesDiasPtr = boost::make_shared<EstimacionesDias>(this);
        establishConnections(estimacionesDiasPtr.get());
        estimacionesDiasCreated = true;
    }
    return estimacionesDiasPtr;
}

PlanificacionesDiasPtr DataStore::getPlanificacionesDias()
{
    QLOG_TRACE_FN();
    if (!planificacionesDiasCreated)
    {
        planificacionesDiasPtr = boost::make_shared<PlanificacionesDias>(this);
        establishConnections(planificacionesDiasPtr.get());
        planificacionesDiasCreated = true;
    }
    return planificacionesDiasPtr;
}

PlanificacionesSubSectoresPtr DataStore::getPlanificacionesSubSectores()
{
    QLOG_TRACE_FN();
    if (!planificacionesSubSectoresCreated)
    {
        planificacionesSubSectoresPtr = boost::make_shared<PlanificacionesDiasSubSectores>(this);
        establishConnections(planificacionesSubSectoresPtr.get());
        planificacionesSubSectoresCreated = true;
    }
    return planificacionesSubSectoresPtr;

}

SectoresPtr DataStore::getSectores()
{
    QLOG_TRACE_FN();
    if (!sectoresCreated)
    {
        sectoresPtr = boost::make_shared<Sectores>(this);
        establishConnections(sectoresPtr.get());
        sectoresCreated = true;
    }
    return sectoresPtr;
}

SubSectoresPtr DataStore::getSubSectores()
{
    QLOG_TRACE_FN();
    if (!subSectoresCreated)
    {
        subSectoresPtr = boost::make_shared<SubSectores>(this);
        establishConnections(subSectoresPtr.get());
        subSectoresCreated = true;
    }
    return subSectoresPtr;
}


CalendarioPersonasPtr DataStore::getCalendarios()
{
    QLOG_TRACE_FN();
    if (!calendariosCreated)
    {
        calendariosPtr = boost::make_shared<CalendarioPersonas>(this);
        establishConnections(calendariosPtr.get());
        calendariosCreated = true;
    }
    return calendariosPtr;
}

CapacidadesPersonaSectorPtr DataStore::getCapacidades()
{
    QLOG_TRACE_FN();
    if (!capacidadesCreated)
    {
        capacidadesPtr = boost::make_shared<CapacidadesPersonaSector>(this);
        establishConnections(capacidadesPtr.get());
        capacidadesCreated = true;
    }
    return capacidadesPtr;
}
