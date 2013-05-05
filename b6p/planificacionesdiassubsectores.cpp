#include "planificacionesdiassubsectores.h"

PlanificacionesDiasSubSectores::PlanificacionesDiasSubSectores(QObject *parent) :
    ACollection(tr("Planifications of Sectors and subsectors for a day"),
                "Planifications of Sectors and subsectors for a day", true, parent)
{
}

QString PlanificacionesDiasSubSectores::getSelectFromMainDB()
{
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, LastUpdate from planificacionsubsector "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString PlanificacionesDiasSubSectores::getSqlString()
{
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, sent from planificacionsubsector ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString PlanificacionesDiasSubSectores::getSQLExistsInMainDB()
{
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin,AllowOverWorking from planificacionsubsector "
            " where IDRecord = :IDRecord;");
}

void PlanificacionesDiasSubSectores::addRecord(RecordPtr record, bool setNew)
{
    PlanificacionSubSectorPtr p = boost::make_shared<PlanificacionSubSector>(this);

    p->IDRecord().setValue((*record)["IDRecord"].toInt());
    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->IDSector().setValue((*record)["IDSector"].toInt());
    p->IDSubSector().setValue((*record)["IDSubsector"].toInt());
    p->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    p->HoraInicio().setValue((*record)["HoraInicio"].toInt());
    p->HoraFin().setValue((*record)["HoraFin"].toInt());
    p->AllowOverWorking().setValue((*record)["AllowOverworking"].toInt() == 1 ? true : false);
    p->setSentStatus((*record)["sent"].toInt() == 1);

    if (setNew)
        p->setNew();
    else
        p->setInitialized();

    m_Planificacion[p->IDRecord().value()] = p;
}

void PlanificacionesDiasSubSectores::updateRecord(RecordPtr record)
{
    PlanificacionSubSectorPtr p = m_Planificacion[(*record)["IDRecord"].toInt()];

    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->IDSector().setValue((*record)["IDSector"].toInt());
    p->IDSubSector().setValue((*record)["IDSubsector"].toInt());
    p->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    p->HoraInicio().setValue((*record)["HoraInicio"].toInt());
    p->HoraFin().setValue((*record)["HoraFin"].toInt());
    p->AllowOverWorking().setValue((*record)["AllowOverWorking"].toInt() == 1 ? true : false);
}

void PlanificacionesDiasSubSectores::deleteRecord(RecordPtr record)
{
    m_Planificacion.remove((*record)["IDRecord"].toInt());
}

bool PlanificacionesDiasSubSectores::exists(RecordPtr record)
{
    return (m_Planificacion[(*record)["IDRecord"].toInt()] != PlanificacionSubSectorPtr());
}

QString PlanificacionesDiasSubSectores::getDeleteStatement()
{
    return QString("update planificacionsubsector "
                   " set RecordStatus = %1 "
                   " where IDRecord = :IDRecord;").arg(RECORD_DELETED);
}

QString PlanificacionesDiasSubSectores::getUpdateStatement()
{
    return QString("update planificacionsubsector "
                   " set Dia = :Dia, IDSector = :IDSector, "
                   " IDSubsector = :IDSubSector, "
                   " IDEmpleado = :IDEmpleado, "
                   " HoraInicio = :HoraInicio, HoraFin = :HoraFin, "
                   " AllowOverWorking = :AllowOverWorking, "
                   " RecordStatus = %1 "
                   " where IDRecord = :IDRecord;").arg(RECORD_MODIFIED);
}

QString PlanificacionesDiasSubSectores::getInsertStatement(bool IncludeIDs)
{
    if (IncludeIDs)
        return QString("insert into planificacionsubsector "
                       " (IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, RecordStatus) "
                       " values "
                       " (:IDRecord, :Dia, :IDSector, :IDSubSector, :IDEmpleado, :HoraInicio, :HoraFin, :AllowOverWorking, %1);").arg(RECORD_NEW);
    else
        return QString("insert into planificacionsubsector "
                       " (Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, RecordStatus) "
                       " values "
                       " (:Dia, :IDSector, :IDSubSector, :IDEmpleado, :HoraInicio, :HoraFin, :AllowOverWorking, %1);").arg(RECORD_NEW);
}

RecordSet PlanificacionesDiasSubSectores::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
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

RecordSet PlanificacionesDiasSubSectores::getUnsent()
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
    {
        if (p->isUnSent())
            res->push_back(p->asRecordPtr());
    }
    return res;
}

