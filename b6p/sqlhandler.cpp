#include "sqlhandler.h"
#include <QSqlError>
#include <QDateTime>
#include <QVariant>
#include <QMessageBox>
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
        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database"));
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
        QMessageBox::information(NULL, QObject::tr("DB Error"), QObject::tr("Can't open Database"));
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
            q.bindValue(param, value);
        }
    }
    q.exec();
    if (q.lastError().type() != QSqlError::NoError)
    {
        QMessageBox::information(NULL, QObject::tr("SQL Error"), q.lastError().text());
    }
    qDebug() << q.lastError();
    if (returnLastInsertedID)
        return q.lastInsertId().toInt();
    else
        return 0;
}
