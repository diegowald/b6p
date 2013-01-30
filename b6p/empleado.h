#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QObject>
#include <boost/shared_ptr.hpp>

#include "nullablefield.h"
#include <QDate>

#include "capacidadpersonasector.h"
#include "calendariopersona.h"

class Empleado : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit Empleado(bool isNew = false, QObject *parent = 0);
    
    NullableField<int> &IDEmpleado();
    NullableField<QString> &Apellido();
    NullableField<QString> &Nombre();
    NullableField<QString> &Legajo();
    NullableField<QDate> &FechaIngreso();

    /*void IDEmpleado(NullableField<int> value);
    void Apellido(NullableField<QString> value);
    void Nombre(NullableField<QString> value);
    void Legajo(NullableField<QString> value);
    void FechaIngreso(NullableField<QDate> value);*/

    CapacidadPersonaSectorLst getCapacities();
    CalendarioPersonaLst getDisponibilidad();

    virtual RecordPtr asRecordPtr();

signals:
    
public slots:
    
private:
    NullableField<int> idEmpleado;
    NullableField<QString> apellido;
    NullableField<QString> nombre;
    NullableField<QString> legajo;
    NullableField<QDate> fechaIngreso;
};

typedef boost::shared_ptr<Empleado> EmpleadoPtr;
typedef boost::shared_ptr<QList<EmpleadoPtr> > EmpleadosLst;

#endif // EMPLEADO_H
