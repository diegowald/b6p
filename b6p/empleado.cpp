#include "empleado.h"
#include "datastore.h"
#include "days.h"
#include "timehelper.h"
#include<QsLog.h>

// Printing support
#include <QUrl>
#include "timeassignment.h"

EmployeeCalculatedCapacity::EmployeeCalculatedCapacity(Empleado* parentEmpleado, QDate Dia) :
    QObject(parentEmpleado)
{
    QLOG_TRACE() << "EmployeeCalculatedCapacity::EmployeeCalculatedCapacity(Empleado* parentEmpleado, QDate Dia)";
    empleado = parentEmpleado;
    capacityForTask = -1000;
    dia = Dia;
}

void EmployeeCalculatedCapacity::setCapacity(int value)
{
    QLOG_TRACE() << "void EmployeeCalculatedCapacity::setCapacity(int value)";
    capacityForTask = value;
}

Empleado* EmployeeCalculatedCapacity::EmpleadoAsignado()
{
    QLOG_TRACE() << "Empleado* EmployeeCalculatedCapacity::EmpleadoAsignado()";
    return empleado;
}

int EmployeeCalculatedCapacity::Capacity()
{
    QLOG_TRACE() << "int EmployeeCalculatedCapacity::Capacity()";
    return capacityForTask;
}

int EmployeeCalculatedCapacity::HorasPreviamenteTrabajadas()
{
    QLOG_TRACE() << "int EmployeeCalculatedCapacity::HorasPreviamenteTrabajadas()";
    int horas = 0;
    // Esta no es la mejor manera de obtener un valor, ya que se puede reescribir si eventualmente
    // se conecta a otro lugar, pero si se tiene en cuenta que un solo slot va a estar conectado, entonces
    // deberia funcionar.
    emit calcularHorasPreviamenteTrabajadas(empleado->IDEmpleado().value(), horas);
    return horas;
}

int EmployeeCalculatedCapacity::DiasPreviamenteTrabajados()
{
    QLOG_TRACE() << "int EmployeeCalculatedCapacity::DiasPreviamenteTrabajados()";
    PlanificacionSubSectorLst diasTrabajados =
            DataStore::instance()->getPlanificacionesSubSectores()
            ->getDiasAnterioresTrabajadosPorEmpleado(dia, empleado->IDEmpleado().value());

    return diasTrabajados->count();
}

bool EmployeeCalculatedCapacity::hasWarningsDias()
{
    QLOG_TRACE() << "bool EmployeeCalculatedCapacity::hasWarningsDias()";
    bool warningDias = (DiasPreviamenteTrabajados() > DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 0));
    return warningDias;
}

bool EmployeeCalculatedCapacity::hasWarningsHorasMenorAMinimo()
{
    QLOG_TRACE() << "bool EmployeeCalculatedCapacity::hasWarningsHorasMenorAMinimo()";
    bool warningHoras = (HorasPreviamenteTrabajadas() < DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MIN_HOURS, 0));
    return warningHoras;
}

bool EmployeeCalculatedCapacity::hasWarningsHorasMayorAMaximo()
{
    QLOG_TRACE() << "bool EmployeeCalculatedCapacity::hasWarningsHorasMayorAMaximo()";
    bool warningHoras = (HorasPreviamenteTrabajadas() > DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MAX_HOURS, 24));
    return warningHoras;
}

Empleado::Empleado(bool isNew, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE() << "Empleado::Empleado(bool isNew, QObject *parent)";
    if (isNew)
        idEmpleado.setValue(-1);
    else
        idEmpleado.setNull();
    apellido.setNull();
    nombre.setNull();
    fechaIngreso.setNull();
    isBaja.setNull();
    legajo.setNull();

    idEmpleado.setParent(this);
    apellido.setParent(this);
    nombre.setParent(this);
    fechaIngreso.setParent(this);
    isBaja.setParent(this);
    legajo.setParent(this);

    if (isNew)
        setNew();
}

