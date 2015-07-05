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
#include "planificacionesdias.h"
#include "datastore.h"
#include "dlgselectorbytdate.h"

#include <QsLog.h>


PlanificacionesDias::PlanificacionesDias(const QString &dbName, QObject *parent) :
    ACollection(tr("Days Planifications"),
                "Days Planifications", false, ACollection::MERGE_KEEP_MAIN, dbName, parent)
{
    QLOG_TRACE_FN();
    planUnderEdition = PlanificacionDiaPtr(NULL);
    connect(this, SIGNAL(requestSave()), this, SLOT(saveRequested()));
}

QString PlanificacionesDias::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, Notas, IDSupervisor, LastUpdate from planificaciondia "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString PlanificacionesDias::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select Dia, Notas, IDSupervisor, sent, EstadoPlanificacion, RecordStatus from planificaciondia ")
            + QString(" where RecordStatus <> ") + QString::number(DELETED) + QString(";");
}

QString PlanificacionesDias::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select Dia, Notas, IDSupervisor, EstadoPlanificacion from planificaciondia where Dia = :Dia;");
}

void PlanificacionesDias::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    PlanificacionDiaPtr p = PlanificacionDiaPtr::create(this);

    p->Dia().setValue(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
    p->Notas().setValue((*record)["Notas"].toString());
    p->IDSupervisor().setValue((*record)["IDSupervisor"].toInt());
    p->EstadoPlanificacion().setValue((EstadosPlanificacion)(*record)["EstadoPlanificacion"].toInt());
    p->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));

    if (setNew)
        p->setNew();
    else
        p->setInitialized();

    m_Planificaciones[p->Dia().value()] = p;
}

void PlanificacionesDias::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    PlanificacionDiaPtr p = m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];

    p->Notas().setValue((*record)["Notas"].toString());
    p->IDSupervisor().setValue((*record)["IDSupervisor"].toInt());
    p->EstadoPlanificacion().setValue((EstadosPlanificacion)(*record)["EstadoPlanificacion"].toInt());
    if (isFromSincro)
    {
        p->setInMemoryRecordStatus(UNMODIFIED);
        p->setLocalRecordStatus(UNMODIFIED);
    }
}

void PlanificacionesDias::deleteRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    m_Planificaciones.remove(QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date());
}

bool PlanificacionesDias::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    return (PlanificacionDiaPtr() != m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()]);
}

bool PlanificacionesDias::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    PlanificacionDiaPtr p = m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    if (p != PlanificacionDiaPtr())
    {
        return p->isEqualsTo(record);
    }
    else
        return false;
}

bool PlanificacionesDias::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    PlanificacionDiaPtr p = m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return p->isUnSent();
}

RecordPtr PlanificacionesDias::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return RecordPtr();
    PlanificacionDiaPtr p = m_Planificaciones[QDateTime::fromMSecsSinceEpoch((*record)["Dia"].toLongLong()).date()];
    return p->asRecordPtr();
}


QString PlanificacionesDias::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondia "
                   " set RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia;").arg(DELETED);
}

QString PlanificacionesDias::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondia "
                   " set RecordStatus = %1, sent = 0 "
                   " where Dia = :Dia;").arg(DELETED);
}

QString PlanificacionesDias::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondia "
                   " set Notas = :Notas, IDSupervisor = :IDSupervisor, "
                   " RecordStatus = %1, EstadoPlanificacion = :EstadoPlanificacion, sent = 0 "
                   " where Dia = :Dia;").arg(MODIFIED);
}

QString PlanificacionesDias::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update planificaciondia "
                   " set Notas = :Notas, IDSupervisor = :IDSupervisor, "
                   " RecordStatus = %1, EstadoPlanificacion = :EstadoPlanificacion, sent = 0 "
                   " where Dia = :Dia;").arg(MODIFIED);
}

