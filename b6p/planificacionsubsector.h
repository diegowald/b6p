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
#ifndef PLANIFICACIONSUBSECTOR_H
#define PLANIFICACIONSUBSECTOR_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
#include "subsector.h"
#include "empleado.h"

class PlanificacionSubSector;
typedef boost::shared_ptr<PlanificacionSubSector> PlanificacionSubSectorPtr;
typedef boost::shared_ptr<QList<PlanificacionSubSectorPtr> > PlanificacionSubSectorLst;


class PlanificacionSubSector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit PlanificacionSubSector(QObject *parent = 0);
    virtual ~PlanificacionSubSector();

    NullableField<int> &IDRecord();
    NullableField<QDate> &Dia();
    NullableField<int> &IDSector();
    NullableField<int> &IDSubSector();
    NullableField<int> &IDEmpleado();
    NullableField<int> &HoraInicio();
    NullableField<int> &HoraFin();
    NullableField<bool> &AllowOverWorking();

    SectorPtr getSector();
    SubSectorPtr getSubsector();
    EmpleadoPtr getEmpleado();

    void updateID(int newID);

    bool isEqualsTo(PlanificacionSubSectorPtr other);
    void updateWith(PlanificacionSubSectorPtr other);

    virtual RecordPtr asRecordPtr();
    virtual bool isEqualsTo(RecordPtr record);

    double CantidadHoras();

signals:
    
public slots:
    
private:
    NullableField<int> m_IDRecord;
    NullableField<QDate> m_Dia;
    NullableField<int> m_IDSector;
    NullableField<int> m_IDSubSector;
    NullableField<int> m_IDEmpleado;
    NullableField<int> m_HoraInicio;
    NullableField<int> m_HoraFin;
    NullableField<bool> m_AllowOverworking;
};


#endif // PLANIFICACIONSUBSECTOR_H
