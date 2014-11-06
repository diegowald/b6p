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
#include "licenciaempleado.h"
#include<QsLog.h>
#include <boost/make_shared.hpp>
#include "datastore.h"

LicenciaEmpleado::LicenciaEmpleado(bool isNew, QObject *parent)
    : QObject(parent)
{
    QLOG_TRACE_FN();
    if (isNew)
    {
        id.setValue(-1);
        setNew();
    }
    else
        id.setNull();
}

RecordPtr LicenciaEmpleado::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr::create();

    QLOG_TRACE() << id.toVariant();
    (*res)["ID"] = id.toVariant();
    (*res)["IDEmpleado"] = idEmpleado.toVariant();
    (*res)["FechaDesde"] = fechaDesde.toVariant();
    (*res)["FechaHasta"] = fechaHasta.toVariant();
    (*res)["tipoLicencia"] = tipoLicencia.toVariant();
    (*res)["descripcion"] = descripcion.toVariant();

    (*res)["RecordStatus"] = getLocalRecordStatus(); // Capaz que es inmemoryRecordStatus



    (*res)[RECORD_ID] = idEmpleado.toVariant();
    return res;
}

void LicenciaEmpleado::updateID(int newRecordId)
{
    QLOG_TRACE_FN();
    id.setValue(newRecordId);
}

bool LicenciaEmpleado::canBeDeleted()
{
    return true;
}

bool LicenciaEmpleado::isEqualsTo(RecordPtr record, const QStringList &fieldsToMerge)
{
    QLOG_TRACE_FN();
    bool res = true;
    RecordPtr localRec = asRecordPtr();
    foreach (QString fld, fieldsToMerge) {
        res &= ((*record)[fld] == (*localRec)[fld]);
    }
    res &= ((*record)["RecordStatus"] == (*localRec)["RecordStatus"]);
    return res;
}

NullableField<int> &LicenciaEmpleado::ID()
{
    return id;
}

NullableField<int> &LicenciaEmpleado::IDEmpleado()
{
    return idEmpleado;
}

NullableField<QDate> &LicenciaEmpleado::FechaDesde()
{
    return fechaDesde;
}

NullableField<QDate> &LicenciaEmpleado::FechaHasta()
{
    return fechaHasta;
}

NullableField<QString> &LicenciaEmpleado::TipoLicencia()
{
    return tipoLicencia;
}

NullableField<QString> &LicenciaEmpleado::Descripcion()
{
    return descripcion;
}

bool LicenciaEmpleado::contains(QDate &date)
{
    bool from = fechaDesde.isNull() ? true : (fechaDesde.value() <= date);
    bool to = fechaHasta.isNull() ? true : (date <= fechaHasta.value());

    return from && to;
}
