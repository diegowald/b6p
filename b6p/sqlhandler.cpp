#include "sqlhandler.h"
#include <QSqlError>
#include <QDateTime>
#include <QVariant>

SQLHandler::SQLHandler(QString database)
{
    m_database = database;
}

QSqlQuery SQLHandler::getAll(QString query)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("localhost");
    db.setDatabaseName(m_database);

    if (!db.open())
    {
        // Error
        return QSqlQuery();
    }

    QSqlQuery q(query);
    q.exec();
    return q;
}

int SQLHandler::executeQuery(QString cmd, RecordPtr record, bool returnLastInsertedID)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("localhost");
    db.setDatabaseName(m_database);

    if (!db.open())
    {
        // Error
        return -1;
    }
    qDebug() << cmd;
    QSqlQuery q;
    q.prepare(cmd);

    foreach(QString key, record->keys())
    {
        QString param(":" + key);
        if (cmd.contains(param))
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
                value = dt.toMSecsSinceEpoch();
                break;
            }
            default:
                break;
            }
            q.bindValue(param, value);
        }
    }
    q.exec();
    qDebug() << q.lastError();
    if (returnLastInsertedID)
        return q.lastInsertId().toInt();
    else
        return 0;
}