QString PlanificacionesDias::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificaciondia "
                   " (Dia, Notas, IDSupervisor, RecordStatus, EstadoPlanificacion, sent) "
                   " values "
                   " (:Dia, :Notas, :IDSupervisor, %1, :EstadoPlanificacion, 0);").arg(NEW);
}

QString PlanificacionesDias::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return QString("insert into planificaciondia "
                   " (Dia, Notas, IDSupervisor, RecordStatus, EstadoPlanificacion, sent) "
                   " values "
                   " (:Dia, :Notas, :IDSupervisor, %1, :EstadoPlanificacion, 0);").arg(NEW);
}

RecordSet PlanificacionesDias::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = RecordSet::create();
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
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

RecordSet PlanificacionesDias::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = RecordSet::create();
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (p->isUnSent())
            res->push_back(p->asRecordPtr());
    }
    return res;
}

void PlanificacionesDias::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Date")
         << tr("Day")
         << tr("Supervisor")
         << tr("Notes")
         << tr("Estimated hours")
         << tr("Planned hours")
         << tr("Status")
         << tr("Complete");
}

QSharedPointer<QList<QStringList>> PlanificacionesDias::getAll()
{
    QLOG_TRACE_FN();
    QSharedPointer<QList<QStringList>> res = QSharedPointer<QList<QStringList>>::create();

    PlanificacionDiaLst lst = getAll(false);

    foreach(PlanificacionDiaPtr p, *lst)
    {
        QStringList r;
        r << p->Dia().value().toString()
          << (p->Supervisor() == EmpleadoPtr() ? "" : p->Supervisor()->Apellido().value() + ", " + p->Supervisor()->Nombre().value())
          << QString::number(p->Estimacion()->EstimacionHoras().value())
          << QString::number(p->HorasPlanificadas())
          << p->Estado();
        res->push_back(r);
    }
    return res;
}

void PlanificacionesDias::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    PlanificacionDiaLst planificaciones = this->getAll(false);
    foreach(PlanificacionDiaPtr p, *planificaciones)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, p->Dia().value().toString(Qt::ISODate));
        item->setData(0, Qt::UserRole, p->Dia().value());
        item->setText(1, p->Dia().value().toString("dddd"));
        if (p->IDSupervisor().isNull() || p->IDSupervisor().value() == -1)
            item->setText(2, "");
        else
            item->setText(2, p->Supervisor()->Apellido().value());
        item->setText(3, p->Notas().value());
        if (p->Estimacion() != EstimacionDiaPtr())
            item->setText(4, QString::number(p->Estimacion()->EstimacionHoras().value()));
        item->setText(5, QString::number(p->HorasPlanificadas()));
        item->setText(6, p->Estado());
        item->setText(7, (p->isEverythingAssigned() ? tr("Yes") : tr("No")));
        tree.insertTopLevelItem(0, item);
    }
}

bool PlanificacionesDias::addNew()
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    PlanificacionDiaPtr p;
    p = getByDay(ID.toDate(), false);

    bool editInReadOnly = !planUnderEdition.isNull();
    if (p.data())
    {
        if (!p->EstadoPlanificacion().isNull())
            editInReadOnly = editInReadOnly && (p->EstadoPlanificacion().value() != INPROGRESS);
    }

    if (!p.data())
        p = PlanificacionDiaPtr::create(ID.toDate(), this);

    DlgPlanificacionDia *dlg = new DlgPlanificacionDia();

    if (!editInReadOnly)
    {
        planUnderEdition = p;
        connect(dlg, SIGNAL(accepted(DlgPlanificacionDia*)), this, SLOT(on_DlgEditAccepted(DlgPlanificacionDia*)));
    }
    connect(dlg, SIGNAL(rejected(DlgPlanificacionDia*)), this, SLOT(on_DlgCancelled(DlgPlanificacionDia*)));
    dlg->setData(p, editInReadOnly);

    dlg->setWindowState(dlg->windowState() | Qt::WindowMaximized);
    dlg->show();
    dlg->setFocus();
    dlg->activateWindow();
    return false;
}

