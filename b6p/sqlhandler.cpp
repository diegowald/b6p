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
    RecordSet response = boost::make_shared<QList<RecordPtr> >();

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
        RecordPtr record = boost::make_shared<Record>();
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
    RecordSet response = boost::make_shared<QList<RecordPtr> >();

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
        RecordPtr record = boost::make_shared<Record>();
        for (int i = 0; i < rec.count(); i++)
        {
            (*record)[rec.fieldName(i)] = rec.field(i).value();
        }
        response->push_back(record);
    }

    if (q.lastError().type() != QSqlError::NoError)
    {
        QLOG_ERROR() << QObject::tr("SQL Error") <<  q.lastError().text();
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
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
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
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
