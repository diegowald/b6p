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
#include "licenciasempleados.h"
#include <QsLog.h>

#include <QDateTime>
#include "dlglicencia.h"
#include "datastore.h"

LicenciasEmpleados::LicenciasEmpleados(QObject *parent) :
    ACollection(tr("RestDays"), "RestDays", true, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

LicenciasEmpleados::~LicenciasEmpleados()
{
    QLOG_TRACE_FN();
}

QString LicenciasEmpleados::getSqlString()
{
    QLOG_TRACE_FN();

    return QString("select ID, IDEmpleado, FechaDesde, FechaHasta, tipoLicencia, descripcion, sent, RecordStatus from licenciasEmpleados");
}

QString LicenciasEmpleados::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, IDEmpleado, FechaDesde, FechaHasta, tipoLicencia, descripcion, sent, RecordStatus from licenciasEmpleados "
                   " where LastUpdate >= :LASTUPDATE AND SenderMachine <> :SenderMachine;");
}

bool LicenciasEmpleados::printSelectedRecord(QVariant, QTextDocument &)
{
    /*QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (IDElement.toInt() == -1)
        return false;
    else
        licencia = getLicencia(IDElement.toInt(), false);

    return licencia->print(textDoc);*/
    return false;
}

void LicenciasEmpleados::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = boost::make_shared<LicenciaEmpleado>(false, this);
    licencia->ID().setValue((*record)["ID"].toInt());
    licencia->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    licencia->FechaDesde().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaDesde"].toLongLong()).date());
    licencia->FechaHasta().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaHasta"].toLongLong()).date());
    licencia->TipoLicencia().setValue((*record)["tipoLicencia"].toString());
    licencia->Descripcion().setValue((*record)["descripcion"].toString());
    licencia->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));

    if (setNew)
        licencia->setNew();
    else
    {
        licencia->setInitialized();
    }

    m_Licencias[licencia->ID().value()] = licencia;
}

bool LicenciasEmpleados::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return (licencia != LicenciaEmpleadoPtr());
}

void LicenciasEmpleados::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    licencia->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    licencia->FechaDesde().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaDesde"].toLongLong()).date());
    licencia->FechaHasta().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaHasta"].toLongLong()).date());
    licencia->TipoLicencia().setValue((*record)["TipoLicencia"].toString());
    licencia->Descripcion().setValue((*record)["Descripcion"].toString());
    if (isFromSincro)
    {
        licencia->setInMemoryRecordStatus(UNMODIFIED);
        licencia->setLocalRecordStatus(UNMODIFIED);
    }
}

void LicenciasEmpleados::deleteRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    licencia->setDeleted();// setValue(true);
    if (isFromSincro)
    {
        licencia->setInMemoryRecordStatus(UNMODIFIED);
        licencia->setLocalRecordStatus(UNMODIFIED);
    }
}

bool LicenciasEmpleados::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return licencia->isUnSent();
}

RecordPtr LicenciasEmpleados::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return licencia->asRecordPtr();
}

QStringList LicenciasEmpleados::getFieldsToShowInMerge()
{
    QLOG_TRACE_FN();
    return QStringList();
}


void LicenciasEmpleados::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Lastname")
         << tr("Firstname")
         << tr("ID")
         << tr("From")
         << tr("From Day")
         << tr("To")
         << tr("To Day")
         << tr("Type")
         << tr("Notes");
}


boost::shared_ptr<QList<QStringList> > LicenciasEmpleados::getAll()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    LicenciasEmpleadosLst list = getAllLicencias();

    foreach(LicenciaEmpleadoPtr l, *list)
    {
        QStringList r;

        r << QString::number(l->IDEmpleado().value())
          << l->FechaDesde().value().toString()
          << l->FechaHasta().value().toString()
          << l->TipoLicencia().value()
          << l->Descripcion().value();
        res->push_back(r);
    }

    return res;
}

