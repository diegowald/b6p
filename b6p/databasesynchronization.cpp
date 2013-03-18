#include "databasesynchronization.h"

DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent) :
    QObject(parent)
{
    m_Data = data;
    m_SQLHandler = sqlHandler;
}

void DatabaseSynchronization::getDataFromDB(QString dateFrom)
{
    QString syncroName = name();
    emit gettingDataFromCentralDB(syncroName);
    QString SQL = m_Data->getSelectFromMainDB();
    RecordPtr r = boost::make_shared<Record>();
    (*r)["LASTUPDATE"] = dateFrom;
    m_QueryResult = m_SQLHandler->getAll(SQL, r);
}

void DatabaseSynchronization::applyChanges()
{
    QString syncroName = name();
    emit applyingChanges(syncroName);
    foreach (RecordPtr rec, *m_QueryResult)
    {
        RecordStatus recStatus = (RecordStatus)(*rec)["RecordStatus"].toInt();
        switch (recStatus)
        {
        case NEW:
        case MODIFIED:
            if (!m_Data->exists(rec))
                m_Data->addRecord(rec);
            else
                m_Data->updateRecord(rec);
            break;
        case DELETED:
            if (m_Data->exists(rec))
                m_Data->deleteRecord(rec);
            break;
        case UNINITIALIZED:
            // Fall through
        case UNMODIFIED:
            // Fall through
        default:
            // Do nothing
            break;
        }
    }
}

void DatabaseSynchronization::checkConsistency()
{
    QString syncroName = name();
    emit checkingChanges(syncroName);
}

void DatabaseSynchronization::sendData()
{
    QString syncroName = name();
    emit sendingData(syncroName);
    // obtengo los datos modificados desde la base local
    // estos serian los registros que estan con el flag de enviado en false.

    RecordSet toSend = m_Data->getUnsent();
    foreach(RecordPtr rec, *toSend)
    {
        RecordStatus recStatus = (RecordStatus)(*rec)["RecordStatus"].toInt();
        switch(recStatus)
        {
        case UNINITIALIZED:
            // Fall through
        case UNMODIFIED:
            // Fall through
        case NEW:
            // Fall through
        case MODIFIED:
            if (!existsInMainDB(rec))
                addRecord(rec);
            else
                updateRecord(rec);
            break;
        case DELETED:
            if (existsInMainDB(rec))
                deleteRecord(rec);
            break;
        default:
            // Do nothing
            break;
        }
    }
}



QString DatabaseSynchronization::name()
{
    return m_Data->name();
}


bool DatabaseSynchronization::existsInMainDB(RecordPtr rec)
{
    QString sql = m_Data->getSQLExistsInMainDB();
    RecordSet res = m_SQLHandler->getAll(sql, rec);
    return res->count() != 0;
}

void DatabaseSynchronization::addRecord(RecordPtr rec)
{
    QString s = " USE b6p;";
    m_SQLHandler->executeQuery(s, rec, false);
    QString sql = m_Data->getInsertStatement();
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::updateRecord(RecordPtr rec)
{
    QString sql = m_Data->getUpdateStatement();
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::deleteRecord(RecordPtr rec)
{
    QString sql = m_Data->getDeleteStatement();
    m_SQLHandler->executeQuery(sql, rec, false);
}
