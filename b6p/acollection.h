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

    explicit ACollection(QString Name, QString InvariableName, bool useLastInsertId, QObject *parent = 0);
    
    virtual void exportTo(const QString &filename);
    virtual void load();
    virtual void save(bool includeIDs = false);

    QString &name();
    QString invariableName() const;

    virtual QString suggestedFileName() { return name(); }
    virtual QString getSqlString() = 0;
    virtual void addRecord(RecordPtr record, bool setNew = false) = 0;

    virtual bool exists(RecordPtr record) = 0;
    virtual void updateRecord(RecordPtr record) = 0;
    virtual void deleteRecord(RecordPtr record) = 0;

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
    virtual QString getDeleteStatement() = 0;
    virtual QString getUpdateStatement() = 0;
    virtual QString getInsertStatement(bool IncludeIDs) = 0;
    virtual QString getSQLExistsInMainDB() = 0;
    virtual RecordSet getRecords(RecordStatus status) = 0;
    virtual RecordSet getUnsent() = 0;

    virtual void refreshID(int oldID, int newRecordId) = 0;
    virtual void saveDependants() = 0;
    virtual void setStatusToUnmodified(bool removeDeleted) = 0;
    virtual bool canBeDeleted(QVariant ID) = 0;

    virtual QString getSelectFromMainDB() = 0;

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
    virtual void deleteRecordsDB();
    virtual void updateRecordsToDB();
    virtual void addNewRecordsToDB(bool includeIDs);
    virtual void executeCommand(QString cmd, RecordStatus status);
private:
    QString m_Name;
    QString m_InvariableName;
    SQLHandler sqlEngine;
    bool usesLastInsertedId;
};

#endif // ACOLLECTION_H
