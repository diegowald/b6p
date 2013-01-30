#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include "IRecord.h"

class SQLHandler
{
public:
    SQLHandler(QString database);

    QSqlQuery getAll(QString query);
    void executeQuery(QString cmd, RecordPtr record);

private:
    QString m_database;
};

#endif // SQLHANDLER_H
