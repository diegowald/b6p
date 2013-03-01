#include "qmysql.h"
#include <QtSql>
#include <QMessageBox>


QMysql::QMysql(QObject *parent) :
    QObject(parent)
{
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

/**
 * Secuencia
 * -> Obtengo actualizaciones desde la DB Central
 * -> Aplico los cambios basados en esas actualizaciones
 * -> Verifico que lo que voy a enviar es consistente.
 * -> Si no es consistente corrijo los problemas
 * -> Envio mis datos.
 * -> Aplico esos cambios en el servidor central
 * -> Guardo en la db local la fecha de la ultima actualizacion
 */

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
