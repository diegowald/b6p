/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "SincroManager.h"
#include <QtSql>
#include <QMessageBox>
#include "datastore.h"

#include <QsLog.h>

SincroManager::SincroManager(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_SQL = boost::make_shared<SQLHandler>(
                DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, "127.0.0.1"),
                DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, "b6p"),
                DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, "root"),
                DataStore::instance()->getParametros()->getValue(Parametros::PASSWORD, ""));

    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getSectores(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getSubSectores(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getEmpleados(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getCalendarios(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getCapacidades(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getEstimacionesDias(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getPlanificacionesDias(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getPlanificacionesSubSectores(), m_SQL, this));
    m_Synchronizationtables.push_back(boost::make_shared<DatabaseSynchronization>(DataStore::instance()->getLicencias(), m_SQL, this));


    establishConnections();
}

void SincroManager::runSincro()
{
    QLOG_TRACE_FN();
    emit startingSynchro();
    if (conexionADBOK())
    {
        obtenerFechaDesdeServerCentral();
        obtenerFechaUltimaSincronizacion();
        obtenerActualizacionesDeBaseCentral();

        enviarDatosADBCentral();
        grabarFechaUltimaSincronizacion();
    }
    else
    {
        QLOG_ERROR() << "No se puede conectar a la base de datos.";
        QMessageBox::information(NULL, tr("Unable to connect to database"), tr("Please check connection parameters"));
    }
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

bool SincroManager::conexionADBOK()
{
    QLOG_TRACE_FN();

    if (m_Synchronizationtables.count() == 0)
        return false;

    DatabaseSynchronizationPtr db = m_Synchronizationtables.at(0);
    return db->checkConnection();
}

void SincroManager::obtenerFechaUltimaSincronizacion()
{
    QLOG_TRACE_FN();

    m_FechaUltimaSincronizacion =
            DataStore::instance()->getParametros()->getValue(
                Parametros::LAST_SYNCHRO, "2000-01-01 00:00:00");
}

void SincroManager::obtenerActualizacionesDeBaseCentral()
{
    QLOG_TRACE_FN();
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        QLOG_INFO() << "Getting updates for " << db->name();
        if (db->checkConnection())
        {
            db->getDataFromDB(m_FechaUltimaSincronizacion,
                              DataStore::instance()->getParametros()->getLocalMachine());
            db->applyChanges();
            db->checkConsistency();
        }
        QCoreApplication::processEvents();
    }
}

void SincroManager::enviarDatosADBCentral()
{
    QLOG_TRACE_FN();
    foreach(DatabaseSynchronizationPtr db, m_Synchronizationtables)
    {
        QLOG_INFO() << "Sending data for " << db->name();
        if (db->checkConnection())
        {
            db->sendData(DataStore::instance()->getParametros()->getLocalMachine());
            db->saveLocalChanges();
        }
        QCoreApplication::processEvents();
    }
}

void SincroManager::obtenerFechaDesdeServerCentral()
{
    QLOG_TRACE_FN();
    QString query("SELECT NOW() as Fecha;");

    RecordSet res = m_SQL->getAll(query);
    m_FechaSincro = (*res->at(0))["Fecha"].toDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void SincroManager::grabarFechaUltimaSincronizacion()
{
    QLOG_TRACE_FN();

    DataStore::instance()->getParametros()->setValue(Parametros::LAST_SYNCHRO, m_FechaSincro);
    DataStore::instance()->getParametros()->save();
}

void SincroManager::establishConnections()
{
    QLOG_TRACE_FN();
    foreach(DatabaseSynchronizationPtr dbPtr, m_Synchronizationtables)
    {
        establishConnections(dbPtr);
    }
}

void SincroManager::establishConnections(DatabaseSynchronizationPtr db)
{
    QLOG_TRACE_FN();
    connect(db.get(), SIGNAL(gettingDataFromCentralDB(QString &)), this, SIGNAL(gettingDataFromCentralDB(QString&)));
    connect(db.get(), SIGNAL(applyingChanges(QString &)), this, SIGNAL(applyingChanges(QString&)));
    connect(db.get(), SIGNAL(checkingChanges(QString &)), this, SIGNAL(checkingChanges(QString&)));
    connect(db.get(), SIGNAL(sendingData(QString &)), this, SIGNAL(sendingData(QString&)));
}

QStringList SincroManager::getSincroTableNames()
{
    QLOG_TRACE_FN();
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
