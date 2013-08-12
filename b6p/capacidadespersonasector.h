#ifndef CAPACIDADESPERSONASECTOR_H
#define CAPACIDADESPERSONASECTOR_H

#include <QObject>
#include "acollection.h"
#include "capacidadpersonasector.h"

class CapacidadesPersonaSector : public ACollection
{
    Q_OBJECT
public:
    explicit CapacidadesPersonaSector(QObject *parent = 0);

    QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual QString getTableName() { return "capacidadespersonassector"; }

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
    virtual bool addNew(QTreeWidgetItem *) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false; }
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);

    CapacidadPersonaSectorLst getAll(int IDEmpleado, bool includeDeleted);
    void updateCapacityfromData(CapacidadPersonaSectorLst dataFrom);

    CapacidadPersonaSectorPtr get(int idEmpleado, int IDSector, int IDSubSector, bool includeDeleted);
signals:
    
public slots:
    
private:
    QList<CapacidadPersonaSectorPtr> m_Capacidades;
};

typedef boost::shared_ptr<CapacidadesPersonaSector> CapacidadesPersonaSectorPtr;

#endif // CAPACIDADESPERSONASECTOR_H
