#include "databasesynchronization.h"

DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, QObject *parent) :
    QObject(parent)
{
    m_Data = data;
}

void DatabaseSynchronization::getDataFromDB()
{
    emit gettingDataFromCentralDB(name());
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
