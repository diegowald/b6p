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
    virtual void addRecord(Record &record);
    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool edit(QVariant ID);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int newRecordId);
    virtual void saveDependants();
    virtual void setStatusToUnmodified();


    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);

    EmpleadoPtr getEmpleado(int idEmpleado);
    EmpleadosLst getAll();
    EmpleadosLst getAll(int IDSector, int IDSubSector, DAYS Dia, int HoraInicio, int HoraFin);
signals:
    
public slots:

private:
    QMap<int, EmpleadoPtr> m_Empleados;
};

typedef boost::shared_ptr<Empleados> EmpleadosPtr;
#endif // EMPLEADOS_H
