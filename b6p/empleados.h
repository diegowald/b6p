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

    virtual void addRecord(RecordPtr record);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);


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
    virtual void setStatusToUnmodified(bool removeDeleted);
    virtual bool canBeDeleted(QVariant ID);


    virtual QString getTableName() { return "empleados"; }
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement(bool IncludeIDs);
    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status);
    virtual RecordSet getUnsent();

    virtual QString getSelectFromMainDB();

    EmpleadoPtr getEmpleado(int idEmpleado, bool includeDeleted);
    EmpleadosLst getAll(bool includeDeleted);
    EmpleadosLst getAll(int IDSector, int IDSubSector, DAYS Dia, int HoraInicio, int HoraFin, bool includeDeleted);
signals:
    
public slots:

private:
    QMap<int, EmpleadoPtr> m_Empleados;
};

typedef boost::shared_ptr<Empleados> EmpleadosPtr;
#endif // EMPLEADOS_H
