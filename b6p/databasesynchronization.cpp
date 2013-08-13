#include "databasesynchronization.h"
#include <QDateTime>
#include "dlgmerge.h"
#include <QsLog.h>


DatabaseSynchronization::DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_Data = data;
    m_SQLHandler = sqlHandler;
}

bool DatabaseSynchronization::checkConnection()
{
    QLOG_TRACE_FN();
    return m_SQLHandler->checkConnection();
}

void DatabaseSynchronization::getDataFromDB(const QString &dateFrom, const QString &senderMachine)
{
    QLOG_TRACE_FN();
    QString syncroName = name();
    emit gettingDataFromCentralDB(syncroName);
    QString SQL = m_Data->getSelectFromMainDB();
    Q_ASSERT(SQL != "");
    RecordPtr r = boost::make_shared<Record>();
    (*r)["LASTUPDATE"] = dateFrom;
    (*r)["SenderMachine"] = senderMachine;
    m_QueryResult = m_SQLHandler->getAll(SQL, r);
}

void DatabaseSynchronization::applyChanges()
{
    QLOG_TRACE_FN();
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
        m_Data->save();
}

void DatabaseSynchronization::checkConsistency()
{
    QLOG_TRACE_FN();
    QString syncroName = name();
    emit checkingChanges(syncroName);
}

void DatabaseSynchronization::sendData(const QString &senderMachine)
{
    QLOG_TRACE_FN();
    QString syncroName = name();
    emit sendingData(syncroName);
    // obtengo los datos modificados desde la base local
    // estos serian los registros que estan con el flag de enviado en false.

    RecordSet toSend = m_Data->getUnsent();
    //aca tengo que traer los registros que no fueron enviados a la base central
    //en record status estoy obteniendo el estado de los registros en memoria.
    foreach(RecordPtr rec, *toSend)
    {
        (*rec)["SenderMachine"] = senderMachine;
        RecordStatus recStatus = (RecordStatus)(*rec)["RecordStatus"].toInt();
        switch(recStatus)
        {
        case UNINITIALIZED:
            // Fall through
        case UNMODIFIED:
            // Fall through
            break;
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
    QLOG_TRACE_FN();
    m_Data->setLocalStatusToUnmodified();
}

QString DatabaseSynchronization::name()
{
    QLOG_TRACE_FN();
    return m_Data->name();
}


bool DatabaseSynchronization::existsInMainDB(RecordPtr rec)
{
    QLOG_TRACE_FN();
    QString sql = m_Data->getSQLExistsInMainDB();
    RecordSet res = m_SQLHandler->getAll(sql, rec);
    return res->count() != 0;
}

void DatabaseSynchronization::addRecord(RecordPtr rec)
{
    QLOG_TRACE_FN();
    QString sql = m_Data->getCentralInsertStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::updateRecord(RecordPtr rec)
{
    QLOG_TRACE_FN();
    QString sql = m_Data->getCentralUpdateStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::deleteRecord(RecordPtr rec)
{
    QLOG_TRACE_FN();
    QString sql = m_Data->getCentralDeleteStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}
