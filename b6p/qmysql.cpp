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
