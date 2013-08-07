#include "acollection.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QsLog.h>


ACollection::ACollection(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent) :
    QObject(parent),
    m_Name(Name),
    m_InvariableName(InvariableName),
    sqlEngine("./planning.b6p"),
    usesLastInsertedId(useLastInsertId),
    m_MergeStrategy(MergeStrategy)
{
    QLOG_TRACE() << "ACollection::ACollection(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent)";
}


void ACollection::load()
{
    QLOG_TRACE() << "void ACollection::load()";
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
    QLOG_TRACE() << "void ACollection::save(bool includeIDs)";
    emit saving(m_Name);

    deleteRecordsLocally();
    updateRecordsLocally();
    addNewRecordsLocally();
    saveDependants();
    ///DIEGO///
    //la instruccion de abajo debe setear la bandera de que los registros en memoria estan
    //        seteados a grabados a local storage.
    setStatusToUnmodified(false); // antes true
    emit dataUpdated();
    emit saved(m_Name);
}

void ACollection::saveLocally()
{
    QLOG_TRACE() << "void ACollection::saveLocally()";
    emit saving(m_Name);

    deleteRecordsLocally();
    updateRecordsLocally();
    addNewRecordsLocally();
    saveDependants();
    ///DIEGO///
    //la instruccion de abajo debe setear la bandera de que los registros en memoria estan
    //        seteados a grabados a local storage.
    setStatusToUnmodified(false); // antes true
    emit dataUpdated();
    emit saved(m_Name);
}

void ACollection::deleteRecordsLocally()
{
    QLOG_TRACE() << "void ACollection::deleteRecordsLocally()";
    executeCommand(getLocalDeleteStatement(), DELETED, true);
}

void ACollection::updateRecordsLocally()
{
    QLOG_TRACE() << "void ACollection::updateRecordsLocally()";
    executeCommand(getLocalUpdateStatement(), MODIFIED, true);
}

void ACollection::addNewRecordsLocally()
{
    QLOG_TRACE() << "void ACollection::addNewRecordsLocally()";
    executeCommand(getLocalInsertStatement(), NEW, true);
}

void ACollection::deleteRecordsCentralDB()
{
    QLOG_TRACE() << "void ACollection::deleteRecordsCentralDB()";
    executeCommand(getCentralDeleteStatement(), DELETED, false);
}

void ACollection::updateRecordsCentralDB()
{
    QLOG_TRACE() << "void ACollection::updateRecordsCentralDB()";
    executeCommand(getCentralUpdateStatement(), MODIFIED, false);
}

void ACollection::addNewRecordsCentralDB()
{
    QLOG_TRACE() << "void ACollection::addNewRecordsCentralDB()";
    executeCommand(getCentralInsertStatement(), NEW, false);
}


void ACollection::executeCommand(QString cmd, RecordStatus status, bool impactLocalDatabase)
{
    QLOG_TRACE() << "void ACollection::executeCommand(QString cmd, RecordStatus status)";
    RecordSet set = getRecords(status, impactLocalDatabase);
    foreach(RecordPtr r, *set)
    {
        int newID = sqlEngine.executeQuery(cmd, r, usesLastInsertedId);
        if ((status == NEW) && usesLastInsertedId)
            refreshID((*r)[RECORD_ID].toInt(), newID);
    }
}

bool ACollection::addNewRecord(QTreeWidgetItem *item)
{
    QLOG_TRACE() << "bool ACollection::addNewRecord(QTreeWidgetItem *item)";
    bool result = addNew(item);
    if (result)
        save();
    return result;
}

bool ACollection::addNewRecord()
{
    QLOG_TRACE() << "bool ACollection::addNewRecord()";
    bool result = addNew();
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QTreeWidgetItem *item, QVariant ID)
{
    QLOG_TRACE() << "bool ACollection::editRecord(QTreeWidgetItem *item, QVariant ID)";
    bool result = edit(item, ID);
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QVariant ID)
{
    QLOG_TRACE() << "bool ACollection::editRecord(QVariant ID)";
    bool result = edit(ID);
    if (result)
        save();
    return result;
}

bool ACollection::deleteRecord(QVariant ID)
{
    QLOG_TRACE() << "bool ACollection::deleteRecord(QVariant ID)";
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
    QLOG_TRACE() << "QString &ACollection::name()";
    return m_Name;
}

QString ACollection::invariableName() const
{
    QLOG_TRACE() << "QString ACollection::invariableName() const";
    return m_InvariableName;
}

void ACollection::setSentFlagIntoDatabase()
{
    QLOG_TRACE() << "void ACollection::setSentFlagIntoDatabase()";
    QString sql = "UPDATE %1 set sent = 1;";
    sql = sql.arg(getTableName());
    sqlEngine.executeCommand(sql);
    setSentFlagIntoMemory();
}

void ACollection::exportTo(const QString &filename)
{
    QLOG_TRACE() << "void ACollection::exportTo(const QString &filename)";
    QString fileName = (filename.toLower().endsWith(".csv") ? filename: filename + ".csv");
    QFile file(fileName);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream st(&file);
        QStringList headers;
        defineHeaders(headers);
        QString r = "\"" + headers.join("\",\"") + "\"";
        st << r << endl;

        boost::shared_ptr<QList<QStringList> > records = getAll();

        foreach(QStringList record, *records)
        {
            QString r = "\"" + record.join("\",\"") + "\"";
            st << r << endl;
        }
        QMessageBox::information(NULL,
                                 tr("Export to CSV"),
                                 tr("Successfuly exported!"));
    }
    else
    {
        QMessageBox::information(NULL,
                                 tr("Export to CSV Error"),
                                 tr("Couldn't open file."));
    }
}

QString ACollection::asHTML()
{
    QLOG_TRACE() << "QString ACollection::asHTML()";
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header
    QStringList headers;
    defineHeaders(headers);
    html += "<tr>";
    foreach(QString header, headers) {
        html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
        html += "<b><i>" + header + "</i></b></font>\n</td>";
    }
    html += "</tr>";

    boost::shared_ptr<QList<QStringList> > records = getAll();
    foreach(QStringList record, *records) {
        html += "<tr>";
        foreach(QString field, record) {
            html += "<td>" + field + "</td>";
        }
        html += "</tr>";
    }

    html += "\n</table>\n<br>\n";
    return html;
}

ACollection::MERGE_STRATEGY ACollection::mergeStrategy() const
{
    QLOG_TRACE() << "ACollection::MERGE_STRATEGY ACollection::mergeStrategy() const";
    return m_MergeStrategy;
}