RecordPtr Empleado::asRecordPtr()
{
    QLOG_TRACE() << "RecordPtr Empleado::asRecordPtr()";
    RecordPtr res = boost::make_shared<Record>();

    (*res)["Legajo"] = legajo.toVariant();
    (*res)["Apellido"] = apellido.toVariant();
    (*res)["Nombres"] = nombre.toVariant();
    (*res)["FechaIngreso"] = fechaIngreso.toVariant();
    (*res)["isBaja"] = isBaja.toVariant();
    (*res)["ID"] = idEmpleado.toVariant();

    (*res)[RECORD_ID] = idEmpleado.toVariant();
    return res;
}

bool Empleado::isEqualsTo(RecordPtr record)
{
    bool res = ((*record)["Legajo"] == legajo.toVariant())
            && ((*record)["Apellido"] == apellido.toVariant())
            && ((*record)["Nombres"] == nombre.toVariant())
            && ((*record)["FechaIngreso"] == fechaIngreso.toVariant())
            && ((*record)["isBaja"] == isBaja.toVariant());
    return res;
}

NullableField<int>& Empleado::IDEmpleado()
{
    QLOG_TRACE() << "NullableField<int>& Empleado::IDEmpleado()";
    return idEmpleado;
}

NullableField<QString>& Empleado::Apellido()
{
    QLOG_TRACE() << "NullableField<QString>& Empleado::Apellido()";
    return apellido;
}

NullableField<QString>& Empleado::Nombre()
{
    QLOG_TRACE() << "NullableField<QString>& Empleado::Nombre()";
    return nombre;
}

NullableField<QString>& Empleado::Legajo()
{
    QLOG_TRACE() << "NullableField<QString>& Empleado::Legajo()";
    return legajo;
}

NullableField<QDate>& Empleado::FechaIngreso()
{
    QLOG_TRACE() << "NullableField<QDate>& Empleado::FechaIngreso()";
    return fechaIngreso;
}

NullableField<bool>& Empleado::IsBaja()
{
    QLOG_TRACE() << "NullableField<bool>& Empleado::IsBaja()";
    return isBaja;
}

CapacidadPersonaSectorLst Empleado::Capacities()
{
    QLOG_TRACE() << "CapacidadPersonaSectorLst Empleado::Capacities()";
    if (IDEmpleado().isNull())
        return boost::make_shared<QList<CapacidadPersonaSectorPtr> >();
    else
        return DataStore::instance()->getCapacidades()->getAll(IDEmpleado().value(), false);
}

void Empleado::updateCapacities(CapacidadPersonaSectorLst newCapacities)
{
    QLOG_TRACE() << "void Empleado::updateCapacities(CapacidadPersonaSectorLst newCapacities)";
    CapacidadesPersonaSectorPtr ptr = DataStore::instance()->getCapacidades();
    ptr->updateCapacityfromData(newCapacities);
}

void Empleado::updateDisponibilidades(CalendarioPersonaLst newDisponibilidades)
{
    QLOG_TRACE() << "void Empleado::updateDisponibilidades(CalendarioPersonaLst newDisponibilidades)";
    CalendarioPersonasPtr ptr = DataStore::instance()->getCalendarios();
    ptr->updateCalendarFromData(newDisponibilidades);
}

CalendarioPersonaLst Empleado::Disponibilidades()
{
    QLOG_TRACE() << "CalendarioPersonaLst Empleado::Disponibilidades()";
    if (IDEmpleado().isNull() || IDEmpleado().value() == -1)
        return boost::make_shared<QList<CalendarioPersonaPtr> >();
    else
        return DataStore::instance()->getCalendarios()->getAll(IDEmpleado().value(), false);
}

void Empleado::updateID(int newId)
{
    QLOG_TRACE() << "void Empleado::updateID(int newId)";
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
    QLOG_TRACE() << "EmployeeCalculatedCapacityPtr Empleado::canWork(QDate &Fecha, int IDSector, int IDSubSector, int HoraInicio, int HoraFin)";
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
    QLOG_TRACE() << "bool Empleado::canBeDeleted()";
    return true;
}

bool Empleado::DadoDeBaja()
{
    QLOG_TRACE() << "bool Empleado::DadoDeBaja()";
    return IsBaja().isNull() ? false : IsBaja().value();
}

