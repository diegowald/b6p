#include "SincroManager.h"
#include <QtSql>
#include <QMessageBox>
#include "datastore.h"

SincroManager::SincroManager(QObject *parent) :
    QObject(parent)
{
    m_SQL = boost::make_shared<SQLHandler>(
                DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, "127.0.0.1"),
                DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, "b6p"),
                DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, "root"),
                DataStore::instance()->getParametros()->getValue(Parametros::PASSWORD, "mic1492"));

    /*m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getSectores(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getSubSectores(), m_SQL, this));*/
    //m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getEmpleados(), m_SQL, this));
    /*m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getCalendarios(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getCapacidades(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getEstimacionesDias(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getPlanificacionesDias(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getPlanificacionesSubSectores(), m_SQL, this));*/

    establishConnections();


    /*if (!db.open())
        QMessageBox::critical(0, QObject::tr("Database Error"),
                      db.lastError().text());

    db.close();*/
}

void SincroManager::runSincro()
{
    emit startingSynchro();
    obtenerFechaUltimaSincronizacion();
    obtenerActualizacionesDeBaseCentral();

    enviarDatosADBCentral();
    grabarFechaUltimaSincronizacion();
    emit SynchroEnded();
    /**
 * Secuencia
 * -> Obtengo la fecha/hora de la ultima sincronizacion desde la base local
 * -> Obtengo actualizaciones desde la DB Central desde la ultima sincronizacion
 * -> Aplico los cambios basados en esas actualizaciones
 * -> Verifico que lo que voy a enviar es consistente.
 * -> Si no es consistente corrijo los problemas
 * -> Envio mis datos.
 * -> Aplico esos cambios en el servidor central
 * -> Obtengo la fecha/hora actual desde el servidor y
 * -> Guardo en la db local la fecha de la ultima actualizacion
 */
}


void SincroManager::obtenerFechaUltimaSincronizacion()
{
    m_FechaUltimaSincronizacion =
            DataStore::instance()->getParametros()->getValue(
                Parametros::LAST_SYNCHRO, "2000-01-01 00:00:00");
}

void SincroManager::obtenerActualizacionesDeBaseCentral()
{
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        db->getDataFromDB(m_FechaUltimaSincronizacion);
        db->applyChanges();
        db->checkConsistency();
    }
}

void SincroManager::enviarDatosADBCentral()
{
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        db->sendData();
    }
}


void SincroManager::grabarFechaUltimaSincronizacion()
{
    QString UltimaSincro;
    QString query("SELECT NOW() as Fecha;");

    RecordSet res = m_SQL->getAll(query);
    UltimaSincro = (*res->at(0))["Fecha"].toDateTime().toString("yyyy-MM-dd hh:mm:ss");

    DataStore::instance()->getParametros()->setValue(Parametros::LAST_SYNCHRO, UltimaSincro);
}

void SincroManager::establishConnections()
{
    foreach(DatabaseSynchronizationPtr dbPtr, m_Synchronizationtables)
    {
        establishConnections(dbPtr);
    }
}

void SincroManager::establishConnections(DatabaseSynchronizationPtr db)
{
    connect(db.get(), SIGNAL(gettingDataFromCentralDB(QString &)), this, SIGNAL(gettingDataFromCentralDB(QString&)));
    connect(db.get(), SIGNAL(applyingChanges(QString &)), this, SIGNAL(applyingChanges(QString&)));
    connect(db.get(), SIGNAL(checkingChanges(QString &)), this, SIGNAL(checkingChanges(QString&)));
    connect(db.get(), SIGNAL(sendingData(QString &)), this, SIGNAL(sendingData(QString&)));
}

QStringList SincroManager::getSincroTableNames()
{
    QStringList res;
    foreach(DatabaseSynchronizationPtr dbPtr, m_Synchronizationtables)
    {
        res.push_back(dbPtr->name());
    }
    return res;
}

/**
 * Obtengo las actualizaciones desde la DB central y aplico los cambios
 *
 * Para cada tabla de la lista
 * Obtengo los cambios.
 * Aplico los cambios localmente.
 * Estos cambios se aplican:
 * if A -> Insert
 * if B -> Delete
 * if M -> si Existe -> Update
 *      -> si no Existe -> Insert
 *
 */

/**
 * Verifico que lo que voy a enviar es correcto.
 * Basicamente la idea es verificar que las grillas planificadas sigan siendo coherentes.
 */

/** Si no es coherente corrijo los problemas.
 * Aca lo que hay que hacer es chequear mostrar de alguna manera los cambios
 * que se puedan producir en la grilla
 */

/**
 * Envio mis datos. y los voy aplicando en el servidor central
 * Aca se van enviando, tabla por tabla, los cambios que se han producido localmente.
 */

/**
 * Guardo en la db local la fecha/hora de la ultima actualizacion.
 */
