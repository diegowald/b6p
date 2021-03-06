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
#ifndef TIMEASSIGNMENTITEMEDIT_H
#define TIMEASSIGNMENTITEMEDIT_H

#include <QWidget>
#include <QDate>
#include <QVariant>
#include "empleado.h"
#include "timeassignment.h"

namespace Ui {
class TimeAssignmentItemEdit;
}

class TimeAssignmentItemEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignmentItemEdit(QWidget *parent = 0);
    ~TimeAssignmentItemEdit();
    
    double CantidadHoras();

    int IDSector();
    bool isSubSectorEmpty();
    int IDSubSector();
    bool isEmpleadoEmpty();
    int IDEmpleado();
    int HoraInicio();
    int HoraFin();
    bool AllowOverWorking();

    void setIDSector(int value);
    void setIDSectorNull();
    void setIDSubSector(int value);
    void setIDSubSectorNull();
    void setIDEmpleado(int value);
    void setIDEmpleadoNull();
    void setHoraInicio(int value);
    void setHoraFin(int value);
    void setAllowOverWorking(bool value);

    void setData(QVariant data);
    QVariant data();

    QDate Date();
    void setDate(QDate value);

    void recalculateColorAssignments(int IDEmpleado);
    void recalculateAvailableEmployees();

signals:
    void AssignmentChanged(int fromSeconds, int toSeconds);
    void calcularHoras(int IDEmpleado, int &horas);
    void refreshColorAssignments();
    void AllowOverWorkingForEmployee(int IDEmpleado);
    void employeeChanged(const QString &empleado);
    void sectorChanged(const QString &sector);
    void subSectorChanged(const QString &subSector);

protected:
    void llenarSectores();
    void llenarSubSectores(int IDSector);
    void llenarEmpleados();
private slots:
    void on_cboSectores_currentIndexChanged(int index);
    void on_timeInicio_TimeChanged(int newTime);
    void on_timeFin_TimeChanged(int newTime);

    void on_cboSubsectores_currentIndexChanged(int index);

    void on_cboEmpleado_currentIndexChanged(int index);
    void on_calcularHorasPreviamenteTrabajadas(int IDEmpleado, int &horas);

private:
    Ui::TimeAssignmentItemEdit *ui;
    QDate date;
    QVariant m_Data;
    EmployeeCalculatedCapacityLst emps;
    bool loadingData;
    bool allowOverWorking;
    int previousSelectedEmployee;
    TimeAssignmentSlot currentAssignment;
};

#endif // TIMEASSIGNMENTITEMEDIT_H
