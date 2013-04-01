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
    void addRecord(RecordPtr record);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);

    virtual QString getTableName() { return "capacidadespersonassector"; }
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement(bool IncludeIDs);
    virtual RecordSet getRecords(RecordStatus status);\
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
    virtual void setStatusToUnmodified(bool removeDeleted);

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
