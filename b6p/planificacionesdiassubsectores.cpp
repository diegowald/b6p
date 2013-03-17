#include "planificacionesdiassubsectores.h"

PlanificacionesDiasSubSectores::PlanificacionesDiasSubSectores(QObject *parent) :
    ACollection(tr("Planifications of Sectors and subsectors for a day"),
                "Planifications of Sectors and subsectors for a day", true, parent)
{
}

QString PlanificacionesDiasSubSectores::getSelectFromMainDB()
{
    return "";
}

QString PlanificacionesDiasSubSectores::getSqlString()
{
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin from planificacionsubsector ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

QString PlanificacionesDiasSubSectores::getSQLExistsInMainDB()
{
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin from planificacionsubsector "
            " where IDRecord = :IDRecord;");
}

void PlanificacionesDiasSubSectores::addRecord(RecordPtr record)
{
    PlanificacionSubSectorPtr p = boost::make_shared<PlanificacionSubSector>(this);

    p->IDRecord().setValue((*record)["IDRecord"].toInt());
    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->IDSector().setValue((*record)["IDSector"].toInt());
    p->IDSubSector().setValue((*record)["IDSubsector"].toInt());
    p->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    p->HoraInicio().setValue((*record)["HoraInicio"].toInt());
    p->HoraFin().setValue((*record)["HoraFin"].toInt());
    p->setInitialized();

    m_Planificacion[p->IDRecord().value()] = p;
}

void PlanificacionesDiasSubSectores::updateRecord(RecordPtr record)
{
}

void PlanificacionesDiasSubSectores::deleteRecord(RecordPtr record)
{
}

bool PlanificacionesDiasSubSectores::exists(RecordPtr record)
{
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
                   " RecordStatus = %1 "
                   " where IDRecord = :IDRecord;").arg(RECORD_MODIFIED);
}

QString PlanificacionesDiasSubSectores::getInsertStatement()
{
    return QString("insert into planificacionsubsector "
            " (Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, RecordStatus) "
                   " values "
                   " (:Dia, :IDSector, :IDSubSector, :IDEmpleado, :HoraInicio, :HoraFin, %1);").arg(RECORD_NEW);
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

void PlanificacionesDiasSubSectores::defineHeaders(QStringList &list)
{
}

void PlanificacionesDiasSubSectores::fillData(QTreeWidget &tree)
{
}

bool PlanificacionesDiasSubSectores::addNew()
{
}

bool PlanificacionesDiasSubSectores::edit(QVariant ID)
{
}

bool PlanificacionesDiasSubSectores::deleteElement(QVariant ID)
{
}

bool PlanificacionesDiasSubSectores::canBeDeleted(QVariant ID)
{
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
