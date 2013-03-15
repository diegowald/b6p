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
    virtual void addRecord(RecordPtr record);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);

    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int oldID, int newID);
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted);

    void updateWithOtherData(PlanificacionSubSectorLst other);

    PlanificacionSubSectorLst getAll(QDate Dia, bool includeDeleted);
signals:
    
public slots:
    
private:
    QMap<int, PlanificacionSubSectorPtr> m_Planificacion;
};

typedef boost::shared_ptr<PlanificacionesDiasSubSectores> PlanificacionesSubSectoresPtr;
#endif // PLANIFICACIONESDIASSUBSECTORES_H
