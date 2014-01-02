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
#include "acceso.h"
#include <boost/make_shared.hpp>
#include <QsLog.h>

Acceso::Acceso(QObject *parent) : QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDSector.setNull();
    m_Feature.setNull();
    m_canRead.setNull();
    m_canCreate.setNull();
    m_canUpdate.setNull();
    m_canDelete.setNull();

    m_IDSector.setParent(this);
    m_Feature.setParent(this);
    m_canRead.setParent(this);
    m_canCreate.setParent(this);
    m_canUpdate.setParent(this);
    m_canDelete.setParent(this);
}

Acceso::~Acceso()
{
    QLOG_TRACE_FN();
}

RecordPtr Acceso::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["Feature"] = m_Feature.toVariant();
    (*res)["canRead"] = m_canRead.toVariant();
    (*res)["canCreate"] = m_canCreate.toVariant();
    (*res)["canUpdate"] = m_canUpdate.toVariant();
    (*res)["canDelete"] = m_canDelete.toVariant();

    return res;
}

NullableField<int> &Acceso::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<QString> &Acceso::Feature()
{
    QLOG_TRACE_FN();
    return m_Feature;
}

NullableField<bool> &Acceso::canRead()
{
    QLOG_TRACE_FN();
    return m_canRead;
}

NullableField<bool> &Acceso::canCreate()
{
    QLOG_TRACE_FN();
    return m_canCreate;
}

NullableField<bool> &Acceso::canUpdate()
{
    QLOG_TRACE_FN();
    return m_canUpdate;
}

NullableField<bool> &Acceso::canDelete()
{
    QLOG_TRACE_FN();
    return m_canDelete;
}


bool Acceso::CanRead()
{
    QLOG_TRACE_FN();
    return m_canRead.isNull() ? false : m_canRead.value();
}

bool Acceso::CanCreate()
{
    QLOG_TRACE_FN();
    return m_canCreate.isNull() ? false : m_canCreate.value();
}

bool Acceso::CanUpdate()
{
    QLOG_TRACE_FN();
    return m_canUpdate.isNull() ? false : m_canUpdate.value();
}

bool Acceso::CanDelete()
{
    QLOG_TRACE_FN();
    return m_canDelete.isNull() ? false : m_canDelete.value();
}
