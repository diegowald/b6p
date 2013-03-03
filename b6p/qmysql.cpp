#include "qmysql.h"
#include <QtSql>
#include <QMessageBox>
#include "datastore.h"

QMysql::QMysql(QObject *parent) :
    QObject(parent)
{

    //DatabaseSynchronizationPtr dbs = boost::make_shared<DatabaseSynchronization>();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("b6p");
    db.setUserName("root");
    db.setPassword("mic1492");

    if (!db.open())
        QMessageBox::critical(0, QObject::tr("Database Error"),
                      db.lastError().text());

    db.close();
}

void QMysql::runSincro()
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


void QMysql::obtenerFechaUltimaSincronizacion()
{
    m_FechaUltimaSincronizacion = DataStore::instance()->getParametros()->getValue(Parametros::LAST_SYNCHRO, "");
}

void QMysql::obtenerActualizacionesDeBaseCentral()
{
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        db->getDataFromDB();
        db->applyChanges();
        db->checkConsistency();
    }
}

void QMysql::enviarDatosADBCentral()
{
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        db->sendData();
    }
}


void QMysql::grabarFechaUltimaSincronizacion()
{
    QString UltimaSincro;
    DataStore::instance()->getParametros()->setValue(Parametros::LAST_SYNCHRO, UltimaSincro);
}


void QMysql::establishConnections(DatabaseSynchronizationPtr db)
{
    connect(db.get(), SIGNAL(gettingDataFromCentralDB(QString &)), this, SIGNAL(gettingDataFromCentralDB(QString&)));
    connect(db.get(), SIGNAL(applyingChanges(QString &)), this, SIGNAL(applyingChanges(QString&)));
    connect(db.get(), SIGNAL(checkingChanges(QString &)), this, SIGNAL(checkingChanges(QString&)));
    connect(db.get(), SIGNAL(sendingData(QString &)), this, SIGNAL(sendingData(QString&)));
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
