#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genericlist.h"
#include "datastore.h"
#include "dlgparametros.h"
#include "dlgsynchronization.h"
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
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getPlanificacionesDias(), false, true, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::print(QPrinter *printer)
{
    QLOG_TRACE_FN();
    if (selectedWindowToPrint) {
        QTextDocument textDoc;
        textDoc.setHtml(selectedWindowToPrint->getHTMLReport());
        textDoc.print(printer);
    }
}

void MainWindow::printSelected(QPrinter *printer)
{
    QLOG_TRACE_FN();
    if (selectedWindowToPrint) {
        QTextDocument textDoc;
        selectedWindowToPrint->printSelectedRecord(textDoc);
        textDoc.print(printer);
    }
}

void MainWindow::on_actionPrint_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
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
        selectedWindowToPrint = NULL;
}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QLOG_TRACE_FN();
    if (ui->mdiArea->activeSubWindow()) {
        selectedWindowToPrint = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());
        QPrinter printer(QPrinter::HighResolution);
        QPrintPreviewDialog dlg(&printer, this);
        connect (&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(print(QPrinter*)));
        dlg.setWindowState(dlg.windowState() | Qt::WindowMaximized);
        dlg.exec();
    }
    else
        selectedWindowToPrint = NULL;
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
        // Prints Selected record on active window
        QPrinter printer;
        printer.setOrientation(QPrinter::Landscape);
        QPrintPreviewDialog dlg(&printer, this);
        connect(&dlg, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printSelected(QPrinter*)));
        dlg.setWindowState(dlg.windowState() | Qt::WindowMaximized);
        dlg.exec();
    }
    else
        selectedWindowToPrint = NULL;
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
    DlgSynchronization dlg;
    dlg.exec();
}


