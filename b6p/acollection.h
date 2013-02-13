#ifndef ACOLLECTION_H
#define ACOLLECTION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <QTreeWidget>
#include "sqlhandler.h"
#include "IRecord.h"


class ACollection : public QObject
{
    Q_OBJECT
public:
    explicit ACollection(QString Name, bool useLastInsertId, QObject *parent = 0);
    
    virtual void load();
    virtual void save();

    QString name() const;

    virtual QString getSqlString() = 0;
    virtual void addRecord(Record &record) = 0;

    virtual void defineHeaders(QStringList &list) = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool addNewRecord();
    virtual bool addNew() = 0;
    virtual bool editRecord(QVariant ID);
    virtual bool edit(QVariant ID) = 0;
    bool deleteRecord(QVariant ID);
    virtual bool deleteElement(QVariant ID) = 0;

    virtual QString getDeleteStatement() = 0;
    virtual QString getUpdateStatement() = 0;
    virtual QString getInsertStatement() = 0;
    virtual RecordSet getRecords(RecordStatus status) = 0;
    virtual void refreshID(int newRecordId) = 0;
    virtual void saveDependants() = 0;
    virtual void setStatusToUnmodified() = 0;

signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);
    
public slots:

protected:
    virtual void deleteRecordsDB();
    virtual void updateRecordsToDB();
    virtual void addNewRecordsToDB();
    virtual void executeCommand(QString cmd, RecordStatus status);
private:
    QString m_Name;
    SQLHandler sqlEngine;
    bool usesLastInsertedId;
};

#endif // ACOLLECTION_H
