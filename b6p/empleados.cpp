#include "empleados.h"
#include "genericlist.h"
#include "dlgemployee.h"
#include "datastore.h"

Empleados::Empleados(QObject *parent) :
    ACollection(tr("Employees"), "Employees", true, parent)
{
}

Empleados::~Empleados()
{
}

QString Empleados::getSelectFromMainDB()
{
    return QString("select ID, Apellido, Nombres, Legajo, FechaIngreso, isBaja, Estado from empleados "
                   " where LastUpdate >= :LASTUPDATE;");
}

QString Empleados::getSqlString()
{
    return QString("select ID, Apellido, Nombres, Legajo, FechaIngreso, isBaja from empleados")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void Empleados::addRecord(RecordPtr record)
{
    EmpleadoPtr e = boost::make_shared<Empleado>(false, this);
    e->IDEmpleado().setValue((*record)["ID"].toInt());
    e->Apellido().setValue((*record)["Apellido"].toString());
    e->Nombre().setValue((*record)["Nombres"].toString());
    e->Legajo().setValue((*record)["Legajo"].toString());
    e->FechaIngreso().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaIngreso"].toLongLong()).date());
    e->IsBaja().setValue((*record)["isBaja"].toBool());
    e->setInitialized();
    m_Empleados[e->IDEmpleado().value()] = e;
}

QString Empleados::getDeleteStatement()
{
    return QString("update empleados set isBaja = 1, RecordStatus = %1 where ID = :ID;").arg(RECORD_MODIFIED);
}

QString Empleados::getUpdateStatement()
{
    return QString("update empleados set Apellido = :Apellido, Nombres = :Nombres, "
                   " Legajo = :Legajo, FechaIngreso = :FechaIngreso, RecordStatus = %1  where ID = :ID;").arg(RECORD_MODIFIED);
}

QString Empleados::getInsertStatement()
{
    return QString("insert into empleados (Apellido, Nombres, Legajo, FechaIngreso, RecordStatus, isBaja) "
            " values "
            "(:Apellido, :Nombres, :Legajo, :FechaIngreso, %1, 0);").arg(RECORD_NEW);
}

RecordSet Empleados::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
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

EmpleadoPtr Empleados::getEmpleado(int idEmpleado, bool includeDeleted)
{
    if (m_Empleados.find(idEmpleado) == m_Empleados.end())
        return EmpleadoPtr();
    else
    {
        EmpleadoPtr e = m_Empleados[idEmpleado];
        if (e->DadoDeBaja() && !includeDeleted)
            return EmpleadoPtr();
        return e;
    }
}

EmpleadosLst Empleados::getAll(bool includeDeleted)
{
    EmpleadosLst res = boost::make_shared<QList<EmpleadoPtr> >();
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        if (!e->DadoDeBaja())
            res->push_back(e);
        else
            if (includeDeleted)
                res->push_back(e);
    }

    return res;
}

EmpleadosLst Empleados::getAll(int IDSector, int IDSubSector, DAYS Dia, int HoraInicio, int HoraFin, bool includeDeleted)
{
    EmpleadosLst res = boost::make_shared<QList<EmpleadoPtr> >();
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        if (e->canWork(Dia, IDSector, IDSubSector, HoraInicio, HoraFin))
        {
            if (!e->isDeleted())
                res->push_back(e);
            else
                if (includeDeleted)
                    res->push_back(e);
        }
    }
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
    tree.clear();
    EmpleadosLst emps = getAll(false);
    foreach(EmpleadoPtr emp, *emps)
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
        e = boost::make_shared<Empleado>(true, this);
    else
        e = getEmpleado(ID.toInt(), false);
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

bool Empleados::canBeDeleted(QVariant ID)
{
    bool result = false;
    if (m_Empleados.find(ID.toInt()) != m_Empleados.end())
    {
        result = m_Empleados[ID.toInt()]->canBeDeleted();
    }
    return result;
}

bool Empleados::deleteElement(QVariant ID)
{
    bool result = false;
    if (m_Empleados.find(ID.toInt()) != m_Empleados.end())
    {
        m_Empleados[ID.toInt()]->setDeleted();
        result = true;
    }
    return result;
}

void Empleados::refreshID(int oldID, int newRecordId)
{
    EmpleadoPtr e = m_Empleados[oldID];
    e->updateID(newRecordId);
    m_Empleados.remove(oldID);
    m_Empleados[newRecordId] = e;    
}

void Empleados::saveDependants()
{
    DataStore::instance()->getCapacidades()->save();
    DataStore::instance()->getCalendarios()->save();
}

void Empleados::setStatusToUnmodified(bool removeDeleted)
{
    QList<int> toDelete;
    foreach (EmpleadoPtr e, m_Empleados.values())
    {
        if (removeDeleted && e->isDeleted())
            toDelete.push_back(e->IDEmpleado().value());
        else
            e->setUnmodified();
    }
    foreach(int id, toDelete)
        m_Empleados.remove(id);
}
