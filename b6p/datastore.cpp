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
    QObject(parent)
{
}

DataStore::~DataStore()
{
}

void DataStore::addElement(QString name, ACollection* newMember)
{
    m_DataCollection[name] = boost::shared_ptr<ACollection>(newMember);
    connect(newMember, SIGNAL(loaded(QString)), this, SIGNAL(loaded(QString)));
    connect(newMember, SIGNAL(loading(QString)), this, SIGNAL(loading(QString)));
    connect(newMember, SIGNAL(saved(QString)), this, SIGNAL(saved(QString)));
    connect(newMember, SIGNAL(saving(QString)), this, SIGNAL(saving(QString)));
}

ParametrosPtr DataStore::getParametros()
{
    QString key = "Parametros";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new Parametros(this));
    return ParametrosPtr((Parametros*)m_DataCollection[key].get());
}


EmpleadosPtr DataStore::getEmpleados()
{
    QString key = "Empleados";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new Empleados(this));
    return EmpleadosPtr((Empleados*)m_DataCollection[key].get());
}

EstimacionesDiasPtr DataStore::getEstimacionesDias()
{
    QString key = "Estimaciones Dias";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new EstimacionesDias(this));
    return EstimacionesDiasPtr((EstimacionesDias*)m_DataCollection[key].get());
}

PlanificacionesDiasPtr DataStore::getPlanificacionesDias()
{
    QString key = "Planificaciones Dias";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new PlanificacionesDias(this));
    return PlanificacionesDiasPtr((PlanificacionesDias*)m_DataCollection[key].get());
}

PlanificacionesSubSectoresPtr DataStore::getPlanificacionesSubSectores()
{
    QString key = "Planificaciones SubSectores";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new PlanificacionesDiasSubSectores(this));
    return PlanificacionesSubSectoresPtr((PlanificacionesDiasSubSectores*)m_DataCollection[key].get());
}

SectoresPtr DataStore::getSectores()
{
    QString key = "Sectores";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new Sectores(this));
    return SectoresPtr((Sectores*)m_DataCollection[key].get());
}

SubSectoresPtr DataStore::getSubSectores()
{
    QString key = "SubSectores";
    if (m_DataCollection.find(key) == m_DataCollection.end())
        addElement(key, new SubSectores(this));
    return SubSectoresPtr((SubSectores*)m_DataCollection[key].get());
}
