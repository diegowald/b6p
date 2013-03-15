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
}


QString DatabaseSynchronization::name()
{
    return m_Data->name();
}
