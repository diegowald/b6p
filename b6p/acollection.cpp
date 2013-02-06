#include "acollection.h"
#include <QDebug>

#include <QSqlRecord>
#include <QSqlField>

ACollection::ACollection(QString Name, bool useLastInsertId, QObject *parent) :
    QObject(parent), m_Name(Name), sqlEngine("./planning.b6p"), usesLastInsertedId(useLastInsertId)
{
}


void ACollection::load()
{
    emit loading(m_Name);

    QString sqlString = getSqlString();

    QSqlQuery query = sqlEngine.getAll(sqlString);
    while (query.next())
    {
        QSqlRecord rec = query.record();
        Record record;
        for (int i = 0; i < rec.count(); i++)
        {
            record[rec.fieldName(i)] = rec.field(i).value();
        }
        addRecord(record);
    }
    emit loaded(m_Name);
}

void ACollection::save()
{
    emit saving(m_Name);
    // Obtener los registros eliminados.
    deleteRecordsDB();

    // Obtener los registros modificados
    updateRecordsToDB();

    // Obtener los registros nuevos
    addNewRecordsToDB();

    saveDependants();

    emit saved(m_Name);
}

void ACollection::deleteRecordsDB()
{
    executeCommand(getDeleteStatement(), DELETED);
}

void ACollection::updateRecordsToDB()
{
    executeCommand(getUpdateStatement(), MODIFIED);
}

void ACollection::addNewRecordsToDB()
{
    executeCommand(getInsertStatement(), NEW);
}

void ACollection::executeCommand(QString cmd, RecordStatus status)
{
    RecordSet set = getRecords(status);
    foreach(RecordPtr r, *set)
    {
        int lastId = sqlEngine.executeQuery(cmd, r, usesLastInsertedId);
        if ((status == NEW) && usesLastInsertedId)
            refreshID(lastId);
    }
}

bool ACollection::addNewRecord()
{
    bool result = addNew();
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QVariant ID)
{
    bool result = edit(ID);
    if (result)
        save();
    return result;
}

QString ACollection::name() const
{
    return m_Name;
}
