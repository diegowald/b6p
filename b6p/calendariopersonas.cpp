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
#include "calendariopersonas.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>

CalendarioPersonas::CalendarioPersonas(QObject *parent) :
    ACollection(tr("Employee availability"),
                "Employee availability", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

CalendarioPersonas::~CalendarioPersonas()
{
    QLOG_TRACE_FN();
}

QString CalendarioPersonas::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso, HoraIngreso2, HoraEgreso2, LastUpdate from calendariopersonas "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString CalendarioPersonas::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso, HoraIngreso2, HoraEgreso2, sent, RecordStatus from calendariopersonas "
            " where RecordStatus <> %1;").arg(DELETED);
}

QString CalendarioPersonas::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso, HoraIngreso2, HoraEgreso2 from calendariopersonas "
                   " where Dia = :Dia and IDEmpleado = :IDEmpleado; ");
}

void CalendarioPersonas::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    CalendarioPersonaPtr c = boost::make_shared<CalendarioPersona>(this);

    c->Dia().setValue((*record)["Dia"].toInt());
    c->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    c->HoraIngreso1().setValue((*record)["HoraIngreso"].toInt());
    c->HoraEgreso1().setValue((*record)["HoraEgreso"].toInt());
    c->HoraIngreso2().setValue((*record)["HoraIngreso2"].toInt());
    c->HoraEgreso2().setValue((*record)["HoraEgreso2"].toInt());
    c->setLocalRecordStatus((RecordStatus)(*record)["RecordStatus"].toInt());

    if (setNew)
        c->setNew();
    else
        c->setInitialized();

    m_Calendarios.push_back(c);
}

void CalendarioPersonas::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    CalendarioPersonaPtr c;
    foreach (c, m_Calendarios) {
        if ((c->Dia().value() == (*record)["Dia"]) && (c->IDEmpleado().value() == (*record)["IDEmpleado"]))
            break;
    }
    c->HoraIngreso1().setValue((*record)["HoraIngreso"].toInt());
    c->HoraEgreso1().setValue((*record)["HoraEgreso"].toInt());
    c->HoraIngreso2().setValue((*record)["HoraIngreso2"].toInt());
    c->HoraEgreso2().setValue((*record)["HoraEgreso2"].toInt());
    if (isFromSincro)
    {
        c->setInMemoryRecordStatus(UNMODIFIED);
        c->setLocalRecordStatus(UNMODIFIED);
    }
}

void CalendarioPersonas::deleteRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

bool CalendarioPersonas::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    foreach (CalendarioPersonaPtr c, m_Calendarios) {
        if ((c->Dia().value() == (*record)["Dia"]) && (c->IDEmpleado().value() == (*record)["IDEmpleado"]))
            return true;
    }
    return false;
}

bool CalendarioPersonas::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    foreach (CalendarioPersonaPtr c, m_Calendarios) {
        if ((c->Dia().value() == (*record)["Dia"]) && (c->IDEmpleado().value() == (*record)["IDEmpleado"]))
        {
            return c->isEqualsTo(record);
        }
    }
    return false;
}

bool CalendarioPersonas::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    foreach (CalendarioPersonaPtr c, m_Calendarios) {
        if ((c->Dia().value() == (*record)["Dia"]) && (c->IDEmpleado().value() == (*record)["IDEmpleado"]))
            return c->isUnSent();
    }
    return false;
}

RecordPtr CalendarioPersonas::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    foreach (CalendarioPersonaPtr c, m_Calendarios) {
        if ((c->Dia().value() == (*record)["Dia"]) && (c->IDEmpleado().value() == (*record)["IDEmpleado"]))
            return c->asRecordPtr();
    }
    return RecordPtr();
}

QString CalendarioPersonas::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update calendariopersonas set RecordStatus = %1, sent = 0 where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(DELETED);
}

QString CalendarioPersonas::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update calendariopersonas set RecordStatus = %1, sent = 0 where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(DELETED);
}

QString CalendarioPersonas::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update calendariopersonas set HoraIngreso = :HoraIngreso, HoraEgreso = :HoraEgreso, "
                   " HoraIngreso2 = :HoraIngreso2, HoraEgreso2 = :HoraEgreso2, "
                   " RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(MODIFIED);
}

QString CalendarioPersonas::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update calendariopersonas set HoraIngreso = :HoraIngreso, HoraEgreso = :HoraEgreso, "
                   " HoraIngreso = :HoraIngreso, HoraEgreso = :HoraEgreso, "
                   " RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(MODIFIED);
}

