#include "databasesynchronization.h"
#include <QDateTime>
#include "dlgmerge.h"
#include <QsLog.h>


DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE() << "DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent)";
    m_Data = data;
    m_SQLHandler = sqlHandler;
}

bool DatabaseSynchronization::checkConnection()
{
    QLOG_TRACE() << "void DatabaseSynchronization::getDataFromDB(QString dateFrom)";
    return m_SQLHandler->checkConnection();
}

void DatabaseSynchronization::getDataFromDB(QString dateFrom)
{
    QLOG_TRACE() << "void DatabaseSynchronization::getDataFromDB(QString dateFrom)";
    QString syncroName = name();
    emit gettingDataFromCentralDB(syncroName);
    QString SQL = m_Data->getSelectFromMainDB();
    Q_ASSERT(SQL != "");
    RecordPtr r = boost::make_shared<Record>();
    (*r)["LASTUPDATE"] = dateFrom;
    m_QueryResult = m_SQLHandler->getAll(SQL, r);
}

void DatabaseSynchronization::applyChanges()
{
    QLOG_TRACE() << "void DatabaseSynchronization::applyChanges()";
    QLOG_INFO() << "Applying changes on " << name();
    QString syncroName = name();
    emit applyingChanges(syncroName);
    bool saveAfter = false;
    foreach (RecordPtr rec, *m_QueryResult)
    {
        RecordStatus recStatus = (RecordStatus)(*rec)["RecordStatus"].toInt();
        switch (recStatus)
        {
        case DELETED:
            QLOG_INFO() << "Status Deleted";
            if (m_Data->exists(rec))
            {
                m_Data->deleteRecord(rec, true);
            }
            saveAfter = true;
            break;
        case UNINITIALIZED:
            // Fall through
            QLOG_INFO() << "Status Uninitialized";
        case UNMODIFIED:
            QLOG_INFO() << "Status Unmodified";
            break;
        case NEW:
            // Fall through
            QLOG_INFO() << "Status New";
        case MODIFIED:
            // Fall through
            QLOG_INFO() << "Status Modified";
        default:
            if (!m_Data->exists(rec))
            {
                QLOG_INFO() << "Record does not exist.";
                m_Data->addRecord(rec, true);
            }
            else
            {
                QLOG_INFO() << "Record exists.";
                if (!m_Data->isRecordUnsent(rec))
                {
                    QLOG_INFO() << "Just update record here";
                    // El registro no ha sido modificado localmente. se toman los datos del server central
                    if (!m_Data->localRecordIsEqualsTo(rec))
                    {
                        m_Data->updateRecord(rec, true);
                    }
                }
                else
                {
                    QLOG_INFO() << "Record unsent. based on strategy proceed.";
                    // El registro ha sido modificado localmente.
                    // De acuerdo a la estrategia de los datos, se evalua que hacer.
                    switch (m_Data->mergeStrategy())
                    {
                    case ACollection::MERGE_KEEP_LOCAL:
                        QLOG_INFO() << "MERGE KEEP LOCAL";
                        // No se hace nada, ya que es mas importante el cambio local que el central
                        break;
                    case ACollection::MERGE_KEEP_MAIN:
                        // Se hacen los cambios sin preguntar, ya que los cambios centrales son mas importantes.
                        QLOG_INFO() << "MERGE KEEP MAIN";
                        m_Data->updateRecord(rec, false);
                        break;
                    case ACollection::MERGE_MANUAL:
                        // Aca hay que preguntar cuales son los cambios mas importantes.
                        RecordPtr localRec = m_Data->getLocalRecord(rec);
                        QLOG_DEBUG() << rec;
                        if (!m_Data->localRecordIsEqualsTo(rec))
                        {
                            QLOG_DEBUG() << "Needs to be merged";
                            DlgMerge dlg;
                            dlg.setData(rec, localRec, m_Data->getFieldsToShowInMerge());
                            if (dlg.exec() == QDialog::Accepted)
                            {
                                RecordPtr modifiedRec = dlg.mergedRecord();
                                m_Data->updateRecord(modifiedRec, false);
                            }
                        }
                        else
                        {
                            QLOG_DEBUG() << "Record is equal to local.";
                        }
                        break;
                    }
                }
            }
            saveAfter = true;
            break;
        }
    }
    if (saveAfter)
        m_Data->save(true);
}

void DatabaseSynchronization::checkConsistency()
{
    QLOG_TRACE() << "void DatabaseSynchronization::checkConsistency()";
    QString syncroName = name();
    emit checkingChanges(syncroName);
}

void DatabaseSynchronization::sendData()
{
    QLOG_TRACE() << "void DatabaseSynchronization::sendData()";
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

void DatabaseSynchronization::saveLocalChanges()
{
    QLOG_TRACE() << "void DatabaseSynchronization::saveLocalChanges()";
    m_Data->setSentFlagIntoDatabase();
}

QString DatabaseSynchronization::name()
{
    QLOG_TRACE() << "QString DatabaseSynchronization::name()";
    return m_Data->name();
}


bool DatabaseSynchronization::existsInMainDB(RecordPtr rec)
{
    QLOG_TRACE() << "bool DatabaseSynchronization::existsInMainDB(RecordPtr rec)";
    QString sql = m_Data->getSQLExistsInMainDB();
    RecordSet res = m_SQLHandler->getAll(sql, rec);
    return res->count() != 0;
}

void DatabaseSynchronization::addRecord(RecordPtr rec)
{
    QLOG_TRACE() << "void DatabaseSynchronization::addRecord(RecordPtr rec)";
    QString sql = m_Data->getInsertStatement(true);
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::updateRecord(RecordPtr rec)
{
    QLOG_TRACE() << "void DatabaseSynchronization::updateRecord(RecordPtr rec)";
    QString sql = m_Data->getUpdateStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::deleteRecord(RecordPtr rec)
{
    QLOG_TRACE() << "void DatabaseSynchronization::deleteRecord(RecordPtr rec)";
    QString sql = m_Data->getDeleteStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}
