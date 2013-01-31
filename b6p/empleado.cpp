#include "empleado.h"
#include "datastore.h"

Empleado::Empleado(bool isNew, QObject *parent) :
    QObject(parent)
{
    if (isNew)
        idEmpleado.setValue(-1);
    else
        idEmpleado.setNull();
    apellido.setNull();
    nombre.setNull();
    fechaIngreso.setNull();

    idEmpleado.setParent(this);
    apellido.setParent(this);
    nombre.setParent(this);
    fechaIngreso.setParent(this);

    if (isNew)
        setNew();
}

RecordPtr Empleado::asRecordPtr()
{
    RecordPtr res(new Record());

    (*res)["ID"] = idEmpleado.toVariant();
    (*res)["Apellido"] = apellido.toVariant();
    (*res)["Nombres"] = nombre.toVariant();
    (*res)["FechaIngreso"] = fechaIngreso.toVariant();

    return res;
}

NullableField<int>& Empleado::IDEmpleado()
{
    return idEmpleado;
}

NullableField<QString>& Empleado::Apellido()
{
    return apellido;
}

NullableField<QString>& Empleado::Nombre()
{
    return nombre;
}

NullableField<QString>& Empleado::Legajo()
{
    return legajo;
}

NullableField<QDate>& Empleado::FechaIngreso()
{
    return fechaIngreso;
}

/*void Empleado::IDEmpleado(NullableField<int> value)
{
    idEmpleado.setValue(value);
}

void Empleado::Apellido(NullableField<QString> value)
{
    apellido.setValue(value);
}

void Empleado::Nombre(NullableField<QString> value)
{
    nombre.setValue(value);
}

void Empleado::Legajo(NullableField<QString> value)
{
    legajo.setValue(value);
}

void Empleado::FechaIngreso(NullableField<QDate> value)
{
    fechaIngreso.setValue(value);
}
*/

CapacidadPersonaSectorLst Empleado::getCapacities()
{
    if (IDEmpleado().isNull())
        return CapacidadPersonaSectorLst(new QList<CapacidadPersonaSectorPtr>());
    else
        return DataStore::instance()->getCapacidades()->getAll(IDEmpleado().value());
}

CalendarioPersonaLst Empleado::getDisponibilidad()
{
    if (IDEmpleado().isNull())
        return CalendarioPersonaLst(new QList<CalendarioPersonaPtr>());
    else
        return DataStore::instance()->getCalendarios()->getAll(IDEmpleado().value());
}
