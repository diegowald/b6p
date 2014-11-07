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
#include "planificacionsubsector.h"
#include "datastore.h"
#include <QsLog.h>

PlanificacionSubSector::PlanificacionSubSector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDRecord.setNull();
    m_Dia.setNull();
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_IDEmpleado.setNull();
    m_HoraInicio.setNull();
    m_HoraFin.setNull();
    m_AllowOverworking.setValue(false);

    m_Dia.setParent(this);
    m_IDSector.setParent(this);
    m_IDSubSector.setParent(this);
    m_IDEmpleado.setParent(this);
    m_HoraInicio.setParent(this);
    m_HoraFin.setParent(this);
    m_AllowOverworking.setParent(this);
}

PlanificacionSubSector::~PlanificacionSubSector()
{

}

RecordPtr PlanificacionSubSector::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr::create();

    (*res)["IDRecord"] = m_IDRecord.toVariant();
    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_IDSubSector.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["HoraInicio"] = m_HoraInicio.toVariant();
    (*res)["HoraFin"] = m_HoraFin.toVariant();
    (*res)["AllowOverWorking"] = m_AllowOverworking.value() ? 1 : 0;
    (*res)["RecordStatus"] = getLocalRecordStatus();

    (*res)[RECORD_ID] = m_IDRecord.toVariant();

    return res;
}

bool PlanificacionSubSector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["IDRecord"] == m_IDRecord.toVariant())
            && ((*record)["Dia"] == m_Dia.toVariant())
            && ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["IDSubSector"] == m_IDSubSector.toVariant())
            && ((*record)["IDEmpleado"] == m_IDEmpleado.toVariant())
            && ((*record)["HoraInicio"] == m_HoraInicio.toVariant())
            && ((*record)["HoraFin"] == m_HoraFin.toVariant())
            && ((*record)["AllowOverWorking"] == (m_AllowOverworking.value() ? 1 : 0));
    return res;
}

NullableField<int> &PlanificacionSubSector::IDRecord()
{
    QLOG_TRACE_FN();
    return m_IDRecord;
}

NullableField<QDate> &PlanificacionSubSector::Dia()
{
    QLOG_TRACE_FN();
    return m_Dia;
}

NullableField<int> &PlanificacionSubSector::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<int> &PlanificacionSubSector::IDSubSector()
{
    QLOG_TRACE_FN();
    return m_IDSubSector;
}

NullableField<int> &PlanificacionSubSector::IDEmpleado()
{
    QLOG_TRACE_FN();
    return m_IDEmpleado;
}

NullableField<int> &PlanificacionSubSector::HoraInicio()
{
    QLOG_TRACE_FN();
    return m_HoraInicio;
}

NullableField<int> &PlanificacionSubSector::HoraFin()
{
    QLOG_TRACE_FN();
    return m_HoraFin;
}

NullableField<bool> &PlanificacionSubSector::AllowOverWorking()
{
    QLOG_TRACE_FN();
    return m_AllowOverworking;
}

SectorPtr PlanificacionSubSector::getSector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}

SubSectorPtr PlanificacionSubSector::getSubsector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSubSectores()->getSubSector(m_IDSubSector.value());
}

EmpleadoPtr PlanificacionSubSector::getEmpleado()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getEmpleados()->getEmpleado(m_IDEmpleado.value(), false);
}

double PlanificacionSubSector::CantidadHoras()
{
    QLOG_TRACE_FN();
    if (m_HoraFin.isNull())
        return 0;
    if (m_HoraInicio.isNull())
        return 0;
    return (m_HoraFin.value() - m_HoraInicio.value()) / 3600;
}

bool PlanificacionSubSector::isEqualsTo(PlanificacionSubSectorPtr other)
{
    QLOG_TRACE_FN();
    return (m_IDRecord.value() == other->IDRecord().value());
}

void PlanificacionSubSector::updateWith(PlanificacionSubSectorPtr other)
{
    QLOG_TRACE_FN();
    if (other->Dia().isNull())
        m_Dia.setNull();
    else
        m_Dia.setValue(other->Dia().value());

    if (other->IDSector().isNull())
        m_IDSector.setNull();
    else
        m_IDSector.setValue(other->IDSector().value());

    if (other->IDSubSector().isNull())
        m_IDSubSector.setNull();
    else
        m_IDSubSector.setValue(other->IDSubSector().value());

    if (other->IDEmpleado().isNull())
        m_IDEmpleado.setNull();
    else
        m_IDEmpleado.setValue(other->IDEmpleado().value());

    if (other->HoraInicio().isNull())
        m_HoraInicio.setNull();
    else
        m_HoraInicio.setValue(other->HoraInicio().value());

    if (other->HoraFin().isNull())
        m_HoraFin.setNull();
    else
        m_HoraFin.setValue(other->HoraFin().value());

    m_AllowOverworking.setValue(other->AllowOverWorking());
}

void PlanificacionSubSector::updateID(int newID)
{
    QLOG_TRACE_FN();
    m_IDRecord.setValue(newID);
    setUnmodified();
}

bool PlanificacionSubSector::isPlanificacionDeleted()
{
    QLOG_TRACE_FN();
    PlanificacionDiaPtr planificacion = DataStore::instance()->getPlanificacionesDias()->getByDay(m_Dia.value(), false);
    if (planificacion == PlanificacionDiaPtr())
        return true; // Assume not existant as deleted.

    return planificacion->isDeleted(false);
}
