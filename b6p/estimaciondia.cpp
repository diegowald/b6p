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
#include "estimaciondia.h"
#include "datastore.h"
#include <QsLog.h>

EstimacionDia::EstimacionDia(bool isNew, QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_Dia.setNull();
    m_EstimacionHoras.setNull();

    m_Dia.setParent(this);
    m_EstimacionHoras.setParent(this);

    if (isNew)
    {
        m_Dia.setValue(QDateTime::fromMSecsSinceEpoch(0).date());
        m_EstimacionHoras.setValue(0);
        setNew();
    }
}

RecordPtr EstimacionDia::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = RecordPtr(new Record());

    (*res)["Dia"] = m_Dia.toVariant();
    (*res)["HorasEstimadas"] = m_EstimacionHoras.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();
    return res;
}

bool EstimacionDia::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["Dia"] == m_Dia.toVariant())
            && ((*record)["HorasEstimadas"] == m_EstimacionHoras.toVariant());
    return res;
}

NullableField<QDate> &EstimacionDia::Dia()
{
    QLOG_TRACE_FN();
    return m_Dia;
}

NullableField<int> &EstimacionDia::EstimacionHoras()
{
    QLOG_TRACE_FN();
    return m_EstimacionHoras;
}

bool EstimacionDia::isPlanned()
{
    QLOG_TRACE_FN();
    return (DataStore::instance()->getPlanificacionesDias()->getByDay(m_Dia.value(), false) != PlanificacionDiaPtr());
}

bool EstimacionDia::canBeDeleted()
{
    QLOG_TRACE_FN();
    return true;
}