QString CalendarioPersonas::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into calendariopersonas "
            " (Dia, IDEmpleado, HoraIngreso, HoraEgreso, HoraIngreso, HoraEgreso, RecordStatus, sent) "
            " values "
            " (:Dia, :IDEmpleado, :HoraIngreso, :HoraEgreso, :HoraIngreso2, :HoraEgreso2, %1, 0);").arg(NEW);
}

QString CalendarioPersonas::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into calendariopersonas "
            " (Dia, IDEmpleado, HoraIngreso, HoraEgreso, HoraIngreso2, HoraEgreso2, RecordStatus, sent) "
            " values "
            " (:Dia, :IDEmpleado, :HoraIngreso, :HoraEgreso, :HoraIngreso2, :HoraEgreso2, %1, 0);").arg(NEW);
}

RecordSet CalendarioPersonas::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(CalendarioPersonaPtr c, m_Calendarios)
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

RecordSet CalendarioPersonas::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(CalendarioPersonaPtr c, m_Calendarios)
    {
        if (c->isUnSent())
            res->push_back(c->asRecordPtr());
    }
    return res;
}

void CalendarioPersonas::defineHeaders(QStringList &)
{
    QLOG_TRACE_FN();
}

boost::shared_ptr<QList<QStringList> > CalendarioPersonas::getAll()
{
    QLOG_TRACE_FN();
    return boost::make_shared<QList<QStringList> >();
}

void CalendarioPersonas::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool CalendarioPersonas::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool CalendarioPersonas::edit(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool CalendarioPersonas::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool CalendarioPersonas::canBeDeleted(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

CalendarioPersonaLst CalendarioPersonas::getAll(int IDEmpleado, bool includeDeleted)
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst res = boost::make_shared<QList<CalendarioPersonaPtr> >();
    foreach (CalendarioPersonaPtr cal, m_Calendarios)
    {
        if (cal->IDEmpleado().value() == IDEmpleado)
        {
            if (!cal->isDeleted(true))
                res->push_back(cal);
            else
                if (includeDeleted)
                    res->push_back(cal);
        }
    }
    return res;
}

CalendarioPersonaPtr CalendarioPersonas::get(int IDEmpleado, int Dia, int HoraInicio, int HoraFin, bool includeDeleted)
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst all = getAll(IDEmpleado, false);
    foreach(CalendarioPersonaPtr c, *all)
    {
        if (c->canWork(Dia, HoraInicio, HoraFin))
        {
            if (!c->isDeleted(true))
                return c;
            else
            {
                if (includeDeleted)
                    return c;
            }
        }
    }
    return CalendarioPersonaPtr();
}

bool CalendarioPersonas::canWork(int IDEmpleado, int Dia)
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst all = getAll(IDEmpleado, false);
    foreach (CalendarioPersonaPtr c, *all)
    {
        if (c->canWork(Dia))
            return true;
    }
    return false;
}

void CalendarioPersonas::updateCalendarFromData(CalendarioPersonaLst dataList)
{
    QLOG_TRACE_FN();
    foreach (CalendarioPersonaPtr c, *dataList)
    {
        updateCalendarFromData(c);
    }
}

void CalendarioPersonas::updateCalendarFromData(CalendarioPersonaPtr dataFrom)
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst cp = getAll(dataFrom->IDEmpleado().value(), false);
    foreach(CalendarioPersonaPtr c, *cp)
    {
        if (c->EqualsTo(dataFrom))
        {
            c->updateWith(dataFrom);
            return;
        }
    }

    // Si llega aca es porque no hay un elemento
    CalendarioPersonaPtr c = boost::make_shared<CalendarioPersona>(this);
    c->Dia().setValue(dataFrom->Dia().value());
    c->IDEmpleado().setValue(dataFrom->IDEmpleado().value());
    c->updateWith(dataFrom);
    c->setNew();
    m_Calendarios.push_back(c);
    return;
}

void CalendarioPersonas::updateCalendarWithNewIDEmpleado(int oldId, int newId)
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst cal = getAll(oldId, false);
    foreach (CalendarioPersonaPtr cp, *cal)
    {
        cp->updateIDEmpleado(newId);
    }
}

void CalendarioPersonas::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<CalendarioPersonaPtr> toDelete;
    foreach(CalendarioPersonaPtr c, m_Calendarios)
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
    foreach(CalendarioPersonaPtr c, toDelete)
    {
        m_Calendarios.removeOne(c);
    }
}