void LicenciasEmpleados::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    LicenciasEmpleadosLst licencias = this->getAllLicencias();
    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, QString::number(licencia->IDEmpleado().value()));
        item->setData(0, Qt::UserRole, licencia->ID().value());

        item->setText(1, licencia->FechaDesde().value().toString(Qt::ISODate));
        item->setText(2, licencia->FechaDesde().value().toString("dddd"));
        item->setText(3, licencia->FechaHasta().value().toString(Qt::ISODate));
        item->setText(4, licencia->FechaHasta().value().toString("dddd"));

        item->setText(5, licencia->TipoLicencia().value());
        item->setText(6, licencia->Descripcion().value());
        tree.addTopLevelItem(item);
    }
}

QString LicenciasEmpleados::getTableName()
{
    return "licenciasEmpleados";
}

QString LicenciasEmpleados::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasEmpleados set RecordStatus = %1, sent = 0 where ID = :RECORD_ID;").arg(DELETED);
}

QString LicenciasEmpleados::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasEmpleados set RecordStatus = %1, sent = 0, "
                   " IDEmpleado = :IDEmpleado, FechaDesde = :FechaDesde, FechaHasta = :FechaHasta, "
                   " tipoLicencia = :tipoLicencia, descripcion = :descripcion WHERE ID = :RECORD_ID").arg(MODIFIED);
}

QString LicenciasEmpleados::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("IDEmpleado");
    parameters.append(":IDEmpleado");

    fields.append("FechaDesde");
    parameters.append(":FechaDesde");

    fields.append("FechaHasta");
    parameters.append(":FechaHasta");

    fields.append("tipoLicencia");
    parameters.append(":tipoLicencia");

    fields.append("descripcion");
    parameters.append(":descripcion");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));


    fields.append("sent");
    parameters.append("0");

    QString sql = "insert into licenciasEmpleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}

QString LicenciasEmpleados::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasEmpleados set RecordStatus = %1, sent = 0, SenderMachine = :SenderMachine where ID = :RECORD_ID;").arg(DELETED);
}

QString LicenciasEmpleados::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasEmpleados set RecordStatus = %1, sent = 0, "
                   " IDEmpleado = :IDEmpleado, FechaDesde = :FechaDesde, FechaHasta = :FechaHasta, "
                   " tipoLicencia = :tipoLicencia, descripcion = :descripcion, "
                   " SenderMachine = :SenderMachine WHERE ID = :RECORD_ID").arg(MODIFIED);
}

QString LicenciasEmpleados::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("ID");
    parameters.append(":RECORD_ID");

    fields.append("IDEmpleado");
    parameters.append(":IDEmpleado");

    fields.append("FechaDesde");
    parameters.append(":FechaDesde");

    fields.append("FechaHasta");
    parameters.append(":FechaHasta");

    fields.append("tipoLicencia");
    parameters.append(":tipoLicencia");

    fields.append("descripcion");
    parameters.append(":descripcion");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));

    fields.append("sent");
    parameters.append("0");

    fields.append("SenderMachine");
    parameters.append(":SenderMachine");

    QString sql = "insert into licenciasEmpleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}


QString LicenciasEmpleados::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID from licenciasEmpleados "
                   " where ID = :RECORD_ID ;");
}

