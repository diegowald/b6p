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
#include "estimacionesdias.h"
#include "dlgestimaciondia.h"
#include "dlgaddmanyestimationdays.h"
#include "dlgapproveplanifications.h"
#include "datastore.h"
#include <QsLog.h>

EstimacionesDias::EstimacionesDias(QObject *parent)
    : ACollection(tr("Day Estimations"),
                  "Day Estimations",false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

QString EstimacionesDias::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, HorasEstimadas, LastUpdate from planificaciondias "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString EstimacionesDias::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select Dia, HorasEstimadas, sent, RecordStatus from planificaciondias ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString EstimacionesDias::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, HorasEstimadas from planificaciondias ")
            + QString(" where Dia = :Dia;");
}

void EstimacionesDias::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr e = boost::make_shared<EstimacionDia>(this);
    e->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    e->EstimacionHoras().setValue((*record)["HorasEstimadas"].toInt());
    e->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));

    if (setNew)
        e->setNew();
    else
        e->setInitialized();

    m_Estimaciones[e->Dia().value()] = e;
}

void EstimacionesDias::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    e->EstimacionHoras().setValue((*record)["HorasEstimadas"].toInt());
    if (isFromSincro)
    {
        e->setInMemoryRecordStatus(UNMODIFIED);
        e->setLocalRecordStatus(UNMODIFIED);
    }
}

void EstimacionesDias::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    m_Estimaciones.remove(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
}

bool EstimacionesDias::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    return (m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()] != EstimacionDiaPtr());
}

bool EstimacionesDias::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    if (e != EstimacionDiaPtr())
    {
        return e->isEqualsTo(record);
    }
    else
        return false;
}

bool EstimacionesDias::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return e->isUnSent();
}

RecordPtr EstimacionesDias::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    EstimacionDiaPtr e = m_Estimaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return e->asRecordPtr();
}

QString EstimacionesDias::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionDias set RecordStatus = %1, sent = 0 where Dia = :Dia;").arg(DELETED);
}

QString EstimacionesDias::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificacionDias set RecordStatus = %1, sent = 0 where Dia = :Dia;").arg(DELETED);
}

QString EstimacionesDias::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondias set HorasEstimadas = :HorasEstimadas "
                   " , RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia;").arg(MODIFIED);
}

QString EstimacionesDias::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondias set HorasEstimadas = :HorasEstimadas "
                   " , RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia;").arg(MODIFIED);
}

QString EstimacionesDias::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificaciondias (Dia, HorasEstimadas, RecordStatus, sent) "
                   " values "
                   " (:Dia, :HorasEstimadas, %1, 0);").arg(NEW);
}

QString EstimacionesDias::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificaciondias (Dia, HorasEstimadas, RecordStatus, sent) "
                   " values "
                   " (:Dia, :HorasEstimadas, %1, 0);").arg(NEW);
}

RecordSet EstimacionesDias::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        switch (status)
        {
        case NEW:
            if (e->isNew(fromMemory))
                res->push_back(e->asRecordPtr());
            break;
        case MODIFIED:
        {
            if (e->isModified(fromMemory))
                res->push_back(e->asRecordPtr());
            break;
        }
        case DELETED:
            if (e->isDeleted(fromMemory))
                res->push_back(e->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet EstimacionesDias::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (e->isUnSent())
            res->push_back(e->asRecordPtr());
    }
    return res;
}

boost::shared_ptr<QList<QAction*> > EstimacionesDias::getActions()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QAction*> >actions = boost::make_shared<QList<QAction*> >();

    QAction* action = new QAction(tr("Add Range"), NULL);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/calendar"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon);
    connect(action, SIGNAL(triggered()), this, SLOT(addManyDays()));
    actions->push_back(action);

    action = new QAction(tr("Approve"), NULL);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon2);
    connect(action, SIGNAL(triggered()), this, SLOT(approveSelected()));
    actions->push_back(action);

    return actions;
}

void EstimacionesDias::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Date") << tr("Hours estimation") << tr("Planned");
}

boost::shared_ptr<QList<QStringList> > EstimacionesDias::getAll()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    EstimacionDiaLst lst = getAll(false);

    foreach(EstimacionDiaPtr e, *lst)
    {
        QStringList r;
        r << e->Dia().value().toString()
          << QString::number(e->EstimacionHoras().value())
          << (e->isPlanned() ? tr("Planned") : tr("Not Planned"));
        res->push_back(r);
    }

    return res;
}

bool EstimacionesDias::isColumnEditable(QVariant ID, int column)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr ptr = m_Estimaciones[ID.toDate()];
    return ((column == 1) && (!ptr->isPlanned()));
}

void EstimacionesDias::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    EstimacionDiaLst lst = getAll(false);
    foreach(EstimacionDiaPtr e, *lst)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, e->Dia().value().toString(Qt::TextDate));
            item->setData(0, Qt::UserRole, e->Dia().value());
            item->setText(1, QString::number(e->EstimacionHoras().value()));
            item->setText(2, e->isPlanned() ? tr("Yes") : tr("No"));
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled);
            tree.insertTopLevelItem(0, item);
}
}

