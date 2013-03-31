#include "acollection.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>

ACollection::ACollection(QString Name, QString InvariableName, bool useLastInsertId, QObject *parent) :
    QObject(parent),
    m_Name(Name),
    m_InvariableName(InvariableName),
    sqlEngine("./planning.b6p"),
    usesLastInsertedId(useLastInsertId)
{
}


void ACollection::load()
{
    emit loading(m_Name);

    QString sqlString = getSqlString();

    RecordSet resp = sqlEngine.getAll(sqlString);

    foreach (RecordPtr record, *resp)
    {
        addRecord(record);
    }
    emit loaded(m_Name);
}

void ACollection::save()
{
    emit saving(m_Name);

    deleteRecordsDB();
    updateRecordsToDB();
    addNewRecordsToDB();
    saveDependants();
    setStatusToUnmodified(true);
    emit dataUpdated();
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
    executeCommand(getInsertStatement(false), NEW);
}

void ACollection::executeCommand(QString cmd, RecordStatus status)
{
    RecordSet set = getRecords(status);
    foreach(RecordPtr r, *set)
    {
        int newID = sqlEngine.executeQuery(cmd, r, usesLastInsertedId);
        if ((status == NEW) && usesLastInsertedId)
            refreshID((*r)[RECORD_ID].toInt(), newID);
    }
}

bool ACollection::addNewRecord(QTreeWidgetItem *item)
{
    bool result = addNew(item);
    if (result)
        save();
    return result;
}

bool ACollection::addNewRecord()
{
    bool result = addNew();
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QTreeWidgetItem *item, QVariant ID)
{
    bool result = edit(item, ID);
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

bool ACollection::deleteRecord(QVariant ID)
{
    bool result = false;
    if (canBeDeleted(ID))
    {
        QMessageBox msg;
        msg.setText(tr("Delete element"));
        msg.setInformativeText(tr("Do you want to remove it?"));
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::No);
        if (msg.exec() == QMessageBox::Yes)
        {
            result = deleteElement(ID);
            if (result)
                save();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText(tr("Delete element"));
        msg.setInformativeText(tr("Unable to delete element."));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        result = false;
    }
    return result;
}

QString &ACollection::name()
{
    return m_Name;
}

QString ACollection::invariableName() const
{
    return m_InvariableName;
}

void ACollection::setSentFlagIntoDatabase()
{
    QString sql = "UPDATE %1 set sent = 1;";
    sql = sql.arg(getTableName());
    sqlEngine.executeCommand(sql);
}

void ACollection::exportTo(const QString &filename)
{
    QStringList headers;
    defineHeaders(headers);
    //virtual void fillData(QTreeWidget &tree) = 0;
    QMessageBox::information(NULL, "TODO", "Implementar exportacion a CSV");
}
