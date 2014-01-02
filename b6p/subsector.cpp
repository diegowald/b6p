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
#include "subsector.h"
#include "datastore.h"
#include <QsLog.h>


SubSector::SubSector(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
    m_IDSector.setNull();
    m_IDSubSector.setNull();
    m_Nombre.setNull();
    m_Descripcion.setNull();

    m_IDSector.setParent(this);
    m_IDSubSector.setParent(this);
    m_Nombre.setParent(this);
    m_Descripcion.setParent(this);

}

RecordPtr SubSector::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["IDSector"] = m_IDSector.toVariant();
    (*res)["IDSubSector"] = m_IDSubSector.toVariant();
    (*res)["Nombre"] = m_Nombre.toVariant();
    (*res)["Descripcion"] = m_Descripcion.toVariant();
    (*res)["RecordStatus"] = getLocalRecordStatus();

    (*res)[RECORD_ID] = m_IDSubSector.toVariant();
    return res;
}

bool SubSector::isEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    bool res = ((*record)["IDSector"] == m_IDSector.toVariant())
            && ((*record)["IDSubSector"] == m_IDSubSector.toVariant())
            && ((*record)["Nombre"] == m_Nombre.toVariant())
            && ((*record)["Descripcion"] == m_Descripcion.toVariant());
    return res;
}

NullableField<int> &SubSector::IDSector()
{
    QLOG_TRACE_FN();
    return m_IDSector;
}

NullableField<int> &SubSector::IDSubsector()
{
    QLOG_TRACE_FN();
    return m_IDSubSector;
}

NullableField<QString> &SubSector::Nombre()
{
    QLOG_TRACE_FN();
    return m_Nombre;
}

NullableField<QString> &SubSector::Descripcion()
{
    QLOG_TRACE_FN();
    return m_Descripcion;
}

SectorPtr SubSector::getSector()
{
    QLOG_TRACE_FN();
    return DataStore::instance()->getSectores()->getSector(m_IDSector.value());
}
