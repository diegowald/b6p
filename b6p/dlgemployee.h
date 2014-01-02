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
#ifndef DLGEMPLOYEE_H
#define DLGEMPLOYEE_H

#include <QDialog>
#include "empleado.h"
#include "availabilitywidget.h"

namespace Ui {
class DlgEmployee;
}

class DlgEmployee : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgEmployee(QWidget *parent = 0);
    ~DlgEmployee();

    void setData(EmpleadoPtr empleado);

    QString Apellido();
    QString Nombres();
    QDate FechaIngreso();
    QString Legajo();
    CapacidadPersonaSectorLst Capacities();
    CalendarioPersonaLst Disponibilidades();

protected:
    void setupScreen();
    void setupAssignment(AvailabilityWidget* w, int day);
    CalendarioPersonaPtr getAssignment(AvailabilityWidget *w);

private slots:
    void on_btnAdd_pressed();

    void on_btnDelete_pressed();

    void on_btnAdd_2_clicked();

    void on_btnEdit_2_clicked();

    void on_btnDelete_2_clicked();

private:
    Ui::DlgEmployee *ui;
    EmpleadoPtr m_Empleado;
};

#endif // DLGEMPLOYEE_H
