#include "empleado.h"
#include "datastore.h"

Empleado::Empleado(QObject *parent) :
    QObject(parent)
{
    idEmpleado.setNull();
    apellido.setNull();
    nombre.setNull();
    fechaIngreso.setNull();

    idEmpleado.reparent(this);
    apellido.reparent(this);
    nombre.reparent(this);
    fechaIngreso.reparent(this);

}

NullableField<int> Empleado::IDEmpleado()
{
    return idEmpleado;
}

NullableField<QString> Empleado::Apellido()
{
    return apellido;
}

NullableField<QString> Empleado::Nombre()
{
    return nombre;
}

NullableField<QString> Empleado::Legajo()
{
    return legajo;
}

NullableField<QDate> Empleado::FechaIngreso()
{
    return fechaIngreso;
}

void Empleado::IDEmpleado(NullableField<int> value)
{
    idEmpleado = value;
    idEmpleado.reparent(this);
}

void Empleado::Apellido(NullableField<QString> value)
{
    apellido = value;
    apellido.reparent(this);
}

void Empleado::Nombre(NullableField<QString> value)
{
    nombre = value;
    nombre.reparent(this);
}

void Empleado::Legajo(NullableField<QString> value)
{
    legajo = value;
    legajo.reparent(this);
}

void Empleado::FechaIngreso(NullableField<QDate> value)
{
    fechaIngreso = value;
    fechaIngreso.reparent(this);
}


CapacidadPersonaSectorLst Empleado::getCapacities()
{
    return DataStore::instance()->getCapacidades()->getAll(*IDEmpleado().value());
}

CalendarioPersonaLst Empleado::getDisponibilidad()
{
    return DataStore::instance()->getCalendarios()->getAll(*IDEmpleado().value());
}
