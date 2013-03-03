#include "databasesynchronization.h"

DatabaseSynchronization::DatabaseSynchronization(QString Name, QObject *parent) :
    QObject(parent)
{
    name = Name;
}

void DatabaseSynchronization::getDataFromDB()
{
    emit gettingDataFromCentralDB(name);
}

void DatabaseSynchronization::applyChanges()
{
    emit applyingChanges(name);
}

void DatabaseSynchronization::checkConsistency()
{
    emit checkingChanges(name);
}

void DatabaseSynchronization::sendData()
{
    emit sendingData(name);
}