RecordSet LicenciasEmpleados::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        switch (status)
        {
        case NEW:
            if (licencia->isNew(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        case MODIFIED:
            if (licencia->isModified(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        case DELETED:
            if (licencia->isDeleted(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet LicenciasEmpleados::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (licencia->isUnSent())
            res->push_back(licencia->asRecordPtr());
    }
    return res;
}

void LicenciasEmpleados::refreshID(int oldID, int newRecordId)
{
    QLOG_TRACE_FN();
    QLOG_TRACE() << oldID;
    QLOG_TRACE() << m_Licencias.count();
    LicenciaEmpleadoPtr licencia = m_Licencias[-1];
    licencia->updateID(newRecordId);
    m_Licencias.remove(oldID);
    m_Licencias[newRecordId] = licencia;
}

void LicenciasEmpleados::saveDependants()
{
}

void LicenciasEmpleados::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (removeDeleted && licencia->isDeleted(true))
            toDelete.push_back(licencia->ID().value());
        else
        {
            if (impactInMemmory)
                licencia->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                licencia->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(int id, toDelete)
        m_Licencias.remove(id);
}

bool LicenciasEmpleados::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Licencias.find(ID.toInt()) != m_Licencias.end())
    {
        result = m_Licencias[ID.toInt()]->canBeDeleted();
    }
    return result;
}

bool LicenciasEmpleados::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    if (licencia != LicenciaEmpleadoPtr())
    {
        return licencia->isEqualsTo(record, getFieldsToShowInMerge());
    }
    else
        return false;
}

bool LicenciasEmpleados::addNew()
{
    QLOG_TRACE_FN();
    int id = -1;
    return edit(id);
}

bool LicenciasEmpleados::addNewWithAdditionalData(QVariant data)
{
    QLOG_TRACE_FN();
    int id = -1;
    if (data.canConvert(QVariant::List))
    {
        QList<QVariant> aux = data.toList();
        QDate date = aux.at(0).toDate();
        int idEmpleado = aux.at(1).toInt();
        return editWithIDEmpleado(id, idEmpleado, date, date.addDays(1));
    }
    else
    {
        QDate date = QDate::currentDate();
        return editWithIDEmpleado(id, data.toInt(), date, date.addDays(1));
    }
}

bool LicenciasEmpleados::edit(QVariant ID)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (ID == -1)
        licencia = boost::make_shared<LicenciaEmpleado>(true, this);
    else
        licencia = getLicencia(ID.toInt(), false);
    DlgLicencia dlg;
    dlg.setData(licencia);
    if (dlg.exec() == QDialog::Accepted)
    {
        licencia->IDEmpleado().setValue(dlg.IDEmpleado());
        licencia->FechaDesde().setValue(dlg.FechaDesde());
        licencia->FechaHasta().setValue(dlg.FechaHasta());
        licencia->TipoLicencia().setValue(dlg.TipoLicencia());
        licencia->Descripcion().setValue(dlg.Descripcion());

        m_Licencias[licencia->ID().value()] = licencia;
        return true;
    }
    return false;
}

bool LicenciasEmpleados::editWithIDEmpleado(int ID, int idEmpleado, const QDate& fechaDesde, const QDate& fechaHasta)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (ID == -1)
    {
        licencia = boost::make_shared<LicenciaEmpleado>(true, this);
        licencia->IDEmpleado().setValue(idEmpleado);
        licencia->FechaDesde().setValue(fechaDesde);
        licencia->FechaHasta().setValue(fechaHasta);
    }
    else
        licencia = getLicencia(ID, false);
    DlgLicencia dlg;
    dlg.setData(licencia);
    if (dlg.exec() == QDialog::Accepted)
    {
        licencia->IDEmpleado().setValue(dlg.IDEmpleado());
        licencia->FechaDesde().setValue(dlg.FechaDesde());
        licencia->FechaHasta().setValue(dlg.FechaHasta());
        licencia->TipoLicencia().setValue(dlg.TipoLicencia());
        licencia->Descripcion().setValue(dlg.Descripcion());
        QLOG_TRACE() << licencia->ID().value();
        m_Licencias[licencia->ID().value()] = licencia;
        return true;
    }
    return false;
}

bool LicenciasEmpleados::addNew(QTreeWidgetItem *)
{
    return false;
}

bool LicenciasEmpleados::edit(QTreeWidgetItem *, QVariant)
{
    return false;
}

bool LicenciasEmpleados::deleteElement(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Licencias.find(ID.toInt()) != m_Licencias.end())
    {
        m_Licencias[ID.toInt()]->setDeleted();
        result = true;
    }
    return result;
}


LicenciaEmpleadoPtr LicenciasEmpleados::getLicencia(int idLicencia, bool /*includeDeleted*/)
{
    QLOG_TRACE_FN();
    if (m_Licencias.find(idLicencia) == m_Licencias.end())
        return LicenciaEmpleadoPtr();
    else
    {
        LicenciaEmpleadoPtr licencia = m_Licencias[idLicencia];
        return licencia;
    }
}


