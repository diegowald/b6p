#include "sqlhandler.h"
#include <QSqlError>
#include <QDateTime>
#include <QVariant>
#include <QMessageBox>
#include <boost/make_shared.hpp>
#include <QSqlRecord>
#include <QSqlField>

SQLHandler::SQLHandler(QString database)
{
    m_database = database;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName(m_database);
}

SQLHandler::SQLHandler(QString Server, QString Database, QString User, QString Password)
{
    m_Server = Server;
    m_database = Database;
    m_User = User;
    m_Password = Password;
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(m_Server);
    db.setDatabaseName(m_database);
    db.setUserName(m_User);
    db.setPassword(m_Password);
}

RecordSet SQLHandler::getAll(QString &query)
{
    RecordSet response = boost::make_shared<QList<RecordPtr> >();

    if (!db.isOpen() && !db.open())
    {
        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database"));
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

    db.close();
    return response;
}

RecordSet SQLHandler::getAll(QString &query, RecordPtr record)
{
    RecordSet response = boost::make_shared<QList<RecordPtr> >();

    if (!db.isOpen())
    {
        if (!db.open())
        {
            qDebug() << db.lastError();
            QMessageBox::critical(NULL, QObject::tr("DB Error"), QObject::tr("Can't open database"));
            return response;
        }
    }

    qDebug() << query;
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

    db.close();

    return response;
}

void SQLHandler::addParameters(QSqlQuery &query, QString SQL, RecordPtr record)
{
    foreach(QString key, record->keys())
    {
        qDebug() << key << ": " << (*record)[key];
        QString param(":" + key);
        if (SQL.contains(param))
        {
            qDebug() << param << " = " << (*record)[key];
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
        }
    }
}

int SQLHandler::executeQuery(QString &cmd, RecordPtr record, bool returnLastInsertedID)
{
    if (!db.isOpen() && !db.open())
    {
        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database"));
        // Error
        return -1;
    }
    qDebug() << cmd;
    QSqlQuery q;
    q.prepare(cmd);
    addParameters(q, cmd, record);
    q.exec();
    if (q.lastError().type() != QSqlError::NoError)
    {
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
    }
    qDebug() << q.lastError();
    db.close();
    if (returnLastInsertedID)
        return q.lastInsertId().toInt();
    else
        return 0;
}
