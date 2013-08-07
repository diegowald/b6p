#ifndef ACOLLECTION_H
#define ACOLLECTION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QTreeWidget>
#include "sqlhandler.h"
#include "IRecord.h"
#include <QAction>
#include <QList>
#include <QTextDocument>
#include <QsLogLevel.h>

class ACollection : public QObject
{
    Q_OBJECT
public:
    enum RECORD_STATUS
    {
        RECORD_UNMODIFIED,
        RECORD_NEW,
        RECORD_MODIFIED,
        RECORD_DELETED
    };

    enum MERGE_STRATEGY
    {
        MERGE_KEEP_MAIN,
        MERGE_KEEP_LOCAL,
        MERGE_MANUAL
    };

    explicit ACollection(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent = 0);
    
    virtual void exportTo(const QString &filename);
    virtual void load();
    virtual void save();
    virtual void saveLocally();
    virtual QString asHTML();
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc) = 0;

    QString &name();
    QString invariableName() const;

    virtual QString suggestedFileName() { return name(); }
    virtual QString getSqlString() = 0;
    virtual void addRecord(RecordPtr record, bool setNew = false) = 0;

    virtual bool exists(RecordPtr record) = 0;
    virtual void updateRecord(RecordPtr record, bool isFromSincro) = 0;
    virtual void deleteRecord(RecordPtr record, bool isFromSincro) = 0;
    virtual bool isRecordUnsent(RecordPtr record) = 0;
    virtual RecordPtr getLocalRecord(RecordPtr record) = 0;
    virtual QStringList getFieldsToShowInMerge() = 0;
    virtual ACollection::MERGE_STRATEGY mergeStrategy() const;

    virtual void defineHeaders(QStringList &list) = 0;
    virtual boost::shared_ptr<QList<QStringList> > getAll() = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool isColumnEditable(QVariant, int) { return false; }
    virtual boost::shared_ptr<QList<QAction*> > getActions() { return boost::make_shared<QList<QAction*> >(); }
    bool addNewRecord();
    bool addNewRecord(QTreeWidgetItem *item);
    bool editRecord(QVariant ID);
    bool editRecord(QTreeWidgetItem *item, QVariant ID);
    bool deleteRecord(QVariant ID);
    void setSentFlagIntoDatabase();

    virtual QString getTableName() = 0;
/*    virtual QString getDeleteStatement(bool includeSenderMachine) = 0;
    virtual QString getUpdateStatement(bool includeSenderMachine) = 0;
    virtual QString getInsertStatement(bool IncludeIDs, bool includeSenderMachine) = 0;*/

    virtual QString getLocalDeleteStatement() = 0;
    virtual QString getLocalUpdateStatement() = 0;
    virtual QString getLocalInsertStatement() = 0;

    virtual QString getCentralDeleteStatement() = 0;
    virtual QString getCentralUpdateStatement() = 0;
    virtual QString getCentralInsertStatement() = 0;


    virtual QString getSQLExistsInMainDB() = 0;
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory) = 0;
    virtual RecordSet getUnsent() = 0;

    virtual void refreshID(int oldID, int newRecordId) = 0;
    virtual void saveDependants() = 0;
    virtual void setStatusToUnmodified(bool removeDeleted) = 0;
    virtual bool canBeDeleted(QVariant ID) = 0;

    virtual QString getSelectFromMainDB() = 0;

    virtual bool localRecordIsEqualsTo(RecordPtr record) = 0;

    virtual void setSentFlagIntoMemory() = 0;

protected:
    virtual bool addNew() = 0;
    virtual bool addNew(QTreeWidgetItem *item) = 0;
    virtual bool edit(QVariant ID) = 0;
    virtual bool edit(QTreeWidgetItem *item, QVariant ID) = 0;
    virtual bool deleteElement(QVariant ID) = 0;

signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);
    void dataUpdated();

public slots:

protected:
///DIEGO///
    //aca me parece que conviene desdoblar el abm a sqlite y a la db central
    //asi queda todo mas claro.

    /*virtual void deleteRecordsDB(bool includeSenderMachine);
    virtual void updateRecordsToDB(bool includeSenderMachine);
    virtual void addNewRecordsToDB(bool includeIDs, bool includeSenderMachine);*/

    virtual void deleteRecordsLocally();
    virtual void updateRecordsLocally();
    virtual void addNewRecordsLocally();

    virtual void deleteRecordsCentralDB();
    virtual void updateRecordsCentralDB();
    virtual void addNewRecordsCentralDB();

    virtual void executeCommand(QString cmd, RecordStatus status, bool impactLocalDatabase);
private:
    QString m_Name;
    QString m_InvariableName;
    SQLHandler sqlEngine;
    bool usesLastInsertedId;
    MERGE_STRATEGY m_MergeStrategy;
};

#endif // ACOLLECTION_H
