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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//Printing
#include <QtPrintSupport/QPrinter>
#include "genericlist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(int LoggedUser, QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void EnableActions();
private slots:
    void on_actionOpen_triggered();
    void on_actionPrint_triggered();
    void on_actionExit_triggered();
    void on_actionView_triggered();
    void on_actionParameters_triggered();
    void on_actionAbout_triggered();
    void datastore_loaded(QString name);
    void datastore_loading(QString name);
    void datastore_saved(QString name);
    void datastore_saving(QString name);
    void on_actionSetup_days_triggered();

    void on_actionSynchronize_triggered();

    void on_actionPrint_Preview_triggered();

    void print(QPrinter *printer);
    void printSelected(QPrinter *printer);

    void on_actionPrint_Selected_triggered();

    void on_actionPrint_Preview_Selected_Record_triggered();

    void on_actionHours_by_Sector_and_Subsector_triggered();

    void on_actionPlanned_hours_day_by_day_triggered();

    void on_actionHours_planned_by_employee_triggered();

    void on_actionPlanned_rests_triggered();

private:
    Ui::MainWindow *ui;
    int m_LoggedUser;
    GenericList *selectedWindowToPrint;
};

#endif // MAINWINDOW_H