bool EstimacionesDias::addNew(QTreeWidgetItem *item)
{
    QLOG_TRACE_FN();
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(item, id);
}

bool EstimacionesDias::addNew()
{
    QLOG_TRACE_FN();
    QDate id = QDateTime::fromMSecsSinceEpoch(0).date();
    return edit(id);
}

bool EstimacionesDias::edit(QTreeWidgetItem *item, QVariant ID)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr e = m_Estimaciones[ID.toDate()];
    e->EstimacionHoras().setValue(item->text(1).toInt());
    return true;
}

bool EstimacionesDias::edit(QVariant ID)
{
    QLOG_TRACE_FN();
    EstimacionDiaPtr e;
    if (ID == QDateTime::fromMSecsSinceEpoch(0).date())
        e = boost::make_shared<EstimacionDia>(this);
    else
        e = m_Estimaciones[ID.toDate()];

    DlgEstimacionDia dlg;
    dlg.setData(e);
    if (dlg.exec() == QDialog::Accepted)
    {
        e->Dia().setValue(dlg.Dia());
        e->EstimacionHoras().setValue(dlg.EstimacionHoras());
        m_Estimaciones[e->Dia().value()] = e;
        return true;
    }
    return false;
}

bool EstimacionesDias::deleteElement(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Estimaciones.find(ID.toDate()) != m_Estimaciones.end())
    {
        m_Estimaciones[ID.toDate()]->setDeleted();
        result = true;
    }
    return result;
}

bool EstimacionesDias::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Estimaciones.find(ID.toDate()) != m_Estimaciones.end())
        result = m_Estimaciones[ID.toDate()]->canBeDeleted();
    return result;
}

void EstimacionesDias::refreshID(int, int)
{
    QLOG_TRACE_FN();
}

EstimacionDiaLst EstimacionesDias::getAll(bool includeDeleted)
{
    QLOG_TRACE_FN();
    EstimacionDiaLst res = boost::make_shared<QList<EstimacionDiaPtr> >();

    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (!e->isDeleted(false))
            res->push_back(e);
        else
            if (includeDeleted)
                res->push_back(e);
    }

    return res;
}

EstimacionDiaLst EstimacionesDias::getUnplanned(bool includeDeleted)
{
    QLOG_TRACE_FN();
    EstimacionDiaLst res = boost::make_shared<QList<EstimacionDiaPtr> >();

    foreach(EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (!e->isPlanned())
        {
            if (!e->isDeleted(true))
                res->push_back(e);
            else
                if (includeDeleted)
                    res->push_back(e);
        }
    }

    return res;
}

EstimacionDiaPtr EstimacionesDias::get(QDate dia, bool includeDeleted)
{
    QLOG_TRACE_FN();
    if (m_Estimaciones.find(dia) == m_Estimaciones.end())
        return EstimacionDiaPtr();
    else
    {
        EstimacionDiaPtr e = m_Estimaciones[dia];
        if (!e->isDeleted(true))
            return e;
        else
        {
            if (includeDeleted)
                return e;
            else
                return EstimacionDiaPtr();
        }
    }
}

void EstimacionesDias::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<QDate> toDelete;
    foreach (EstimacionDiaPtr e, m_Estimaciones.values())
    {
        if (removeDeleted && e->isDeleted(true))
            toDelete.push_back(e->Dia().value());
        else
        {
            if (impactInMemmory)
                e->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                e->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(QDate dt, toDelete)
    {
        m_Estimaciones.remove(dt);
    }
}

void EstimacionesDias::addManyDays()
{
    QLOG_TRACE_FN();
    DlgAddManyEstimationDays dlg;
    dlg.setFrom(QDate::currentDate());
    dlg.setTo(QDate::currentDate().addMonths(1));
    if (dlg.exec() == QDialog::Accepted)
    {
        QDate from = dlg.From();
        QDate To = dlg.To();
        int delta = from.daysTo(To);
        for (int i = 0; i < delta; ++i)
        {
            QDate date = from.addDays(i);
            if (m_Estimaciones.find(date) == m_Estimaciones.end())
            {
                EstimacionDiaPtr e = boost::make_shared<EstimacionDia>(true, this);
                e->Dia().setValue(date);
                m_Estimaciones[e->Dia().value()] = e;
            }
        }
        save();
    }
}

void EstimacionesDias::approveSelected()
{
    QLOG_TRACE_FN();
    DlgApprovePlanifications dlg;
    dlg.setData(DataStore::instance()->getPlanificacionesDias()->getAllReadyForApproval());
    if (dlg.exec() == QDialog::Accepted)
    {
        PlanificacionDiaLst lst = dlg.getPlanificacionToApprove();

        foreach(PlanificacionDiaPtr p, *lst)
        {
            p->approve();
        }

        DataStore::instance()->getPlanificacionesDias()->save();
    }
}
