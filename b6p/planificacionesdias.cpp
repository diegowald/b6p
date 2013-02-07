#include "planificacionesdias.h"
#include "datastore.h"
#include "dlgselectorbytdate.h"
#include "dlgplanificaciondia.h"

PlanificacionesDias::PlanificacionesDias(QObject *parent) :
    ACollection(tr("Days Planifications"), false, parent)
{
}

QString PlanificacionesDias::getSqlString()
{
    return "select Dia, Notas, IDSupervisor from planificaciondia;";
}

void PlanificacionesDias::addRecord(Record &record)
{
    PlanificacionDiaPtr p(new PlanificacionDia(this));

    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch(record["Dia"].toLongLong()).date());
    p->Notas().setValue(record["Notas"].toString());
    p->IDSupervisor().setValue(record["IDSupervisor"].toInt());
    p->setInitialized();

    m_Planificaciones[p->Dia().value()] = p;
}

QString PlanificacionesDias::getDeleteStatement()
{
    return "delete from planificaciondia where Dia = :Dia;";
}

QString PlanificacionesDias::getUpdateStatement()
{
    return "update planificaciondia set Notas = :Notas, IDSupervisor = :IDSupervisor where Dia = :Dia;";
}

QString PlanificacionesDias::getInsertStatement()
{
    return "insert into planificaciondia "
            " (Dia, Notas, IDSupervisor) "
            " values "
            " (:Dia, :Notas, :IDSupervisor);";
}

RecordSet PlanificacionesDias::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        switch (status)
        {
        case NEW:
            if (p->isNew())
                res->push_back(p->asRecordPtr());
            break;
        case MODIFIED:
            if (p->isModified())
                res->push_back(p->asRecordPtr());
            break;
        case DELETED:
            if (p->isDeleted())
                res->push_back(p->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

void PlanificacionesDias::defineHeaders(QStringList &list)
{
    list << tr("Date") << tr("Supervisor")
         << tr("Notes") << tr("Estimated hours")
         << tr("Planned hours") << tr("Status");
}

void PlanificacionesDias::fillData(QTreeWidget &tree)
{
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, p->Dia().value().toString(Qt::TextDate));
        item->setData(0, Qt::UserRole, p->Dia().value());
        item->setText(1, p->Supervisor()->Apellido().value());
        item->setText(2, p->Notas().value());
        item->setText(3, QString::number(p->Estimacion()->EstimacionHoras().value()));
        item->setText(4, QString::number(p->HorasPlanificadas()));
        item->setText(5, p->Estado());
        tree.insertTopLevelItem(0, item);
    }
}

bool PlanificacionesDias::addNew()
{
    DlgSelectorBytDate dlg;
    EstimacionDiaLst diasSinEstimar = DataStore::instance()->getEstimacionesDias()->getUnplanned();
    QList<QDate> dias;
    foreach (EstimacionDiaPtr e, *diasSinEstimar)
    {
        dias.push_back(e->Dia().value());
    }

    dlg.setData(dias);
    dlg.setLabel(tr("Date"));
    dlg.setTitle(tr("Select a date to plan"));

    if (dlg.exec() == QDialog::Accepted)
    {
        QDate dia = dlg.selectedDay();
        return edit(dia);
    }
    return false;
}

bool PlanificacionesDias::edit(QVariant ID)
{
    PlanificacionDiaPtr p;
    p = getByDay(ID.toDate());
    if (!p.get())
        p = PlanificacionDiaPtr(new PlanificacionDia(ID.toDate(), this));

    DlgPlanificacionDia dlg;
    dlg.setData(p);
    if (dlg.exec() == QDialog::Accepted)
    {
/*        e->Apellido().setValue(dlg.Apellido());
        e->Nombre().setValue(dlg.Nombres());
        e->FechaIngreso().setValue(dlg.FechaIngreso());
        e->Legajo().setValue(dlg.Legajo());

        e->updateCapacities(dlg.Capacities());
        CalendarioPersonaLst disponibilidades = dlg.Disponibilidades();
        e->updateDisponibilidades(disponibilidades);

        m_Empleados[e->IDEmpleado().value()] = e;*/
        return true;
    }
    return false;
}

bool PlanificacionesDias::deleteElement(QVariant ID)
{
}

void PlanificacionesDias::refreshID(int newRecordId)
{
}

PlanificacionDiaLst PlanificacionesDias::getAll()
{
    PlanificacionDiaLst res(new QList<PlanificacionDiaPtr>());
    foreach (PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        res->push_back(p);
    }
    return res;
}

PlanificacionDiaPtr PlanificacionesDias::getByDay(QDate day)
{
    if (m_Planificaciones.find(day) == m_Planificaciones.end())
        return PlanificacionDiaPtr();
    else
        return m_Planificaciones[day];
}
