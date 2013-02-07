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

bool Empleado::canWork(int Dia, int IDSector, int IDSubSector, QTime HoraInicio, QTime HoraFin)
{
    // Verifico si puede trabajar en el sector y subsector
    CapacidadPersonaSectorPtr cap =
            DataStore::instance()->getCapacidades()->get(idEmpleado.value(), IDSector, IDSubSector);
    if (cap.get() == NULL)
        return false;

    // Verfico si puede trabajar el dia en la franja horaria.
    CalendarioPersonaPtr cal = DataStore::instance()->getCalendarios()->get(
                idEmpleado.value(), Dia, HoraInicio, HoraFin);
    if (cal.get() == NULL)
        return false;
}
