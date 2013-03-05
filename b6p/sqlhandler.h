#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include "IRecord.h"

class SQLHandler
{
public:
    SQLHandler(QString database);
    SQLHandler(QString Server, QString Database, QString User, QString Password);

    RecordSet getAll(QString &query);
    RecordSet getAll(QString &query, RecordPtr record);
    int executeQuery(QString &cmd, RecordPtr record, bool returnLastInsertedID);

protected:
    void addParameters(QSqlQuery &query, QString SQL, RecordPtr record);

private:
    QString m_database;
    QSqlDatabase db;
    QString m_Server;
    QString m_User;
    QString m_Password;
};

#endif // SQLHANDLER_H
