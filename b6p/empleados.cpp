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
#include "empleados.h"
#include "genericlist.h"
#include "dlgemployee.h"
#include "datastore.h"
#include <QMultiMap>
#include <QsLog.h>
#include <QSet>

Empleados::Empleados(const QString &dbName, QObject *parent) :
    ACollection(tr("Employees"), "Employees", true, ACollection::MERGE_MANUAL, dbName, parent)
{
    QLOG_TRACE_FN();
}

Empleados::~Empleados()
{
    QLOG_TRACE_FN();
}

QString Empleados::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, Apellido, Nombres, Legajo, FechaIngreso, isBaja, RecordStatus from empleados "
                   " where LastUpdate >= :LASTUPDATE AND SenderMachine <> :SenderMachine;");
}

QString Empleados::getSqlString()
{
    QLOG_TRACE_FN();
    return QString("select ID, Apellido, Nombres, Legajo, FechaIngreso, isBaja, sent, RecordStatus from empleados");
}

void Empleados::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = boost::make_shared<Empleado>(false, this);
    e->IDEmpleado().setValue((*record)["ID"].toInt());
    e->Apellido().setValue((*record)["Apellido"].toString());
    e->Nombre().setValue((*record)["Nombres"].toString());
    e->Legajo().setValue((*record)["Legajo"].toString());
    e->FechaIngreso().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaIngreso"].toLongLong()).date());
    e->IsBaja().setValue((*record)["isBaja"].toBool());
    e->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));



    if (setNew)
        e->setNew();
    else
    {
        if (e->IsBaja().value())
            e->setDeleted();
        e->setInitialized();
    }

    m_Empleados[e->IDEmpleado().value()] = e;
}

void Empleados::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
//Aca debo mostrar una ventana que indique que hay modificaciones locales.
    e->Apellido().setValue((*record)["Apellido"].toString());
    e->Nombre().setValue((*record)["Nombres"].toString());
    e->Legajo().setValue((*record)["Legajo"].toString());
    e->FechaIngreso().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaIngreso"].toLongLong()).date());
    e->IsBaja().setValue((*record)["isBaja"].toBool());
    if (isFromSincro)
    {
        e->setInMemoryRecordStatus(UNMODIFIED);
        e->setLocalRecordStatus(UNMODIFIED);
    }
}

void Empleados::deleteRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
    e->IsBaja().setValue(true);
    if (isFromSincro)
    {
        e->setInMemoryRecordStatus(UNMODIFIED);
        e->setLocalRecordStatus(UNMODIFIED);
    }
}

bool Empleados::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
    return (e != EmpleadoPtr());
}

bool Empleados::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
    if (e != EmpleadoPtr())
    {
        return e->isEqualsTo(record, getFieldsToShowInMerge());
    }
    else
        return false;
}

bool Empleados::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
    return e->isUnSent();
}

RecordPtr Empleados::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = getEmpleado((*record)["ID"].toInt(), true);
    return e->asRecordPtr();
}

QStringList Empleados::getFieldsToShowInMerge()
{
    QLOG_TRACE_FN();
    return QStringList() << "Apellido"
                         << "Legajo"
                         << "Nombres";
}

QString Empleados::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update empleados set isBaja = 1, RecordStatus = %1, sent = 0 where ID = :RECORD_ID;").arg(DELETED);
}

QString Empleados::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update empleados set isBaja = 1, RecordStatus = %1, sent = 0, SenderMachine = :SenderMachine where ID = :RECORD_ID;").arg(DELETED);
}

QString Empleados::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update empleados set Apellido = :Apellido, Nombres = :Nombres, "
                   " Legajo = :Legajo, FechaIngreso = :FechaIngreso, RecordStatus = %1, isBaja = :isBaja, sent = 0  where ID = :RECORD_ID;").arg(MODIFIED);
}

QString Empleados::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update empleados set Apellido = :Apellido, Nombres = :Nombres, "
                   " Legajo = :Legajo, FechaIngreso = :FechaIngreso, RecordStatus = %1, isBaja = :isBaja, sent = 0, "
                   " SenderMachine = :SenderMachine where ID = :RECORD_ID;").arg(MODIFIED);
}

QString Empleados::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("Apellido");
    parameters.append(":Apellido");

    fields.append("Nombres");
    parameters.append(":Nombres");

    fields.append("Legajo");
    parameters.append(":Legajo");

    fields.append("FechaIngreso");
    parameters.append(":FechaIngreso");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));

    fields.append("isBaja");
    parameters.append("0");

    fields.append("sent");
    parameters.append("0");

    QString sql = "insert into empleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}

QString Empleados::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("ID");
    parameters.append(":RECORD_ID");

    fields.append("Apellido");
    parameters.append(":Apellido");

    fields.append("Nombres");
    parameters.append(":Nombres");

    fields.append("Legajo");
    parameters.append(":Legajo");

    fields.append("FechaIngreso");
    parameters.append(":FechaIngreso");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));

    fields.append("isBaja");
    parameters.append("0");

    fields.append("sent");
    parameters.append("0");

    fields.append("SenderMachine");
    parameters.append(":SenderMachine");

    QString sql = "insert into empleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}

QString Empleados::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID from empleados "
                   " where ID = :RECORD_ID ;");
}

RecordSet Empleados::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        switch (status)
        {
        case NEW:
            if (e->isNew(fromMemory))
                res->push_back(e->asRecordPtr());
            break;
        case MODIFIED:
            if (e->isModified(fromMemory))
                res->push_back(e->asRecordPtr());
            break;
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

RecordSet Empleados::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        if (e->isUnSent())
            res->push_back(e->asRecordPtr());
    }
    return res;
}

