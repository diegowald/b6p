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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datastore.h"
#include "dlgparametros.h"
#include "dlgsynchronization.h"
#include "dlgfilesynchronization.h"
#include <QMessageBox>


// Printing
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPainter>
#include <QMdiSubWindow>
#include <QDebug>
#include <QTextDocument>

#include <QsLog.h>


MainWindow::MainWindow(int LoggedUser, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    QsLogging::Logger::instance().setLoggingLevel(DataStore::instance()->getParametros()->getLoggingLevel());

    QLOG_TRACE_FN();

    ui->setupUi(this);

    // connecting datastore signals with status bar
    connect(DataStore::instance(), SIGNAL(loaded(QString)),
            this, SLOT(datastore_loaded(QString)));
    connect(DataStore::instance(), SIGNAL(loading(QString)),
            this, SLOT(datastore_loading(QString)));
    connect(DataStore::instance(), SIGNAL(saved(QString)),
            this, SLOT(datastore_saved(QString)));
    connect(DataStore::instance(), SIGNAL(saving(QString)),
            this, SLOT(datastore_saving(QString)));

    ui->mainToolBar->hide();

    m_LoggedUser = LoggedUser;
    EnableActions();
    selectedWindowToPrint = NULL;
}

MainWindow::~MainWindow()
{
    QLOG_TRACE_FN();
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QLOG_TRACE_FN();
    // Open Planification List
    CalendarWindow *wnd = new CalendarWindow(m_LoggedUser, DataStore::instance()->getPlanificacionesDias(), false, true, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::print(QPrinter *printer)
{
    QLOG_TRACE_FN();
    QString htmlReport = "";
    if (selectedCalendarWindowToPrint)
    {
        htmlReport = selectedCalendarWindowToPrint->getHTMLReport();
    }
    if (selectedWindowToPrint)
    {
        htmlReport = selectedWindowToPrint->getHTMLReport();
    }

    if (htmlReport.length() > 0)
    {
        QTextDocument textDoc;
        textDoc.setHtml(htmlReport);
        //printer->setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
        textDoc.print(printer);
    }
}

void MainWindow::printSelected(QPrinter *printer)
{
    QLOG_TRACE_FN();
    if (selectedWindowToPrint || selectedCalendarWindowToPrint)
    {
        QTextDocument textDoc;
        if (selectedWindowToPrint)
        {
            selectedWindowToPrint->printSelectedRecord(textDoc);
        }
        else
        {
            selectedCalendarWindowToPrint->printSelectedRecord(textDoc);
        }
//        printer->setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
        textDoc.print(printer);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
        if (!selectedWindowToPrint)
        {
            selectedCalendarWindowToPrint = qobject_cast<CalendarWindow*>(ui->mdiArea->activeSubWindow()->widget());
        }
        // Prints ActiveWindow
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dlg(&printer, this);
        if (dlg.exec() == QDialog::Accepted)
        {
            // Print
            print(&printer);
        }
    }
    else
    {
        selectedWindowToPrint = NULL;
        selectedCalendarWindowToPrint = NULL;
    }
}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
        if (!selectedWindowToPrint)
        {
            selectedCalendarWindowToPrint = qobject_cast<CalendarWindow*>(ui->mdiArea->activeSubWindow()->widget());
        }
        //QPrinter printer(QPrinter::HighResolution);
        QPrinter printer;
        QPrintPreviewDialog dlg(&printer, this);
        connect (&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        dlg.setWindowState(dlg.windowState() | Qt::WindowMaximized);
        dlg.exec();
    }
    else
    {
        selectedCalendarWindowToPrint = NULL;
        selectedWindowToPrint = NULL;
    }
}

void MainWindow::on_actionPrint_Selected_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
        // Prints to printer selected record
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dlg(&printer, this);
        if (dlg.exec() == QDialog::Accepted)
        {
            // Print
            printSelected(&printer);
        }
    }
    else
        selectedWindowToPrint = NULL;
}

void MainWindow::on_actionPrint_Preview_Selected_Record_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
        if (!selectedWindowToPrint)
        {
            selectedCalendarWindowToPrint = qobject_cast<CalendarWindow*>(ui->mdiArea->activeSubWindow()->widget());
        }
        // Prints Selected record on active window
        QPrinter printer;
        //printer.setOrientation(QPrinter::Landscape);
        QPrintPreviewDialog dlg(&printer, this);
        connect(&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printSelected(QPrinter*)));
        dlg.setWindowState(dlg.windowState() | Qt::WindowMaximized);
        dlg.exec();
    }
    else
    {
        selectedWindowToPrint = NULL;
        selectedCalendarWindowToPrint = NULL;
    }
}

