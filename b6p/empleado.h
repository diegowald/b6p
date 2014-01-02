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
#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QObject>
#include <boost/shared_ptr.hpp>

#include "nullablefield.h"
#include <QDate>

#include "capacidadpersonasector.h"
#include "calendariopersona.h"
#include "days.h"
#include "licenciasempleados.h"

#include <QTextDocument>


class Empleado;
typedef boost::shared_ptr<Empleado> EmpleadoPtr;
typedef boost::shared_ptr<QList<EmpleadoPtr> > EmpleadosLst;

class EmployeeCalculatedCapacity : public QObject
{
    Q_OBJECT
public:
    explicit EmployeeCalculatedCapacity(Empleado* parentEmpleado, QDate Dia);

    void setCapacity(int value);

    Empleado *EmpleadoAsignado();
    int Capacity();
    int HorasPreviamenteTrabajadas();
    int DiasPreviamenteTrabajados();

    bool hasWarningsDias();
    bool hasWarningsHorasMenorAMinimo();
    bool hasWarningsHorasMayorAMaximo();
signals:
    void calcularHorasPreviamenteTrabajadas(int IDEmpleado, int &horas);

public slots:

private:
    Empleado* empleado;
    int capacityForTask;
    QDate dia;
};

typedef boost::shared_ptr<EmployeeCalculatedCapacity> EmployeeCalculatedCapacityPtr;
typedef boost::shared_ptr<QList<EmployeeCalculatedCapacityPtr> > EmployeeCalculatedCapacityLst;

class Empleado : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit Empleado(bool isNew, QObject *parent = 0);
    
    void updateID(int newId);
    NullableField<int> &IDEmpleado();
    NullableField<QString> &Apellido();
    NullableField<QString> &Nombre();
    NullableField<QString> &Legajo();
    NullableField<QDate> &FechaIngreso();
    NullableField<bool> &IsBaja();

    CapacidadPersonaSectorLst Capacities();
    void updateCapacities(CapacidadPersonaSectorLst newCapacities);
    CalendarioPersonaLst Disponibilidades();
    void updateDisponibilidades(CalendarioPersonaLst newDisponibilidades);
    LicenciasEmpleadosLst LicenciasProgramadas();
    LicenciaEmpleadoPtr LicenciaProgramada(QDate& fecha);

    virtual RecordPtr asRecordPtr();
    bool isEqualsTo(RecordPtr record, const QStringList &fieldsToMerge);

    bool DadoDeBaja();
    bool isPowerUser();
    EmployeeCalculatedCapacityPtr canWork(QDate &Fecha, int IDSector, int IDSubSector, int HoraInicio, int HoraFin);
    bool canBeDeleted();
    bool isAvailable(QDate &Fecha, bool incluirLicencias);

    bool print(QTextDocument &textDoc);

signals:
    
public slots:
    
private:
    NullableField<int> idEmpleado;
    NullableField<QString> apellido;
    NullableField<QString> nombre;
    NullableField<QString> legajo;
    NullableField<QDate> fechaIngreso;
    NullableField<bool> isBaja;
};


#endif // EMPLEADO_H