void PlanificacionesDias::on_DlgCancelled(DlgPlanificacionDia *dialog)
{
    dialog->deleteLater();
    if (dialog->getData() == planUnderEdition)
    {
        planUnderEdition = PlanificacionDiaPtr(NULL);
    }
}

void PlanificacionesDias::on_DlgEditAccepted(DlgPlanificacionDia *dialog)
{
    planUnderEdition->Dia().setValue(dialog->Dia());
    planUnderEdition->Notas().setValue(dialog->Notas());
    planUnderEdition->IDSupervisor().setValue(dialog->IDSupervisor());

    planUnderEdition->updatePlanificaciones(dialog->Planificaciones());
    m_Planificaciones[planUnderEdition->Dia().value()] = planUnderEdition;
    planUnderEdition->setParent(this);
    planUnderEdition = PlanificacionDiaPtr(NULL);
    dialog->deleteLater();
    emit requestSave();
}

bool PlanificacionesDias::deleteElement(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Planificaciones.find(ID.toDate()) != m_Planificaciones.end())
    {
        m_Planificaciones[ID.toDate()]->setDeleted();
        m_Planificaciones.remove(ID.toDate());
        result = true;
    }
    return result;
}

bool PlanificacionesDias::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Planificaciones.find(ID.toDate()) != m_Planificaciones.end())
        result = m_Planificaciones[ID.toDate()];
    return result;
}

void PlanificacionesDias::refreshID(int, int)
{
    QLOG_TRACE_FN();
}

PlanificacionDiaLst PlanificacionesDias::getAll(bool includeDeleted)
{
    QLOG_TRACE_FN();
    PlanificacionDiaLst res = PlanificacionDiaLst::create();
    foreach (PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (!p->isPlanificacionDeleted() && !p->isDeleted(false))
            res->push_back(p);
        else
            if (includeDeleted)
                res->push_back(p);
    }
    return res;
}

PlanificacionDiaPtr PlanificacionesDias::getByDay(QDate day, bool includeDeleted)
{
    QLOG_TRACE_FN();
    if (m_Planificaciones.find(day) == m_Planificaciones.end())
        return PlanificacionDiaPtr();
    else
    {
        PlanificacionDiaPtr p = m_Planificaciones[day];
        if (!p->isDeleted(true))
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


PlanificacionDiaLst PlanificacionesDias::getAllReadyForApproval()
{
    QLOG_TRACE_FN();
    PlanificacionDiaLst res = PlanificacionDiaLst::create();
    foreach (PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (p->isReadyForApproval())
            res->push_back(p);
    }
    return res;
}


void PlanificacionesDias::saveDependants()
{
    QLOG_TRACE_FN();
    DataStore::instance()->getPlanificacionesSubSectores()->save();
}

void PlanificacionesDias::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<QDate> toDelete;
    foreach(PlanificacionDiaPtr p, m_Planificaciones.values())
    {
        if (removeDeleted && p->isDeleted(true))
            toDelete.push_back(p->Dia().value());
        else
        {
            if (impactInMemmory)
                p->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                p->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(QDate dt, toDelete)
    {
        m_Planificaciones.remove(dt);
    }
}

QSharedPointer<QList<QAction*>> PlanificacionesDias::getActions()
{
    QLOG_TRACE_FN();
    QSharedPointer<QList<QAction*>> actions = QSharedPointer<QList<QAction*>>::create();

    QAction *action = new QAction(tr("Approve"), NULL);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon2);
    connect(action, SIGNAL(triggered()),
            DataStore::instance()->getEstimacionesDias().data(),
            SLOT(approveSelected()));
    actions->push_back(action);

    return actions;
}

bool PlanificacionesDias::printSelectedRecord(QVariant IDElement, QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    PlanificacionDiaPtr p;
    p = getByDay(IDElement.toDate(), false);
    if (p.data())
    {
        return p->print(textDoc);
    }
    return false;
}
