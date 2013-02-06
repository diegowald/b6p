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

CapacidadPersonaSectorLst Empleado::Capacities()
{
    if (IDEmpleado().isNull())
        return CapacidadPersonaSectorLst(new QList<CapacidadPersonaSectorPtr>());
    else
        return DataStore::instance()->getCapacidades()->getAll(IDEmpleado().value());
}

void Empleado::updateCapacities(CapacidadPersonaSectorLst newCapacities)
{
    foreach (CapacidadPersonaSectorPtr c, *newCapacities)
    {
        DataStore::instance()->getCapacidades()->updateCapacityfromData(c);
    }
}

void Empleado::updateDisponibilidades(CalendarioPersonaLst newDisponibilidades)
{
    CalendarioPersonasPtr ptr = DataStore::instance()->getCalendarios();
    ptr->updateCalendarFromData(newDisponibilidades);
}

CalendarioPersonaLst Empleado::Disponibilidades()
{
    if (IDEmpleado().isNull() || IDEmpleado().value() == -1)
        return CalendarioPersonaLst(new QList<CalendarioPersonaPtr>());
    else
        return DataStore::instance()->getCalendarios()->getAll(IDEmpleado().value());
}

void Empleado::updateID(int newId)
{
    DataStore::instance()->getCalendarios()->updateCalendarWithNewIDEmpleado(-1, newId);


    CapacidadPersonaSectorLst cps = Capacities();
    foreach (CapacidadPersonaSectorPtr cs, *cps)
    {
        cs->updateIDEmpleado(newId);
    }

    IDEmpleado().setValue(newId);
    setUnmodified();
}
