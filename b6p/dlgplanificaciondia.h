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
#ifndef DLGPLANIFICACIONDIA_H
#define DLGPLANIFICACIONDIA_H

#include <QDialog>
#include "planificaciondia.h"
#include "planificacionsubsector.h"
#include "timeassignmentitemedit.h"


namespace Ui {
class DlgPlanificacionDia;
}

class DlgPlanificacionDia : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgPlanificacionDia(QWidget *parent = 0);
    ~DlgPlanificacionDia();
    void setData(PlanificacionDiaPtr data);
    QDate Dia();
    QString Notas();
    int IDSupervisor();
    PlanificacionSubSectorLst Planificaciones();
private:
    void displayPlannedHours(double hours);
    QStringList getHeaders();
    QStringList getRecord(TimeAssignmentItemEdit *time);
    boost::shared_ptr<QList<QStringList> > getAll();
    void setReadOnly();
    QList<int> getCurrentlyWorkingEmployees();
    void llenarLicencias(const QDate& date, int column);


private slots:
    void on_btnAdd_pressed();
    void on_btnEdit_pressed();
    void slot_AssignmentChanged(int from, int to);

    void on_btnDelete_pressed();
    void on_calcularHoras(int IDEmpleado, int& horas);
    void on_refreshColorAssignments();
    void on_AllowOverWorkingForEmployee(int IDEmpleado);

    void on_btnExport_pressed();

    void on_toolButton_clicked();

private:
    Ui::DlgPlanificacionDia *ui;
    QDate m_Dia;
    int newID;
    QList<int> SubsectorsToDelete;
    int m_HorasEstimadas;
};

#endif // DLGPLANIFICACIONDIA_H