bool Empleado::isPowerUser()
{
    QLOG_TRACE() << "bool Empleado::isPowerUser()";
    // Devuelve true si el empleado esta en el grupo Gerencia o Supervisor
    CapacidadPersonaSectorPtr c = DataStore::instance()->getCapacidades()->get(idEmpleado.value(), 8, 0, false);
    if (c.get())
        return true;
    c = DataStore::instance()->getCapacidades()->get(idEmpleado.value(), 9, 0, false);
    return c.get();
}

bool Empleado::print(QTextDocument &textDoc)
{
    QLOG_TRACE() << "bool Empleado::print(QTextDocument &textDoc)";
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header

    html += "<tr>";
    html += "<td bgcolor=\"lightgray\" colspan=\"2\"><font size=\"+1\">";
    html += "<b><i>" + tr("Employee") + "</i></b></font>\n</td>";
    html += "</tr>";

    html += "<tr><td>" + tr("LastName") + "</td><td>" + Apellido().value() + "</td></tr>";
    html += "<tr><td>" + tr("Names") + "</td><td>" + Nombre().value() + "</td></tr>";
    html += "<tr><td>" + tr("ID") + "</td><td>" + Legajo().value() + "</td></tr>";
    html += "<tr><td>" + tr("Start Date") + "</td><td>" + FechaIngreso().value().toString() + "</td></tr>";
    html += "</table>";

    html += "<br>";

    CapacidadPersonaSectorLst capacidades = Capacities();

    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr><td colspan=\"4\" bgcolor=\"lightgray\"><font size=\"+1\"<b><i>" + tr("Expertise") + "</i></b></font></td></tr>";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Sector") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("SubSector") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Proficiency") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("") + "</i></font>\n</td>";
    html += "</tr>";

    foreach (CapacidadPersonaSectorPtr c, *capacidades) {
        html += "<tr>";
        if (c->getSector())
            html += "<td>" + c->getSector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        if (c->getSubSector())
            html += "<td>" + c->getSubSector()->Nombre().value() + "</td>";
        else
            html += "<td> </td>";

        html += "<td>" + QString::number(c->Capacidad().value()) + "</td>";

        html += "<td>" + tr("Diagram") + "</td>";
        html += "</tr>";
    }
    html += "\n</table>\n<br>\n";

    CalendarioPersonaLst calendarios = Disponibilidades();
    html += "<table width=\"100%\" border=1 cellspacing=0>\n";
    html += "<tr><td colspan=\"4\" bgcolor=\"lightgray\"><font size=\"+1\"<b><i>" + tr("Availability")  + "</i></b></font></td></tr>";
    html += "<tr>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Day") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("Start Time") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
    html += "<i>" + tr("End Time") + "</i></font>\n</td>";
    html += "<td bgcolor=\"lightgray\"><font size=\"+1\"><i></i></font>\n</td>";
    html += "</tr>";

    int imgNumber = 0;
    foreach (CalendarioPersonaPtr c, *calendarios) {
        html += "<tr>";
        html += "<td>" + Days::Days2String(Days::DayOfWeek2DAYS(c->Dia().value())) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraIngreso().value()) + "</td>";
        html += "<td>" + TimeHelper::SecondsToString(c->HoraEgreso().value()) + "</td>";
        QString img = "img%1";
        img = img.arg(imgNumber);
        html += "<td><img src=\"" + img + "\"></td>";

        QRect rect;
        rect.setWidth(500);
        rect.setHeight(30);
        QPixmap px(rect.size());
        TimeAssignment ts;
        ts.resize(rect.size());
        ts.setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
        ts.setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
        ts.setStartAssignment(c->HoraIngreso().value());
        ts.setEndAssignment(c->HoraEgreso().value());

        ts.setPaintBackgroundReferences(true);
        ts.setPaintVerticalGrid(true);
        ts.setShowBackgroundText(true);
        ts.setHollowTimeLine(true);
        ts.setTimeLineColor(Qt::black);

        ts.render(&px, QPoint(), QRegion(rect));
        textDoc.addResource(QTextDocument::ImageResource, QUrl(img), px);
        imgNumber++;
        html += "</tr>";
    }
    html += "\n</table>\n<br>\n";

    textDoc.setHtml(html);
    return true;
}
