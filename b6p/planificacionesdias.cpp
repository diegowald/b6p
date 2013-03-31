#include "planificacionesdias.h"
#include "datastore.h"
#include "dlgselectorbytdate.h"
#include "dlgplanificaciondia.h"

PlanificacionesDias::PlanificacionesDias(QObject *parent) :
    ACollection(tr("Days Planifications"),
                "Days Planifications", false, parent)
{
}

QString PlanificacionesDias::getSelectFromMainDB()
{
    return QString("select Dia, Notas, IDSupervisor, LastUpdate from planificaciondia "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString PlanificacionesDias::getSqlString()
{
    return QString("select Dia, Notas, IDSupervisor, sent from planificaciondia ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString PlanificacionesDias::getSQLExistsInMainDB()
{
    return QString("select Dia, Notas, IDSupervisor from planificaciondia where Dia = :Dia;");
}

void PlanificacionesDias::addRecord(RecordPtr record)
{
    PlanificacionDiaPtr p = boost::make_shared<PlanificacionDia>(this);

    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->Notas().setValue((*record)["Notas"].toString());
    p->IDSupervisor().setValue((*record)["IDSupervisor"].toInt());
    p->setSentStatus((*record)["sent"].toInt() == 1);
    p->setInitialized();

    m_Planificaciones[p->Dia().value()] = p;
}

void PlanificacionesDias::updateRecord(RecordPtr record)
{
    PlanificacionDiaPtr p = m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];

    p->Notas().setValue((*record)["Notas"].toString());
    p->IDSupervisor().setValue((*record)["IDSupervisor"].toInt());

}

void PlanificacionesDias::deleteRecord(RecordPtr record)
{
    m_Planificaciones.remove(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
}

bool PlanificacionesDias::exists(RecordPtr record)
{
    return (PlanificacionDiaPtr() != m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()]);
}

QString PlanificacionesDias::getDeleteStatement()
{
    return QString("update planificaciondia "
                   " set RecordStatus = %1 "
                   " where Dia = :Dia;").arg(RECORD_DELETED);
}

QString PlanificacionesDias::getUpdateStatement()
{
    return QString("update planificaciondia "
                   " set Notas = :Notas, IDSupervisor = :IDSupervisor, "
                   " RecordStatus = %1 "
                   " where Dia = :Dia;").arg(RECORD_MODIFIED);

}

QString PlanificacionesDias::getInsertStatement(bool)
{
    return QString("insert into planificaciondia "
                   " (Dia, Notas, IDSupervisor, RecordStatus) "
                   " values "
                   " (:Dia, :Notas, :IDSupervisor, %1);").arg(RECORD_NEW);
}

RecordSet PlanificacionesDias::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
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

RecordSet PlanificacionesDias::getUnsent()
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (p->isUnSent())
            res->push_back(p->asRecordPtr());
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
        if (p->IDSupervisor().isNull() || p->IDSupervisor().value() == -1)
            item->setText(1, "");
        else
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
    EstimacionDiaLst diasSinEstimar = DataStore::instance()->getEstimacionesDias()->getUnplanned(false);
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
    p = getByDay(ID.toDate(), false);
    if (!p.get())
        p = boost::make_shared<PlanificacionDia>(ID.toDate(), this);

    DlgPlanificacionDia dlg;
    dlg.setData(p);
    if (dlg.exec() == QDialog::Accepted)
    {
        p->Dia().setValue(dlg.Dia());
        p->Notas().setValue(dlg.Notas());
        p->IDSupervisor().setValue(dlg.IDSupervisor());

        p->updatePlanificaciones(dlg.Planificaciones());
        m_Planificaciones[p->Dia().value()] = p;
        p->setParent(this);
        return true;
    }
    return false;
}

bool PlanificacionesDias::deleteElement(QVariant ID)
{
    bool result = false;
    if (m_Planificaciones.find(ID.toDate()) != m_Planificaciones.end())
    {
        m_Planificaciones[ID.toDate()]->setDeleted();
        result = true;
    }
    return result;
}

bool PlanificacionesDias::canBeDeleted(QVariant ID)
{
    bool result = false;
    if (m_Planificaciones.find(ID.toDate()) != m_Planificaciones.end())
        result = m_Planificaciones[ID.toDate()];
    return result;
}

void PlanificacionesDias::refreshID(int, int)
{
}

PlanificacionDiaLst PlanificacionesDias::getAll(bool includeDeleted)
{
    PlanificacionDiaLst res = boost::make_shared<QList<PlanificacionDiaPtr> >();
    foreach (PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (!p->isDeleted())
            res->push_back(p);
        else
            if (includeDeleted)
                res->push_back(p);
    }
    return res;
}

PlanificacionDiaPtr PlanificacionesDias::getByDay(QDate day, bool includeDeleted)
{
    if (m_Planificaciones.find(day) == m_Planificaciones.end())
        return PlanificacionDiaPtr();
    else
    {
        PlanificacionDiaPtr p = m_Planificaciones[day];
        if (!p->isDeleted())
            return p;
        else
        {
            if (includeDeleted)
                return p;
            else
                return PlanificacionDiaPtr();
        }
    }
}

void PlanificacionesDias::saveDependants()
{
    DataStore::instance()->getPlanificacionesSubSectores()->save();
}

void PlanificacionesDias::setStatusToUnmodified(bool removeDeleted)
{
    QList<QDate> toDelete;
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (removeDeleted && p->isDeleted())
            toDelete.push_back(p->Dia().value());
        else
            p->setUnmodified();
    }
    foreach(QDate dt, toDelete)
    {
        m_Planificaciones.remove(dt);
    }
}