void MainWindow::on_actionExit_triggered()
{
    QLOG_TRACE_FN();
    // Exits application
    QApplication::exit(0);
}

void MainWindow::on_actionView_triggered()
{
    QLOG_TRACE_FN();
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getEmpleados(), false, true, this);
    ui->mdiArea->addSubWindow(wnd)->setWindowState(Qt::WindowMaximized);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionSetup_days_triggered()
{
    QLOG_TRACE_FN();
    // Open days setup list.
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getEstimacionesDias(), true, true, this);
    wnd->AllowAdd(false);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionParameters_triggered()
{
    QLOG_TRACE_FN();
    // Open Parameters
    DlgParametros dlg(this);
    if (dlg.exec() == QDialog::Accepted)
    {
        // aca hay que guardar los parametros
        DataStore::instance()->getParametros()->save();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QLOG_TRACE_FN();
    // Opens About box.
    QMessageBox::about(this, tr("About B6P"), tr("B6Planner"));
}

void MainWindow::datastore_loaded(QString name)
{
    QLOG_TRACE_FN();
    ui->statusBar->showMessage(tr("%1 Loaded.").arg(name));
}

void MainWindow::datastore_loading(QString name)
{
    QLOG_TRACE_FN();
    ui->statusBar->showMessage(tr("Loading %1...").arg(name));
}

void MainWindow::datastore_saved(QString name)
{
    QLOG_TRACE_FN();
    ui->statusBar->showMessage(tr("%1 Saved.").arg(name));
}

void MainWindow::datastore_saving(QString name)
{
    QLOG_TRACE_FN();
    ui->statusBar->showMessage(tr("Saving %1...").arg(name));
}


void MainWindow::EnableActions()
{
    QLOG_TRACE_FN();
    if (m_LoggedUser > 0)
    {
        QString feature = DataStore::instance()->getEmpleados()->invariableName();
        ui->actionView->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));

        feature = DataStore::instance()->getPlanificacionesDias()->invariableName();
        ui->actionOpen->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));
        ui->actionSetup_days->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));

        feature = DataStore::instance()->getParametros()->invariableName();
        ui->actionParameters->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));

        feature = "Sincro";
        ui->actionSynchronize->setEnabled(DataStore::instance()->getAccesos()->canRead(m_LoggedUser, feature));
    }
    else
    {
        ui->actionView->setEnabled(true);
        ui->actionOpen->setEnabled(true);
        ui->actionAbout->setEnabled(true);
        ui->actionSetup_days->setEnabled(true);
        ui->actionParameters->setEnabled(true);
        ui->actionSynchronize->setEnabled(true);
    }
}

void MainWindow::on_actionSynchronize_triggered()
{
    QLOG_TRACE_FN();
    if (DataStore::instance()->getParametros()->getValue(Parametros::USE_FILE_SYNCHRO, 1) == 0)
    {
        DlgSynchronization dlg;
        dlg.exec();
    }
    else
    {
        DlgFileSynchronization dlg;
        dlg.exec();
    }
}



void MainWindow::on_actionHours_by_Sector_and_Subsector_triggered()
{
    QLOG_TRACE_FN();
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getReporteHorasSectorSubSector(), false, true, this);
    ui->mdiArea->addSubWindow(wnd)->setWindowState(Qt::WindowMaximized);
    wnd->show();
    wnd->activateWindow();
    wnd->setABMButtonsVisible(false);
}

void MainWindow::on_actionPlanned_hours_day_by_day_triggered()
{
    QLOG_TRACE_FN();
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getReporteHorasDiaADia(), false, true, this);
    ui->mdiArea->addSubWindow(wnd)->setWindowState(Qt::WindowMaximized);
    wnd->show();
    wnd->activateWindow();
    wnd->setABMButtonsVisible(false);
}

void MainWindow::on_actionHours_planned_by_employee_triggered()
{
    QLOG_TRACE_FN();
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getReporteHorasPorEmpleado(), false, true, this);
    ui->mdiArea->addSubWindow(wnd)->setWindowState(Qt::WindowMaximized);
    wnd->show();
    wnd->activateWindow();
    wnd->setABMButtonsVisible(false);
}

void MainWindow::on_actionPlanned_rests_triggered()
{
    QLOG_TRACE_FN();
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getReporteFrancosPlanificados(), false, true, this);
    ui->mdiArea->addSubWindow(wnd)->setWindowState(Qt::WindowMaximized);
    wnd->show();
    wnd->activateWindow();
    wnd->setABMButtonsVisible(false);
}
