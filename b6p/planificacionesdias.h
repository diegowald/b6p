#ifndef PLANIFICACIONESDIAS_H
#define PLANIFICACIONESDIAS_H

#include "acollection.h"
#include "planificaciondia.h"

class PlanificacionesDias : public ACollection
{
    Q_OBJECT
public:
    explicit PlanificacionesDias(QObject *parent = 0);
    virtual QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc);

    virtual QString getTableName() { return "planificaciondia"; }
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement(bool IncludeIDs);
    virtual RecordSet getRecords(RecordStatus status);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants();
    virtual void setStatusToUnmodified(bool removeDeleted);
    virtual boost::shared_ptr<QList<QAction*> > getActions();

    PlanificacionDiaLst getAll(bool includeDeleted);
    PlanificacionDiaPtr getByDay(QDate day, bool includeDeleted);
    PlanificacionDiaLst getAllReadyForApproval();
signals:
    
public slots:
    
private:
    QMap<QDate, PlanificacionDiaPtr> m_Planificaciones;
};

typedef boost::shared_ptr<PlanificacionesDias> PlanificacionesDiasPtr;
#endif // PLANIFICACIONESDIAS_H
