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
#include "calendariopersona.h"
#include "datastore.h"
#include <QsLog.h>

CalendarioPersona::CalendarioPersona(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_Dia.setNull();
    m_IDEmpleado.setNull();
    m_HoraIngreso1.setNull();
    m_HoraEgreso1.setNull();
    m_HoraIngreso2.setNull();
    m_HoraEgreso2.setNull();

    m_Dia.setParent(this);
    m_IDEmpleado.setParent(this);
    m_HoraIngreso1.setParent(this);
    m_HoraEgreso1.setParent(this);
    m_HoraIngreso2.setParent(this);
    m_HoraEgreso2.setParent(this);
}

RecordPtr CalendarioPersona::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr::create();

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["IDEmpleado"] = m_IDEmpleado.toVariant();
    (*res)["HoraIngreso"] = m_HoraIngreso1.toVariant();
    (*res)["HoraEgreso"] = m_HoraEgreso1.toVariant();
    (*res)["HoraIngreso2"] = m_HoraIngreso2.toVariant();
    (*res)["HoraEgreso2"] = m_HoraEgreso2.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();
    return res;
}

bool CalendarioPersona::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["Dia"] == m_Dia.toVariant())
            && ((*record)["IDEmpleado"] == m_IDEmpleado.toVariant())
            && ((*record)["HoraIngreso"] == m_HoraIngreso1.toVariant())
            && ((*record)["HoraEgreso"] == m_HoraEgreso1.toVariant())
            && ((*record)["HoraIngreso2"] == m_HoraIngreso2.toVariant())
            && ((*record)["HoraEgreso2"] == m_HoraEgreso2.toVariant());
    return res;
}

NullableField<int> &CalendarioPersona::Dia()
{
    QLOG_TRACE_FN();
    return m_Dia;
}

NullableField<int> &CalendarioPersona::IDEmpleado()
{
    QLOG_TRACE_FN();
    return m_IDEmpleado;
}

NullableField<int> &CalendarioPersona::HoraIngreso1()
{
    QLOG_TRACE_FN();
    return m_HoraIngreso1;
}

NullableField<int> &CalendarioPersona::HoraEgreso1()
{
    QLOG_TRACE_FN();
    return m_HoraEgreso1;
}

NullableField<int> &CalendarioPersona::HoraIngreso2()
{
    QLOG_TRACE_FN();
    return m_HoraIngreso2;
}

NullableField<int> &CalendarioPersona::HoraEgreso2()
{
    QLOG_TRACE_FN();
    return m_HoraEgreso2;
}

bool CalendarioPersona::EqualsTo(CalendarioPersonaPtr other)
{
    QLOG_TRACE_FN();
    return ((m_Dia.value() == other->Dia().value())
            && m_IDEmpleado.value() == other->IDEmpleado().value());
}

void CalendarioPersona::updateWith(CalendarioPersonaPtr other)
{
    QLOG_TRACE_FN();
    if (other->HoraIngreso1().isNull())
        m_HoraIngreso1.setNull();
    else
        m_HoraIngreso1.setValue(other->HoraIngreso1().value());

    if (other->HoraEgreso1().isNull())
        m_HoraEgreso1.setNull();
    else
        m_HoraEgreso1.setValue(other->HoraEgreso1().value());

    if (other->HoraIngreso2().isNull())
        m_HoraIngreso2.setNull();
    else
        m_HoraIngreso2.setValue(other->HoraIngreso2().value());

    if (other->HoraEgreso2().isNull())
        m_HoraEgreso2.setNull();
    else
        m_HoraEgreso2.setValue(other->HoraEgreso2().value());
}

void CalendarioPersona::updateIDEmpleado(int newId)
{
    QLOG_TRACE_FN();
    m_IDEmpleado.setValue(newId);
}

bool CalendarioPersona::canWork(int Dia, int HoraInicio, int HoraFin)
{
    QLOG_TRACE_FN();
    if (m_Dia.value() != Dia)
        return false;

    bool canWorkOnTimeWindow1 = true;
    if (HoraInicio < m_HoraIngreso1.value())
        canWorkOnTimeWindow1 = false;

    if (HoraFin > m_HoraEgreso1.value())
        canWorkOnTimeWindow1 = false;

    bool canWorkOnTimeWindow2 = true;
    if (HoraInicio < m_HoraIngreso2.value())
        canWorkOnTimeWindow2 = false;

    if (HoraFin > m_HoraEgreso2.value())
        canWorkOnTimeWindow2 = false;



    return canWorkOnTimeWindow1 || canWorkOnTimeWindow2;
}

bool CalendarioPersona::canWork(int Dia)
{
    QLOG_TRACE_FN();
    return ((m_Dia.value() == Dia) && (cantWorkingHours() > 0));
}

int CalendarioPersona::cantWorkingHours()
{
    return (m_HoraEgreso1.value() - m_HoraIngreso1.value()) +
            (m_HoraEgreso2.value() - m_HoraIngreso1.value());
}
