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
#include "sqlhandler.h"
#include <QSqlError>
#include <QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <boost/make_shared.hpp>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlDriver>
#include <QsLog.h>

SQLHandler::SQLHandler(QString database)
{
    QLOG_TRACE_FN();
    m_database = database;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(m_database);
    m_UsingSQLITE = true;
}

SQLHandler::SQLHandler(QString Server, QString Database, QString User, QString Password)
{
    QLOG_TRACE_FN();
    m_Server = Server;
    m_database = Database;
    m_User = User;
    m_Password = Password;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(m_Server);
    db.setDatabaseName(m_database);
    db.setUserName(m_User);
    db.setPassword(m_Password);
    m_UsingSQLITE = false;
}

bool SQLHandler::tryReconnect()
{
    QLOG_TRACE_FN();
    if (!db.isOpen() && !db.open())
    {
        if (m_UsingSQLITE)
        {
            QLOG_INFO() << "Database trying to reconnect: SQLite Database";
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setHostName("localhost");
            db.setDatabaseName(m_database);
        }
        else
        {
            QLOG_INFO() << "Database trying to reconnect: MySQL Database";
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(m_Server);
            db.setDatabaseName(m_database);
            db.setUserName(m_User);
            db.setPassword(m_Password);
        }
    }


    if (db.isOpen())
        return true;

    bool result = db.open();
    if (!result)
    {
        QLOG_ERROR() << "DB cannot be opened. Reason:" << db.lastError().text();
    }
    return result;
}

bool SQLHandler::checkConnection()
{
    QLOG_TRACE_FN();
    if (!tryReconnect())
        return false;
    QString sql = "SELECT 1;";
    RecordSet rs = getAll(sql);
    return (1 == rs->count());
}

RecordSet SQLHandler::getAll(QString &query)
{
    QLOG_TRACE_FN();
    RecordSet response = RecordSet::create();

    if (!tryReconnect())
    {
        QLOG_ERROR() << QObject::tr("Can't open Database.")
                     << QObject::tr("Reason: ")
                     << db.lastError().text();

        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database")
                                 + '\n'
                                 + QObject::tr("Reason: ")
                                 + db.lastError().text());
        // Error
        return response;
    }

    QSqlQuery q(query);
    q.exec();

    while (q.next())
    {
        QSqlRecord rec = q.record();
        RecordPtr record = RecordPtr::create();
        for (int i = 0; i < rec.count(); i++)
        {
            (*record)[rec.fieldName(i)] = rec.field(i).value();
        }
        response->push_back(record);
    }

    if (q.lastError().type() != QSqlError::NoError)
    {
        QLOG_ERROR() << QObject::tr("SQL Error: ")
                     << q.lastError().text();
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
    }
    db.close();
    return response;
}

RecordSet SQLHandler::getAll(QString &query, RecordPtr record)
{
    QLOG_TRACE_FN();
    QLOG_DEBUG() << "Query: " << query;
    RecordSet response = RecordSet::create();

    if (!tryReconnect())
    {
        QLOG_ERROR() <<  QObject::tr("Can't open Database. ")
                      << QObject::tr("Reason: ")
                      << db.lastError().text();

        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database")
                                 + '\n'
                                 + QObject::tr("Reason: ")
                                 + db.lastError().text());

        return response;
    }

    QSqlQuery q;
    q.prepare(query);
    addParameters(q, query, record);
    q.exec();

    while (q.next())
    {
        QSqlRecord rec = q.record();
        RecordPtr record = RecordPtr::create();
        for (int i = 0; i < rec.count(); i++)
        {
            (*record)[rec.fieldName(i)] = rec.field(i).value();
        }
        response->push_back(record);
    }

    if (q.lastError().type() != QSqlError::NoError)
    {
        QLOG_ERROR() << QObject::tr("SQL Error") <<  q.lastError().text();
        QMessageBox::information(NULL, QObject::tr("SQL Error"), query + "\n" + q.lastError().text());
    }
    db.close();

    return response;
}

void SQLHandler::addParameters(QSqlQuery &query, QString &SQL, RecordPtr record)
{
    QLOG_TRACE_FN();
    foreach(QString key, record->keys())
    {
        QString param(":" + key);
        if (SQL.contains(param))
        {
            QVariant value = (*record)[key];
            switch (value.type())
            {
            case QVariant::DateTime:
            case QVariant::Date:
            case QVariant::Time:
            {
                QDateTime dt = value.toDateTime();
                if (value.type() == QVariant::Time)
                {
                    dt.setDate(QDateTime::currentDateTime().date());
                    dt.setTime(value.toTime());
                }
                value = dt.toMSecsSinceEpoch();
                break;
            }
            default:
                break;
            }
            query.bindValue(param, value);
            QLOG_DEBUG() << "Parameter: " << param << ", Value: " << value;
        }
    }
}

int SQLHandler::executeQuery(QString &cmd, RecordPtr record, bool returnLastInsertedID)
{
    QLOG_TRACE_FN();
    QLOG_DEBUG() << "cmd: " << cmd;
    QLOG_DEBUG() << "returnLastInsertedID: " << returnLastInsertedID;
    if (!tryReconnect())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");
        db.setDatabaseName(m_database);
    }

    QSqlQuery q;
    q.prepare(cmd);
    addParameters(q, cmd, record);
    q.exec();
    if (q.lastError().type() != QSqlError::NoError)
    {
        QLOG_ERROR() << QObject::tr("SQL Error:") << q.lastError().text();
        QString msg = cmd + " "  + q.lastError().text();
        QMessageBox::information(NULL, QObject::tr("SQL Error"), msg);
    }

    qlonglong lastID = (returnLastInsertedID ? q.lastInsertId().toLongLong() : -1);
    db.close();

    if (returnLastInsertedID)
    {
        QLOG_DEBUG() << q.lastInsertId();
        QLOG_DEBUG() << lastID;
        return (int)lastID;
    }
    else
        return 0;
}

void SQLHandler::executeCommand(QString &cmd)
{
    QLOG_TRACE_FN();
    QLOG_DEBUG() << "cmd: " << cmd;
    if (!tryReconnect())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");
        db.setDatabaseName(m_database);
    }

    QSqlQuery q;
    q.prepare(cmd);
    q.exec();

    if (q.lastError().type() != QSqlError::NoError)
    {
        QLOG_ERROR() << QObject::tr("SQL Error: ") << q.lastError().text();
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
    }

    db.close();
}
