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
    explicit ACollection(QString Name, bool useLastInsertId, QObject *parent = 0);
    
    virtual void load();
    virtual void save();

    QString name() const;

    virtual QString getSqlString() = 0;
    virtual void addRecord(Record &record) = 0;

    virtual void defineHeaders(QStringList &list) = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool isColumnEditable(int column) { return false; }
    virtual boost::shared_ptr<QList<QAction*> > getActions() { return boost::make_shared<QList<QAction*> >(); }
    bool addNewRecord();
    bool addNewRecord(QTreeWidgetItem *item);
    bool editRecord(QVariant ID);
    bool editRecord(QTreeWidgetItem *item, QVariant ID);
    bool deleteRecord(QVariant ID);


    virtual QString getDeleteStatement() = 0;
    virtual QString getUpdateStatement() = 0;
    virtual QString getInsertStatement() = 0;
    virtual RecordSet getRecords(RecordStatus status) = 0;
    virtual void refreshID(int newRecordId) = 0;
    virtual void saveDependants() = 0;
    virtual void setStatusToUnmodified() = 0;

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
