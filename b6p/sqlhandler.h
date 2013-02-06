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
    int executeQuery(QString cmd, RecordPtr record, bool returnLastInsertedID);

private:
    QString m_database;
};

#endif // SQLHANDLER_H
