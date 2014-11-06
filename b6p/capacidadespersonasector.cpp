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
#include "capacidadespersonasector.h"
#include <QsLog.h>


CapacidadesPersonaSector::CapacidadesPersonaSector(const QString &dbName, QObject *parent) :
    ACollection(tr("Employee capacity by Sector"),
                "Employee capacity by Sector", false, ACollection::MERGE_KEEP_LOCAL, dbName, parent)
{
    QLOG_TRACE_FN();
}

CapacidadPersonaSectorLst CapacidadesPersonaSector::getAll(int IDEmpleado, bool includeDeleted)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorLst res = CapacidadPersonaSectorLst::create();
    foreach(CapacidadPersonaSectorPtr cap, m_Capacidades)
    {
        if (cap->IDEmpleado().value() == IDEmpleado)
        {
            if (!cap->isDeleted(true))
                res->push_back(cap);
            else
                if (includeDeleted)
                    res->push_back(cap);
        }
    }
    return res;
}

CapacidadPersonaSectorPtr CapacidadesPersonaSector::get(int idEmpleado, int IDSector, int IDSubSector, bool includeDeleted)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorLst all = getAll(idEmpleado, includeDeleted);
    foreach(CapacidadPersonaSectorPtr c, *all)
    {
        if (c->canWork(IDSector, IDSubSector))
            return c;
    }
    return CapacidadPersonaSectorPtr();
}

QString CapacidadesPersonaSector::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad, LastUpdate from capacidadespersonassector "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString CapacidadesPersonaSector::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad, sent, RecordStatus from capacidadespersonassector ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString CapacidadesPersonaSector::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select IDSector, IDSubSector, IDEmpleado, Capacidad from capacidadespersonassector "
                   " where IDSector = :IDSector and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;");
}

void CapacidadesPersonaSector::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorPtr c = CapacidadPersonaSectorPtr::create(this);

    c->IDSector().setValue((*record)["IDSector"].toInt());
    c->ID_SubSector().setValue((*record)["IDSubSector"].toInt());
    c->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    c->Capacidad().setValue((*record)["Capacidad"].toInt());
    c->setLocalRecordStatus((RecordStatus)(*record)["RecordStatus"].toInt());

    if (setNew)
        c->setNew();
    else
        c->setInitialized();

    m_Capacidades.push_back(c);
}

void CapacidadesPersonaSector::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);

    c->Capacidad().setValue((*record)["Capacidad"].toInt());
    if (isFromSincro)
    {
        c->setLocalRecordStatus(UNMODIFIED);
        c->setInMemoryRecordStatus(UNMODIFIED);
    }
}

void CapacidadesPersonaSector::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);

    m_Capacidades.removeOne(c);
}

bool CapacidadesPersonaSector::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return (c != CapacidadPersonaSectorPtr());
}

bool CapacidadesPersonaSector::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    if (c != CapacidadPersonaSectorPtr())
    {
        return c->isEqualsTo(record);
    }
    else
        return false;
}

bool CapacidadesPersonaSector::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return c->isUnSent();
}

RecordPtr CapacidadesPersonaSector::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    CapacidadPersonaSectorPtr c = get((*record)["IDEmpleado"].toInt(),
            (*record)["IDSector"].toInt(),
            (*record)["IDSubSector"].toInt(), true);
    return c->asRecordPtr();
}

QString CapacidadesPersonaSector::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update capacidadespersonassector set RecordStatus = %1, sent = 0 where IDSector = :IDSector "
                   " and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;").arg(DELETED);
}

QString CapacidadesPersonaSector::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update capacidadespersonassector set RecordStatus = %1, sent = 0 where IDSector = :IDSector "
                   " and IDSubSector = :IDSubSector and IDEmpleado = :IDEmpleado;").arg(DELETED);
}

QString CapacidadesPersonaSector::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update capacidadespersonassector set "
                   " Capacidad = :Capacidad, RecordStatus = %1, sent = 0 "
                   " where "
                   " IDSector = :IDSector and IDSubSector = :IDSubSector "
                   " and IDEmpleado = :IDEmpleado;").arg(MODIFIED);
}

QString CapacidadesPersonaSector::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update capacidadespersonassector set "
                   " Capacidad = :Capacidad, RecordStatus = %1, sent = 0 "
                   " where "
                   " IDSector = :IDSector and IDSubSector = :IDSubSector "
                   " and IDEmpleado = :IDEmpleado;").arg(MODIFIED);
}

QString CapacidadesPersonaSector::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into capacidadespersonassector "
                   " (IDSector, IDSubSector, IDEmpleado, Capacidad, RecordStatus, sent) "
                   " values "
                   " (:IDSector, :IDSubSector, :IDEmpleado, :Capacidad, %1, 0);").arg(NEW);
}

QString CapacidadesPersonaSector::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into capacidadespersonassector "
                   " (IDSector, IDSubSector, IDEmpleado, Capacidad, RecordStatus, sent) "
                   " values "
                   " (:IDSector, :IDSubSector, :IDEmpleado, :Capacidad, %1, 0);").arg(NEW);
}

RecordSet CapacidadesPersonaSector::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = RecordSet::create();
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        switch (status)
        {
        case NEW:
            if (c->isNew(fromMemory))
                res->push_back(c->asRecordPtr());
            break;
        case MODIFIED:
        {
            if (c->isModified(fromMemory))
                res->push_back(c->asRecordPtr());
            break;
        }
        case DELETED:
            if (c->isDeleted(fromMemory))
                res->push_back(c->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet CapacidadesPersonaSector::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = RecordSet::create();
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        if (c->isUnSent())
            res->push_back(c->asRecordPtr());
    }
    return res;
}

void CapacidadesPersonaSector::defineHeaders(QStringList &)
{
    QLOG_TRACE_FN();
}

QSharedPointer<QList<QStringList>> CapacidadesPersonaSector::getAll()
{
    QLOG_TRACE_FN();
    return QSharedPointer<QList<QStringList>>::create();
}

void CapacidadesPersonaSector::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool CapacidadesPersonaSector::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool CapacidadesPersonaSector::edit(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool CapacidadesPersonaSector::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool CapacidadesPersonaSector::canBeDeleted(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

void CapacidadesPersonaSector::updateCapacityfromData(CapacidadPersonaSectorLst dataFrom)
{
    QLOG_TRACE_FN();
    if (dataFrom->count() > 0)
    {
        CapacidadPersonaSectorLst capsEmpleado = getAll(dataFrom->at(0)->IDEmpleado().value(), false);
        foreach (CapacidadPersonaSectorPtr nc, *dataFrom)
        {
            bool found = false;
            foreach (CapacidadPersonaSectorPtr c, *capsEmpleado)
            {
                if (c->EqualsTo(nc))
                {
                    c->updateWith(nc);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                m_Capacidades.push_back(nc);
                nc->setNew();
            }
        }
    }
}

void CapacidadesPersonaSector::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<CapacidadPersonaSectorPtr> toDelete;
    foreach(CapacidadPersonaSectorPtr c, m_Capacidades)
    {
        if (removeDeleted && c->isDeleted(true))
            toDelete.push_back(c);
        else
        {
            if (impactInMemmory)
                c->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                c->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(CapacidadPersonaSectorPtr c, toDelete)
    {
        m_Capacidades.removeOne(c);
    }
}
