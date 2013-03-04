#include "databasesynchronization.h"

DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent) :
    QObject(parent)
{
    m_Data = data;
    m_SQLHandler = sqlHandler;
}

void DatabaseSynchronization::getDataFromDB(QString dateFrom)
{
    emit gettingDataFromCentralDB(name());
    QString SQL = m_Data->getSelectFromMainDB();
    RecordPtr r = boost::make_shared<Record>();
    (*r)["LASTUPDATE"] = dateFrom;
    M_QueryResult = m_SQLHandler->getAll(SQL, r);
}

void DatabaseSynchronization::applyChanges()
{
    emit applyingChanges(name());
}

void DatabaseSynchronization::checkConsistency()
{
    emit checkingChanges(name());
}

void DatabaseSynchronization::sendData()
{
    emit sendingData(name());
}


QString &DatabaseSynchronization::name()
{
    QString s = m_Data->name();
    return s;
}
