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
#ifndef SINCROMANAGER_H
#define SINCROMANAGER_H

#include <QObject>
#include "databasesynchronization.h"
#include <boost/shared_ptr.hpp>
#include "sqlhandler.h"


class SincroManager : public QObject
{
    Q_OBJECT
public:
    explicit SincroManager(QObject *parent = 0);

    void runSincro();
    QStringList getSincroTableNames();
protected:
    void obtenerFechaUltimaSincronizacion();
    void obtenerActualizacionesDeBaseCentral();
    void obtenerFechaDesdeServerCentral();

    void enviarDatosADBCentral();

    void grabarFechaUltimaSincronizacion();

    void establishConnections();
    void establishConnections(DatabaseSynchronizationPtr db);
    bool conexionADBOK();

signals:
    void startingSynchro();
    void getDataFromCentralDB(QString &tableName);
    void applyingChanges(QString &tableName);
    void checkingChanges(QString &tableName);
    void sendingData(QString &tableName);
    void SynchroEnded();
public slots:
    

private:
    QString m_FechaUltimaSincronizacion;
    QList<DatabaseSynchronizationPtr> m_Synchronizationtables;
    boost::shared_ptr<SQLHandler> m_SQL;
    QString m_FechaSincro;
};

#endif // QMYSQL_H