void PlanificacionesDiasSubSectores::defineHeaders(QStringList &)
{
}

boost::shared_ptr<QList<QStringList> > PlanificacionesDiasSubSectores::getAll()
{
    return boost::make_shared<QList<QStringList> >();
}

void PlanificacionesDiasSubSectores::fillData(QTreeWidget &)
{
}

bool PlanificacionesDiasSubSectores::addNew()
{
    return false;
}

bool PlanificacionesDiasSubSectores::edit(QVariant )
{
    return false;
}

bool PlanificacionesDiasSubSectores::deleteElement(QVariant)
{
    return false;
}

bool PlanificacionesDiasSubSectores::canBeDeleted(QVariant)
{
    return false;
}

PlanificacionSubSectorLst PlanificacionesDiasSubSectores::getAll(QDate Dia, bool includeDeleted)
{
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();

    foreach(PlanificacionSubSectorPtr p, m_Planificacion.values())
    {
        if (p->Dia().value() == Dia)
        {
            if (!p->isDeleted())
                res->push_back(p);
            else
            {
                if (includeDeleted)
                    res->push_back(p);
            }
        }
    }

    return res;
}

PlanificacionSubSectorLst PlanificacionesDiasSubSectores::getDiasAnterioresTrabajadosPorEmpleado(
        QDate Dia, int IDEmpleado)
{
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();
    QMap<QDate, PlanificacionSubSectorPtr> diasTrabajados;

    foreach(PlanificacionSubSectorPtr p, m_Planificacion.values())
    {
        if ((p->Dia().value() < Dia) && (p->IDEmpleado().value() == IDEmpleado))
        {
            if (!p->isDeleted())
                diasTrabajados[p->Dia().value()] = p;
        }
    }

    QDate fechaAnt = Dia.addDays(-1);
    while(diasTrabajados.find(fechaAnt) != diasTrabajados.end())
    {
        res->push_back(diasTrabajados[fechaAnt]);
        fechaAnt = fechaAnt.addDays(-1);
    }

    return res;
}


void PlanificacionesDiasSubSectores::updateWithOtherData(PlanificacionSubSectorLst other)
{
    if (other->count() == 0)
        return;

    PlanificacionSubSectorLst lista = getAll(other->at(0)->Dia().value(), false);

    foreach (PlanificacionSubSectorPtr o, *other)
    {
        bool found = false;
        foreach(PlanificacionSubSectorPtr ps, *lista)
        {
            if (ps->isEqualsTo(o))
            {
                if (o->isDeleted())
                    ps->setDeleted();
                else
                    ps->updateWith(o);
                found = true;
                break;
            }
        }
        if (!found)
        {
            m_Planificacion[o->IDRecord().value()] = o;
            o->setParent(this);
            o->setNew();
        }
    }
}

void PlanificacionesDiasSubSectores::setStatusToUnmodified(bool removeDeleted)
{
    QList<int> toDelete;
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
    {
        if (removeDeleted && p->isDeleted())
            toDelete.push_back(p->IDRecord().value());
        else
            p->setUnmodified();
    }
    foreach(int id, toDelete)
    {
        m_Planificacion.remove(id);
    }
}

void PlanificacionesDiasSubSectores::refreshID(int oldID, int newID)
{
    PlanificacionSubSectorPtr p = m_Planificacion[oldID];
    if (p)
    {
        p->updateID(newID);
        m_Planificacion.remove(oldID);
        m_Planificacion[newID] = p;
    }
}
