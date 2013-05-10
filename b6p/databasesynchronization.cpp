#include "databasesynchronization.h"
#include <QDateTime>
#include "dlgmerge.h"

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
    Q_ASSERT(SQL != "");
    RecordPtr r = boost::make_shared<Record>();
    (*r)["LASTUPDATE"] = dateFrom;
    m_QueryResult = m_SQLHandler->getAll(SQL, r);
}

void DatabaseSynchronization::applyChanges()
{
    QString syncroName = name();
    emit applyingChanges(syncroName);
    bool saveAfter = false;
    foreach (RecordPtr rec, *m_QueryResult)
    {
        RecordStatus recStatus = (RecordStatus)(*rec)["RecordStatus"].toInt();
        switch (recStatus)
        {
        case DELETED:
            if (m_Data->exists(rec))
                m_Data->deleteRecord(rec);
            saveAfter = true;
            break;
        case NEW:
            // Fall through
        case MODIFIED:
            // Fall through
        case UNMODIFIED:
            // Fall through
        case UNINITIALIZED:
            // Fall through
        default:
            if (!m_Data->exists(rec))
            {
                m_Data->addRecord(rec, true);
            }
            else
            {
                if (!m_Data->isRecordUnsent(rec))
                {
                    // El registro no ha sido modificado localmente. se toman los datos del server central
                    m_Data->updateRecord(rec);
                }
                else
                {
                    // El registro ha sido modificado localmente.
                    // De acuerdo a la estrategia de los datos, se evalua que hacer.
                    switch (m_Data->mergeStrategy())
                    {
                    case ACollection::MERGE_KEEP_LOCAL:
                        // No se hace nada, ya que es mas importante el cambio local que el central
                        break;
                    case ACollection::MERGE_KEEP_MAIN:
                        // Se hacen los cambios sin preguntar, ya que los cambios centrales son mas importantes.
                        m_Data->updateRecord(rec);
                        break;
                    case ACollection::MERGE_MANUAL:
                        // Aca hay que preguntar cuales son los cambios mas importantes.
                        DlgMerge dlg;
                        RecordPtr localRec = m_Data->getLocalRecord(rec);
                        dlg.setData(rec, localRec, m_Data->getFieldsToShowInMerge());
                        if (dlg.exec() == QDialog::Accepted)
                        {
                            RecordPtr modifiedRec = dlg.mergedRecord();
                            m_Data->updateRecord(modifiedRec);
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

void DatabaseSynchronization::saveLocalChanges()
{
    m_Data->setSentFlagIntoDatabase();
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
    QString sql = m_Data->getInsertStatement(true);
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::updateRecord(RecordPtr rec)
{
    QString sql = m_Data->getUpdateStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}

void DatabaseSynchronization::deleteRecord(RecordPtr rec)
{
    QString sql = m_Data->getDeleteStatement();
    Q_ASSERT(sql != "");
    m_SQLHandler->executeQuery(sql, rec, false);
}
