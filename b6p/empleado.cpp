#include "empleado.h"

Empleado::Empleado(QObject *parent) :
    QObject(parent)
{
    idEmpleado.setNull();
    apellido.setNull();
    nombre.setNull();
    fechaIngreso.setNull();
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
}

void Empleado::Apellido(NullableField<QString> value)
{
    apellido = value;
}

void Empleado::Nombre(NullableField<QString> value)
{
    nombre = value;
}

void Empleado::Legajo(NullableField<QString> value)
{
    legajo = value;
}

void Empleado::FechaIngreso(NullableField<QDate> value)
{
    fechaIngreso = value;
}
