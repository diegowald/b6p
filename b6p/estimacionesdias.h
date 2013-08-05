#ifndef ESTIMACIONESDIAS_H
#define ESTIMACIONESDIAS_H

#include "acollection.h"
#include <QMap>
#include "estimaciondia.h"

class EstimacionesDias : public ACollection
{
    Q_OBJECT
public:
    EstimacionesDias(QObject *parent = 0);
    virtual QString getSqlString();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual QString getTableName() { return "planificaciondias"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();
    virtual void setSentFlagIntoMemory();


    virtual QString getSelectFromMainDB();

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool isColumnEditable(QVariant ID, int column);
    virtual boost::shared_ptr<QList<QAction *> > getActions();

    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *item);
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *item, QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted);

    EstimacionDiaLst getAll(bool includeDeleted);
    EstimacionDiaPtr get(QDate dia, bool includeDeleted);
    EstimacionDiaLst getUnplanned(bool includeDeleted);

public slots:
    void addManyDays();
    void approveSelected();

private:
    QMap<QDate, EstimacionDiaPtr> m_Estimaciones;
};

typedef boost::shared_ptr<EstimacionesDias> EstimacionesDiasPtr;
#endif // ESTIMACIONESDIAS_H
