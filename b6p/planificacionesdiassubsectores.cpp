/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "planificacionesdiassubsectores.h"
#include <QsLog.h>

PlanificacionesDiasSubSectores::PlanificacionesDiasSubSectores(QObject *parent) :
    ACollection(tr("Planifications of Sectors and subsectors for a day"),
                "Planifications of Sectors and subsectors for a day", true,
                ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

QString PlanificacionesDiasSubSectores::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, LastUpdate from planificacionsubsector "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString PlanificacionesDiasSubSectores::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, sent, RecordStatus from planificacionsubsector ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString PlanificacionesDiasSubSectores::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin,AllowOverWorking from planificacionsubsector "
            " where IDRecord = :IDRecord;");
}

void PlanificacionesDiasSubSectores::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorPtr p = boost::make_shared<PlanificacionSubSector>(this);

    p->IDRecord().setValue((*record)["IDRecord"].toInt());
    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->IDSector().setValue((*record)["IDSector"].toInt());
    p->IDSubSector().setValue((*record)["IDSubsector"].toInt());
    p->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    p->HoraInicio().setValue((*record)["HoraInicio"].toInt());
    p->HoraFin().setValue((*record)["HoraFin"].toInt());
    p->AllowOverWorking().setValue((*record)["AllowOverworking"].toInt() == 1 ? true : false);
    p->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));

    if (setNew)
        p->setNew();
    else
        p->setInitialized();

    m_Planificacion[p->IDRecord().value()] = p;
}

void PlanificacionesDiasSubSectores::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorPtr p = m_Planificacion[(*record)["IDRecord"].toInt()];

    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->IDSector().setValue((*record)["IDSector"].toInt());
    p->IDSubSector().setValue((*record)["IDSubsector"].toInt());
    p->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    p->HoraInicio().setValue((*record)["HoraInicio"].toInt());
    p->HoraFin().setValue((*record)["HoraFin"].toInt());
    p->AllowOverWorking().setValue((*record)["AllowOverWorking"].toInt() == 1 ? true : false);
    if (isFromSincro)
    {
        p->setInMemoryRecordStatus(UNMODIFIED);
        p->setLocalRecordStatus(UNMODIFIED);
    }
}

void PlanificacionesDiasSubSectores::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    m_Planificacion.remove((*record)["IDRecord"].toInt());
}

bool PlanificacionesDiasSubSectores::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    return (m_Planificacion[(*record)["IDRecord"].toInt()] != PlanificacionSubSectorPtr());
}

bool PlanificacionesDiasSubSectores::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorPtr p = m_Planificacion[(*record)["IDRecord"].toInt()];
    if (p != PlanificacionSubSectorPtr())
    {
        return p->isEqualsTo(record);
    }
    else
        return false;
}

bool PlanificacionesDiasSubSectores::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    PlanificacionSubSectorPtr p = m_Planificacion[(*record)["IDRecord"].toInt()];
    return p->isUnSent();
}

RecordPtr PlanificacionesDiasSubSectores::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    PlanificacionSubSectorPtr p = m_Planificacion[(*record)["IDRecord"].toInt()];
    return p->asRecordPtr();
}

QString PlanificacionesDiasSubSectores::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionsubsector "
                   " set RecordStatus = %1, sent = 0 "
                   " where IDRecord = :IDRecord;").arg(DELETED);
}

QString PlanificacionesDiasSubSectores::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionsubsector "
                   " set RecordStatus = %1, sent = 0 "
                   " where IDRecord = :IDRecord;").arg(DELETED);
}

QString PlanificacionesDiasSubSectores::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionsubsector "
                   " set Dia = :Dia, IDSector = :IDSector, "
                   " IDSubsector = :IDSubSector, "
                   " IDEmpleado = :IDEmpleado, "
                   " HoraInicio = :HoraInicio, HoraFin = :HoraFin, "
                   " AllowOverWorking = :AllowOverWorking, "
                   " RecordStatus = %1 "
                   " where IDRecord = :IDRecord;").arg(MODIFIED);
}

