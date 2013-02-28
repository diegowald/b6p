#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genericlist.h"
#include "datastore.h"
#include "dlgparametros.h"
#include "qmysql.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    //DataStore::instance()->initialize(this);

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

    //QMysql x;

    /*ui->widget->setBackgroundColor(Qt::white);
    ui->widget->setTimeLineColor(Qt::lightGray);
    ui->widget->setTimeLineHeight(4);
    ui->widget->setAssignmentColor(Qt::darkRed);
    ui->widget->setAssignmentHeight(6);
    QDateTime dt = ui->widget->startAssignment();
    dt.setTime(QTime(10, 0, 0));
    ui->widget->setStartAssignment(dt);
*/

    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    // Open Planification List
    GenericList *wnd = new GenericList(DataStore::instance()->getPlanificacionesDias(), false, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionApprove_triggered()
{
    // Approve current planification
}


void MainWindow::on_actionPrint_triggered()
{
    // Prints planification
}

void MainWindow::on_actionExit_triggered()
{
    // Exits application
}

void MainWindow::on_actionView_triggered()
{
    // Open Employees list
    GenericList *wnd = new GenericList(DataStore::instance()->getEmpleados(), false, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionSetup_days_triggered()
{
    // Open days setup list.
    GenericList *wnd = new GenericList(DataStore::instance()->getEstimacionesDias(), true, this);
    wnd->AllowAdd(false);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionParameters_triggered()
{
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
    // Opens About box.
}

void MainWindow::datastore_loaded(QString name)
{
    ui->statusBar->showMessage(tr("%1 Loaded.").arg(name));
}

void MainWindow::datastore_loading(QString name)
{
    ui->statusBar->showMessage(tr("Loading %1...").arg(name));
}

void MainWindow::datastore_saved(QString name)
{
    ui->statusBar->showMessage(tr("%1 Saved.").arg(name));
}

void MainWindow::datastore_saving(QString name)
{
    ui->statusBar->showMessage(tr("Saving %1...").arg(name));
}

