#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>

class SQLHandler
{
public:
    SQLHandler(QString database);

    QSqlQuery getAll(QString query);

private:
    QString m_database;
};

#endif // SQLHANDLER_H
