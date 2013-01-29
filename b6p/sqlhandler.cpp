#include "sqlhandler.h"

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
    }

    QSqlQuery q(query);
    q.exec();
    return q;
}