LicenciasEmpleadosLst LicenciasEmpleados::getAllLicencias()
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        licencias->push_back(licencia);
    }
    return licencias;
}

LicenciasEmpleadosLst LicenciasEmpleados::getAllLicencias(const QDate &from, const QDate &to)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        bool valido = false;
        if ((from <= licencia->FechaDesde().value()) && (licencia->FechaDesde().value() <= to))
            valido = true;

        if (!valido && ((from <= licencia->FechaHasta().value()) && (licencia->FechaHasta().value() <= to)))
            valido = true;

        if (!valido && ((licencia->FechaDesde().value() <= from) && (from <= licencia->FechaHasta().value())))
            valido = true;

        if (!valido && ((licencia->FechaDesde().value() <= to) && (to <= licencia->FechaHasta().value())))
            valido = true;

        if (valido)
            licencias->push_back(licencia);
    }
    return licencias;
}

LicenciasEmpleadosLst LicenciasEmpleados::getAllLicencias(const QDate& date)
{
    QLOG_TRACE_FN();
    QDate from = date;
    QDate to = date.addDays(1);
    return getAllLicencias(from, to);
}

LicenciasEmpleadosLst LicenciasEmpleados::getFrancos(QDate &date)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    QString TipoFranco = DataStore::instance()->getParametros()->getFrancoType();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->FechaDesde().value() <= date) && (date <= licencia->FechaHasta().value()) && (licencia->TipoLicencia().value() == TipoFranco))
        {
            licencias->push_back(licencia);
        }
    }
    return licencias;
}

LicenciasEmpleadosLst LicenciasEmpleados::getAllLicenciasEmpleado(int idEmpleado)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (licencia->IDEmpleado().value() == idEmpleado)
            licencias->push_back(licencia);
    }
    return licencias;
}

LicenciaEmpleadoPtr LicenciasEmpleados::getLicenciaEmpleado(int idEmpleado, QDate &date)
{
    QLOG_TRACE_FN();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->IDEmpleado().value() == idEmpleado) && (licencia->contains(date)))
        {
            return licencia;
        }
    }
    return LicenciaEmpleadoPtr();
}

LicenciaEmpleadoPtr LicenciasEmpleados::getUltimoFranco(int idEmpleado, QDate& date)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = getAllLicenciasEmpleado(idEmpleado);
    LicenciasEmpleadosLst licenciasPreviasAFecha = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    QString ultimoFrancoType = DataStore::instance()->getParametros()->getFrancoType();
    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        if ((licencia->FechaDesde().value() <= date) && (date <= licencia->FechaHasta().value())
                && (licencia->TipoLicencia().value() == ultimoFrancoType))
        {
            licenciasPreviasAFecha->push_back(licencia);
        }
    }

    LicenciaEmpleadoPtr ultimaLicencia = LicenciaEmpleadoPtr();
    if (licenciasPreviasAFecha->count() > 0)
    {
        ultimaLicencia = licenciasPreviasAFecha->at(0);
        foreach (LicenciaEmpleadoPtr licencia, *licenciasPreviasAFecha)
        {
            if (ultimaLicencia->FechaHasta().value() < licencia->FechaHasta().value())
            {
                ultimaLicencia = licencia;
            }
        }
    }
    return ultimaLicencia;
}

bool LicenciasEmpleados::isOnLicence(int idEmpleado, QDate &date)
{
    QLOG_TRACE_FN();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->IDEmpleado().value() == idEmpleado) && (licencia->contains(date)))
        {
            return true;
        }
    }
    return false;
}

QStringList LicenciasEmpleados::getDistinctLicenceType()
{
    QLOG_TRACE_FN();
    QSet<QString> set;
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        QLOG_TRACE() << licencia->TipoLicencia().value();
        if ((!licencia->TipoLicencia().isNull()) && (licencia->TipoLicencia().value() != ""))
            set.insert(licencia->TipoLicencia().value());
    }
    return set.toList();
}
