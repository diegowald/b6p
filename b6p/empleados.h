#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <QObject>

#include "acollection.h"
#include "empleado.h"
#include <QMap>
#include "days.h"

class Empleados : public ACollection
{
    Q_OBJECT
public:
    explicit Empleados(QObject *parent = 0);
    virtual ~Empleados();
    virtual QString getSqlString();

    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge();
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc);


    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants();
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual bool canBeDeleted(QVariant ID);


    virtual QString getTableName() { return "empleados"; }

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

    EmpleadoPtr getEmpleado(int idEmpleado, bool includeDeleted);
    EmpleadosLst getAll(bool includeDeleted);
    EmpleadosLst getPowerUsers();
    EmployeeCalculatedCapacityLst getAll(int IDSector, int IDSubSector, QDate Fecha, int HoraInicio, int HoraFin, bool includeDeleted);
signals:
    
public slots:

private:
    QMap<int, EmpleadoPtr> m_Empleados;
};

typedef boost::shared_ptr<Empleados> EmpleadosPtr;
#endif // EMPLEADOS_H
