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
#ifndef PLANIFICACIONDIA_H
#define PLANIFICACIONDIA_H

#include <QObject>
#include <QDate>
#include <QSharedPointer>
#include "nullablefield.h"
#include "empleado.h"
#include "estimaciondia.h"
#include "planificacionsubsector.h"

// printing
#include <QTextDocument>

enum EstadosPlanificacion
{
    INPROGRESS,
    FINISHED,
    APPROVED
};

class PlanificacionDia : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit PlanificacionDia(QDate date, QObject *parent = 0);
    explicit PlanificacionDia(QObject *parent = 0);

    NullableField<QDate> &Dia();
    NullableField<QString> &Notas();
    NullableField<int> &IDSupervisor();
    NullableField<EstadosPlanificacion> &EstadoPlanificacion();
    int HorasPlanificadas();
    EmpleadoPtr Supervisor();
    EstimacionDiaPtr Estimacion();
    virtual RecordPtr asRecordPtr();
    virtual bool isEqualsTo(RecordPtr record);
    QString Estado();
    void approve();

    bool print(QTextDocument &textDoc);
    bool print2(QTextDocument &textDoc);


    bool isEverythingAssigned();
    bool isReadyForApproval();

    void updatePlanificaciones(PlanificacionSubSectorLst dataFrom);
    PlanificacionSubSectorLst getPlanificaciones();

    bool isPlanificacionDeleted();

signals:
    
public slots:
    
private:
    QMultiMap<QString, PlanificacionSubSectorPtr> list2map(PlanificacionSubSectorLst lst);
private:
    NullableField<QDate> m_Dia;
    NullableField<QString> m_Notas;
    NullableField<int> m_IDSupervisor;
    NullableField<EstadosPlanificacion> m_EstadosPlanificacion;
};

typedef QSharedPointer<PlanificacionDia> PlanificacionDiaPtr;
typedef QSharedPointer<QList<PlanificacionDiaPtr> > PlanificacionDiaLst;

#endif // PLANIFICACIONDIA_H
