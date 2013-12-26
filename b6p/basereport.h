#ifndef BASEREPORT_H
#define BASEREPORT_H
#include <QObject>

#include "acollection.h"
#include <QMap>
#include "days.h"


class BaseReport : public ACollection
{
    Q_OBJECT
public:
    BaseReport(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent = 0);
    virtual ~BaseReport();

    virtual QString getSqlString();

    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr rercord, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge();
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc);


    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *);
    virtual bool addNewWithAdditionalData(QVariant);
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants();
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual bool canBeDeleted(QVariant ID);


    virtual QString getTableName();

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();


    virtual QString getSelectFromMainDB();

    virtual boost::shared_ptr<QList<QAction*> > getActions();

    virtual void refreshReport() = 0;

public slots:
    virtual void filter();
};

#endif // BASEREPORT_H