EmpleadoPtr Empleados::getEmpleado(int idEmpleado, bool includeDeleted)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
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

EmpleadosLst Empleados::getPowerUsers()
{
    QLOG_TRACE_FN();
    EmpleadosLst res = boost::make_shared<QList<EmpleadoPtr> >();
    foreach (EmpleadoPtr e, m_Empleados.values())
    {
        if (!e->DadoDeBaja() && e->isPowerUser())
            res->push_back(e);
    }
    return res;
}

EmployeeCalculatedCapacityLst Empleados::getAll(int IDSector, int IDSubSector, QDate Fecha, int HoraInicio, int HoraFin, bool includeDeleted)
{
    QLOG_TRACE_FN();
    EmployeeCalculatedCapacityLst res = boost::make_shared<QList<EmployeeCalculatedCapacityPtr> >();
    QMultiMap<int, EmployeeCalculatedCapacityPtr> candidates;
    foreach(EmpleadoPtr e, m_Empleados.values())
    {
        EmployeeCalculatedCapacityPtr capacity = e->canWork(Fecha, IDSector, IDSubSector, HoraInicio, HoraFin);
        if (capacity->Capacity() > 0)
        {
            if (!e->isDeleted(false) || includeDeleted)
                candidates.insert(capacity->Capacity(), capacity);
        }
    }

    // Ahora recorro de mayor capacidad a menor capacidad y armo la respuesta
    if (candidates.count() > 0)
    {
        QMap<int, EmployeeCalculatedCapacityPtr>::const_iterator it = --candidates.constEnd();
        while (it != candidates.constBegin())
        {
            res->push_back(it.value());
            --it;
        }
        res->push_back(it.value());
    }

    return res;
}

EmpleadosLst Empleados::getAllAvailableByDay(QDate &Fecha, QList<int> &empleadosNoDisponibles, bool incluirLicencias)
{

    QLOG_TRACE_FN();
    EmpleadosLst res = boost::make_shared<QList<EmpleadoPtr> >();
    QSet<int> availables;
    foreach (EmpleadoPtr empleado, m_Empleados.values())
    {
        if (empleado->isAvailable(Fecha, incluirLicencias))
            availables.insert(empleado->IDEmpleado().value());
    }

    QSet<int> notAvailable;
    foreach (int idEmpleado, empleadosNoDisponibles)
    {
        notAvailable.insert(idEmpleado);
    }

    QSet<int> resultado = availables.subtract(notAvailable);

    foreach (int idEmpleado, resultado.values())
    {
        res->push_back(getEmpleado(idEmpleado, true));
    }

    return res;
}

void Empleados::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Lastname")
            << tr("Firstname")
            << tr("ID")
            << tr("Start");
}

boost::shared_ptr<QList<QStringList> > Empleados::getAll()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    EmpleadosLst lst = getAll(false);

    foreach(EmpleadoPtr e, *lst)
    {
        QStringList r;
        r << e->Apellido().value()
          << e->Nombre().value()
          << e->Legajo().value()
          << e->FechaIngreso().value().toString();
        res->push_back(r);
    }

    return res;
}

void Empleados::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    EmpleadosLst emps = getAll(false);
    foreach(EmpleadoPtr emp, *emps)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, emp->Apellido().value());
        item->setData(0, Qt::UserRole, emp->IDEmpleado().value());
        item->setText(1, emp->Nombre().value());
        item->setText(2, emp->Legajo().value());
        item->setText(3, emp->FechaIngreso().value().toString(Qt::ISODate));
        tree.insertTopLevelItem(0, item);
    }
}

bool Empleados::addNew()
{
    QLOG_TRACE_FN();
    int id = -1;
    return edit(id);
}

bool Empleados::edit(QVariant ID)
{
    QLOG_TRACE_FN();
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

        if (ID == -1)
            m_Empleados[e->IDEmpleado().value()] = e;
        return true;
    }
    return false;
}

bool Empleados::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Empleados.find(ID.toInt()) != m_Empleados.end())
    {
        result = m_Empleados[ID.toInt()]->canBeDeleted();
    }
    return result;
}

bool Empleados::deleteElement(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Empleados.find(ID.toInt()) != m_Empleados.end())
    {
        m_Empleados[ID.toInt()]->setDeleted();
        m_Empleados[ID.toInt()]->IsBaja().setValue(true);
        result = true;
    }
    return result;
}

void Empleados::refreshID(int oldID, int newRecordId)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e = m_Empleados[oldID];
    e->updateID(newRecordId);
    m_Empleados.remove(oldID);
    m_Empleados[newRecordId] = e;
}

void Empleados::saveDependants()
{
    QLOG_TRACE_FN();
    DataStore::instance()->getCapacidades()->save();
    DataStore::instance()->getCalendarios()->save();
}

void Empleados::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach (EmpleadoPtr e, m_Empleados.values())
    {
        if (removeDeleted && e->isDeleted(true))
            toDelete.push_back(e->IDEmpleado().value());
        else
        {
            if (impactInMemmory)
                e->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                e->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(int id, toDelete)
        m_Empleados.remove(id);
}

bool Empleados::printSelectedRecord(QVariant IDElement, QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    EmpleadoPtr e;
    if (IDElement.toInt() == -1)
        return false;
    else
        e = getEmpleado(IDElement.toInt(), false);

    return e->print(textDoc);
}
