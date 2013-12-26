#ifndef PLANIFICACIONESDIASSUBSECTORES_H
#define PLANIFICACIONESDIASSUBSECTORES_H

#include "acollection.h"
#include "planificacionsubsector.h"

class PlanificacionesDiasSubSectores : public ACollection
{
    Q_OBJECT
public:
    explicit PlanificacionesDiasSubSectores(QObject *parent = 0);
    virtual QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual QString getTableName() { return "planificacionsubsector"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();


    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int oldID, int newID);
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);

    void updateWithOtherData(PlanificacionSubSectorLst other);

    PlanificacionSubSectorLst getAll(const QDate& Dia, bool includeDeleted);
    PlanificacionSubSectorLst getDiasAnterioresTrabajadosPorEmpleado(QDate Dia, int IDEmpleado);
    PlanificacionSubSectorLst getAll(const QDate& dateFrom, const QDate& dateTo);
signals:
    
public slots:
    
private:
    QMap<int, PlanificacionSubSectorPtr> m_Planificacion;
};

typedef boost::shared_ptr<PlanificacionesDiasSubSectores> PlanificacionesSubSectoresPtr;
#endif // PLANIFICACIONESDIASSUBSECTORES_H
