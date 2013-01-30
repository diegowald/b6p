#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genericlist.h"
#include "datastore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    //DataStore::instance()->initialize(this);

    ui->setupUi(this);
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
    GenericList *wnd = new GenericList(DataStore::instance()->getEmpleados(), this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionParameters_triggered()
{
    // Open Parameters
}

void MainWindow::on_actionAbout_triggered()
{
    // Opens About box.
}
