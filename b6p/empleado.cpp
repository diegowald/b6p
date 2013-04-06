#include "empleado.h"
#include "datastore.h"

EmployeeCalculatedCapacity::EmployeeCalculatedCapacity(Empleado* parentEmpleado, QDate Dia) :
    QObject(parentEmpleado)
{
    empleado = parentEmpleado;
    capacityForTask = -1000;
    dia = Dia;
}

void EmployeeCalculatedCapacity::setCapacity(int value)
{
    capacityForTask = value;
}

Empleado* EmployeeCalculatedCapacity::EmpleadoAsignado()
{
    return empleado;
}

int EmployeeCalculatedCapacity::Capacity()
{
    return capacityForTask;
}

int EmployeeCalculatedCapacity::HorasPreviamenteTrabajadas()
{
#warning terminar esta funcion
    int horas = 0;
    // Esta no es la mejor manera de obtener un valor, ya que se puede reescribir si eventualmente
    // se conecta a otro lugar, pero si se tiene en cuenta que un solo slot va a estar conectado, entonces
    // deberia funcionar.
    emit calcularHorasPreviamenteTrabajadas(empleado->IDEmpleado().value(), horas);
    return horas;
}

int EmployeeCalculatedCapacity::DiasPreviamenteTrabajados()
{
    PlanificacionSubSectorLst diasTrabajados =
            DataStore::instance()->getPlanificacionesSubSectores()
            ->getDiasAnterioresTrabajadosPorEmpleado(dia, empleado->IDEmpleado().value());

    return diasTrabajados->count();
}

bool EmployeeCalculatedCapacity::hasWarningsDias()
{
    bool warningDias = (DiasPreviamenteTrabajados() > DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 0));
    qDebug() << "Warning Dias: " << warningDias;
    return warningDias;
}

bool EmployeeCalculatedCapacity::hasWarningsHoras()
{
    bool warningHoras = (HorasPreviamenteTrabajadas() < DataStore::instance()->getParametros()->getValue(Parametros::MIN_WORKING_HOURS, 0));
    qDebug() << "Warning Horas: " << warningHoras;
    return warningHoras;
}


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
    isBaja.setNull();

    idEmpleado.setParent(this);
    apellido.setParent(this);
    nombre.setParent(this);
    fechaIngreso.setParent(this);
    isBaja.setParent(this);

    if (isNew)
        setNew();
}

RecordPtr Empleado::asRecordPtr()
{
    RecordPtr res = boost::make_shared<Record>();

    (*res)["Legajo"] = idEmpleado.toVariant();
    (*res)["Apellido"] = apellido.toVariant();
    (*res)["Nombres"] = nombre.toVariant();
    (*res)["FechaIngreso"] = fechaIngreso.toVariant();
    (*res)["isBaja"] = isBaja.toVariant();

    (*res)[RECORD_ID] = idEmpleado.toVariant();
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

NullableField<bool>& Empleado::IsBaja()
{
    return isBaja;
}

CapacidadPersonaSectorLst Empleado::Capacities()
{
    if (IDEmpleado().isNull())
        return boost::make_shared<QList<CapacidadPersonaSectorPtr> >();
    else
        return DataStore::instance()->getCapacidades()->getAll(IDEmpleado().value(), false);
}

void Empleado::updateCapacities(CapacidadPersonaSectorLst newCapacities)
{
    CapacidadesPersonaSectorPtr ptr = DataStore::instance()->getCapacidades();
    ptr->updateCapacityfromData(newCapacities);
}

void Empleado::updateDisponibilidades(CalendarioPersonaLst newDisponibilidades)
{
    CalendarioPersonasPtr ptr = DataStore::instance()->getCalendarios();
    ptr->updateCalendarFromData(newDisponibilidades);
}

CalendarioPersonaLst Empleado::Disponibilidades()
{
    if (IDEmpleado().isNull() || IDEmpleado().value() == -1)
        return boost::make_shared<QList<CalendarioPersonaPtr> >();
    else
        return DataStore::instance()->getCalendarios()->getAll(IDEmpleado().value(), false);
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

EmployeeCalculatedCapacityPtr Empleado::canWork(QDate &Fecha, int IDSector, int IDSubSector, int HoraInicio, int HoraFin)
{
    EmployeeCalculatedCapacityPtr res = boost::make_shared<EmployeeCalculatedCapacity>(this, Fecha);
    // Verifico si puede trabajar en el sector y subsector
    CapacidadPersonaSectorPtr cap =
            DataStore::instance()->getCapacidades()->get(idEmpleado.value(), IDSector, IDSubSector, false);
    if (cap.get() == NULL)
    {
        res->setCapacity(0);
        return res;
    }


    // Verifico si puede trabajar el dia en la franja horaria.
    DAYS Dia = Days::DayOfWeek2DAYS(Fecha.dayOfWeek());
    CalendarioPersonaPtr cal = DataStore::instance()->getCalendarios()->get(
                idEmpleado.value(), Dia, HoraInicio, HoraFin, false);

    // Aca pueden darse varios casos. POr ahora solo vamos a contemplar que el empleado
    // efectivamente pueda trabajar en esa franja horaria.

    if (cal.get() == NULL)
    {
        res->setCapacity(0);
        return res;
    }

    if (cap.get() != NULL)
        res->setCapacity(cap->Capacidad().value()); // A esto habria que afectarlo

    return res;
}

bool Empleado::canBeDeleted()
{
    return true;
}

bool Empleado::DadoDeBaja()
{
    return IsBaja().isNull() ? false : IsBaja().value();
}
