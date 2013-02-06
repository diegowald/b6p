#include "datastore.h"

DataStore* DataStore::m_Instance = NULL;

DataStore* DataStore::instance()
{
    if (m_Instance == NULL)
        m_Instance = new DataStore();
    return m_Instance;
}

void DataStore::initialize(QObject *parent)
{
    setParent(parent);
}

DataStore::DataStore(QObject *parent) :
    QObject(parent), parametrosCreated(false),
    empleadosCreated(false), estimacionesDiasCreated(false),
    planificacionesDiasCreated(false), planificacionesSubSectoresCreated(false),
    sectoresCreated(false), subSectoresCreated(false),
    calendariosCreated(false), capacidadesCreated(false)
{
}

DataStore::~DataStore()
{
}

void DataStore::establishConnections(ACollection* newMember)
{
    connect(newMember, SIGNAL(loaded(QString)), this, SIGNAL(loaded(QString)));
    connect(newMember, SIGNAL(loading(QString)), this, SIGNAL(loading(QString)));
    connect(newMember, SIGNAL(saved(QString)), this, SIGNAL(saved(QString)));
    connect(newMember, SIGNAL(saving(QString)), this, SIGNAL(saving(QString)));
    newMember->load();
}

ParametrosPtr DataStore::getParametros()
{
    if (!parametrosCreated)
    {
        parametrosPtr = ParametrosPtr(new Parametros(this));
        establishConnections(parametrosPtr.get());
        parametrosCreated = true;
    }
    return parametrosPtr;
}


EmpleadosPtr DataStore::getEmpleados()
{
    if (!empleadosCreated)
    {
        empleadosPtr = EmpleadosPtr(new Empleados(this));
        establishConnections(empleadosPtr.get());
        empleadosCreated = true;
    }
    return empleadosPtr;
}

EstimacionesDiasPtr DataStore::getEstimacionesDias()
{
    if (!estimacionesDiasCreated)
    {
        estimacionesDiasPtr = EstimacionesDiasPtr(new EstimacionesDias(this));
        establishConnections(estimacionesDiasPtr.get());
        estimacionesDiasCreated = true;
    }
    return estimacionesDiasPtr;
}

PlanificacionesDiasPtr DataStore::getPlanificacionesDias()
{
    if (!planificacionesDiasCreated)
    {
        planificacionesDiasPtr = PlanificacionesDiasPtr(new PlanificacionesDias(this));
        establishConnections(planificacionesDiasPtr.get());
        planificacionesDiasCreated = true;
    }
    return planificacionesDiasPtr;
}

PlanificacionesSubSectoresPtr DataStore::getPlanificacionesSubSectores()
{
    if (!planificacionesSubSectoresCreated)
    {
        planificacionesSubSectoresPtr = PlanificacionesSubSectoresPtr(new PlanificacionesDiasSubSectores(this));
        establishConnections(planificacionesSubSectoresPtr.get());
        planificacionesSubSectoresCreated = true;
    }
    return planificacionesSubSectoresPtr;

}

SectoresPtr DataStore::getSectores()
{
    if (!sectoresCreated)
    {
        sectoresPtr = SectoresPtr(new Sectores(this));
        establishConnections(sectoresPtr.get());
        sectoresCreated = true;
    }
    return sectoresPtr;
}

SubSectoresPtr DataStore::getSubSectores()
{
    if (!subSectoresCreated)
    {
        subSectoresPtr = SubSectoresPtr(new SubSectores(this));
        establishConnections(subSectoresPtr.get());
        subSectoresCreated = true;
    }
    return subSectoresPtr;
}


CalendarioPersonasPtr DataStore::getCalendarios()
{
    if (!calendariosCreated)
    {
        calendariosPtr = CalendarioPersonasPtr(new CalendarioPersonas(this));
        establishConnections(calendariosPtr.get());
        calendariosCreated = true;
    }
    return calendariosPtr;
}

CapacidadesPersonaSectorPtr DataStore::getCapacidades()
{
    if (!capacidadesCreated)
    {
        capacidadesPtr = CapacidadesPersonaSectorPtr(new CapacidadesPersonaSector(this));
        establishConnections(capacidadesPtr.get());
        capacidadesCreated = true;
    }
    return capacidadesPtr;
}