QString PlanificacionesDiasSubSectores::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionsubsector "
                   " set Dia = :Dia, IDSector = :IDSector, "
                   " IDSubsector = :IDSubSector, "
                   " IDEmpleado = :IDEmpleado, "
                   " HoraInicio = :HoraInicio, HoraFin = :HoraFin, "
                   " AllowOverWorking = :AllowOverWorking, "
                   " RecordStatus = %1 "
                   " where IDRecord = :IDRecord;").arg(MODIFIED);
}

QString PlanificacionesDiasSubSectores::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificacionsubsector "
                   " (Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, RecordStatus) "
                   " values "
                   " (:Dia, :IDSector, :IDSubSector, :IDEmpleado, :HoraInicio, :HoraFin, :AllowOverWorking, %1);").arg(NEW);
}

QString PlanificacionesDiasSubSectores::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificacionsubsector "
                   " (IDRecord, Dia, IDSector, IDSubsector, IDEmpleado, HoraInicio, HoraFin, AllowOverWorking, RecordStatus, sent) "
                   " values "
                   " (:IDRecord, :Dia, :IDSector, :IDSubSector, :IDEmpleado, :HoraInicio, :HoraFin, :AllowOverWorking, %1, 0);").arg(NEW);
}


RecordSet PlanificacionesDiasSubSectores::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
    {
        switch (status)
        {
        case NEW:
            if (p->isNew(fromMemory))
                res->push_back(p->asRecordPtr());
            break;
        case MODIFIED:
        {
            if (p->isModified(fromMemory))
                res->push_back(p->asRecordPtr());
            break;
        }
        case DELETED:
            if (p->isDeleted(fromMemory))
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
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
}

boost::shared_ptr<QList<QStringList> > PlanificacionesDiasSubSectores::getAll()
{
    QLOG_TRACE_FN();
    return boost::make_shared<QList<QStringList> >();
}

void PlanificacionesDiasSubSectores::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool PlanificacionesDiasSubSectores::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool PlanificacionesDiasSubSectores::edit(QVariant )
{
    QLOG_TRACE_FN();
    return false;
}

bool PlanificacionesDiasSubSectores::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool PlanificacionesDiasSubSectores::canBeDeleted(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

PlanificacionSubSectorLst PlanificacionesDiasSubSectores::getAll(const QDate &Dia, bool includeDeleted)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();

    foreach(PlanificacionSubSectorPtr p, m_Planificacion.values())
    {
        if (p->Dia().value() == Dia)
        {
            if (!p->isDeleted(true))
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

PlanificacionSubSectorLst PlanificacionesDiasSubSectores::getAll(const QDate& dateFrom, const QDate& dateTo)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();

    foreach(PlanificacionSubSectorPtr p, m_Planificacion.values())
    {
        QDate date = p->Dia().value();
        if ((dateFrom <= date) && (date <= dateTo))
        {
            if (!p->isPlanificacionDeleted() && !p->isDeleted(false))
                res->push_back(p);
            /*else
            {
                if (includeDeleted)
                    res->push_back(p);
            }*/
        }
    }

    return res;
}

PlanificacionSubSectorLst PlanificacionesDiasSubSectores::getDiasAnterioresTrabajadosPorEmpleado(
        QDate Dia, int IDEmpleado)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();
    QMap<QDate, PlanificacionSubSectorPtr> diasTrabajados;

    foreach(PlanificacionSubSectorPtr p, m_Planificacion.values())
    {
        if ((p->Dia().value() < Dia) && (p->IDEmpleado().value() == IDEmpleado))
        {
            if (!p->isDeleted(true))
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
    QLOG_TRACE_FN();
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
                if (o->isDeleted(true))
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

void PlanificacionesDiasSubSectores::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach(PlanificacionSubSectorPtr p, m_Planificacion)
    {
        if (removeDeleted && p->isDeleted(true))
            toDelete.push_back(p->IDRecord().value());
        else
        {
            if (impactInMemmory)
                p->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                p->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(int id, toDelete)
    {
        m_Planificacion.remove(id);
    }
}

void PlanificacionesDiasSubSectores::refreshID(int oldID, int newID)
{
    QLOG_TRACE_FN();
    PlanificacionSubSectorPtr p = m_Planificacion[oldID];
    if (p)
    {
        p->updateID(newID);
        m_Planificacion.remove(oldID);
        m_Planificacion[newID] = p;
    }
}
