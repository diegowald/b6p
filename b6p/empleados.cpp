#include "empleados.h"
#include "genericlist.h"
#include "dlgemployee.h"

Empleados::Empleados(QObject *parent) :
    ACollection(tr("Employees"), parent)
{
}

Empleados::~Empleados()
{
}

QString Empleados::getSqlString()
{
    return "select ID, Apellido, Nombres, Legajo, FechaIngreso from empleados";
}

void Empleados::addRecord(Record &record)
{
    EmpleadoPtr e(new Empleado(false, this));
    e->IDEmpleado().setValue(record["ID"].toInt());
    e->Apellido().setValue(record["Apellido"].toString());
    e->Nombre().setValue(record["Nombres"].toString());
    e->Legajo().setValue(record["Legajo"].toString());
    e->FechaIngreso().setValue(QDateTime::fromMSecsSinceEpoch(record["FechaIngreso"].toLongLong()).date());
    e->setInitialized();
    m_Empleados[e->IDEmpleado().value()] = e;
}

QString Empleados::getDeleteStatement()
{
    return "delete from empleados where ID = :ID;";
}

QString Empleados::getUpdateStatement()
{
    return "update empleados set Apellido = :Apellido, Nombres = :Nombres, "
            " Legajo = :Legajo, FechaIngreso = :FechaIngreso where ID = :ID;";
}

QString Empleados::getInsertStatement()
{
    return "insert into empleados (Apellido, Nombres, Legajo, FechaIngreso) "
            " values "
            "(:Apellido, :Nombres, :Legajo, :FechaIngreso);";
}

RecordSet Empleados::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        switch (status)
        {
        case NEW:
            if (e->isNew())
                res->push_back(e->asRecordPtr());
            break;
        case MODIFIED:
            if (e->isModified())
                res->push_back(e->asRecordPtr());
            break;
        case DELETED:
            if (e->isDeleted())
                res->push_back(e->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

EmpleadoPtr Empleados::getEmpleado(int idEmpleado)
{
    if (m_Empleados.find(idEmpleado) == m_Empleados.end())
        return EmpleadoPtr();
    else
        return m_Empleados[idEmpleado];
}

EmpleadosLst Empleados::getAll()
{
    EmpleadosLst res(new QList<EmpleadoPtr>(m_Empleados.values()));
    return res;
}

void Empleados::defineHeaders(QStringList &list)
{
    list << tr("Lastname")
            << tr("Firstname")
            << tr("ID")
            << tr("Start");
}

void Empleados::fillData(QTreeWidget &tree)
{
    foreach(EmpleadoPtr emp, m_Empleados)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, emp->Apellido().value());
        item->setData(0, Qt::UserRole, emp->IDEmpleado().value());
        item->setText(1, emp->Nombre().value());
        item->setText(2, emp->Legajo().value());
        item->setText(3, emp->FechaIngreso().value().toString(Qt::TextDate));
        tree.insertTopLevelItem(0, item);
    }
}

bool Empleados::addNew()
{
    int id = -1;
    return edit(id);
}

bool Empleados::edit(QVariant ID)
{
    EmpleadoPtr e;
    if (ID == -1)
        e = EmpleadoPtr(new Empleado(true, this));
    else
        e = getEmpleado(ID.toInt());
    DlgEmployee dlg;
    dlg.setData(e);
    if (dlg.exec() == QDialog::Accepted)
    {
        e->Apellido().setValue(dlg.Apellido());
        e->Nombre().setValue(dlg.Nombres());
        e->FechaIngreso().setValue(dlg.FechaIngreso());
        e->Legajo().setValue(dlg.Legajo());

        e->updateCapacities(dlg.Capacities());
        CalendarioPersonaLst disponibilidades = dlg.Disponibilidades();
        e->updateDisponibilidades(disponibilidades);

        m_Empleados[e->IDEmpleado().value()] = e;
        return true;
    }
    return false;
}

bool Empleados::deleteElement(QVariant ID)
{
}
