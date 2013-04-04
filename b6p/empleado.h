#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QObject>
#include <boost/shared_ptr.hpp>

#include "nullablefield.h"
#include <QDate>

#include "capacidadpersonasector.h"
#include "calendariopersona.h"
#include "days.h"


class Empleado;
typedef boost::shared_ptr<Empleado> EmpleadoPtr;
typedef boost::shared_ptr<QList<EmpleadoPtr> > EmpleadosLst;

class EmployeeCalculatedCapacity : public QObject
{
    Q_OBJECT
public:
    explicit EmployeeCalculatedCapacity(Empleado* parentEmpleado, QObject *parent = 0);

    void setCapacity(int value);

    Empleado *EmpleadoAsignado();
    int Capacity();
    int HorasPreviamenteTrabajadas();
    int DiasPreviamenteTrabajados();

    bool hasWarnings();
signals:

public slots:

private:
    Empleado* empleado;
    int capacityForTask;
};

typedef boost::shared_ptr<EmployeeCalculatedCapacity> EmployeeCalculatedCapacityPtr;
typedef boost::shared_ptr<QList<EmployeeCalculatedCapacityPtr> > EmployeeCalculatedCapacityLst;

class Empleado : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit Empleado(bool isNew, QObject *parent = 0);
    
    void updateID(int newId);
    NullableField<int> &IDEmpleado();
    NullableField<QString> &Apellido();
    NullableField<QString> &Nombre();
    NullableField<QString> &Legajo();
    NullableField<QDate> &FechaIngreso();
    NullableField<bool> &IsBaja();

    CapacidadPersonaSectorLst Capacities();
    void updateCapacities(CapacidadPersonaSectorLst newCapacities);
    CalendarioPersonaLst Disponibilidades();
    void updateDisponibilidades(CalendarioPersonaLst newDisponibilidades);

    virtual RecordPtr asRecordPtr();

    bool DadoDeBaja();
    EmployeeCalculatedCapacityPtr canWork(DAYS Dia, int IDSector, int IDSubSector, int HoraInicio, int HoraFin);
    bool canBeDeleted();

signals:
    
public slots:
    
private:
    NullableField<int> idEmpleado;
    NullableField<QString> apellido;
    NullableField<QString> nombre;
    NullableField<QString> legajo;
    NullableField<QDate> fechaIngreso;
    NullableField<bool> isBaja;
};


#endif // EMPLEADO_H
