#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genericlist.h"
#include "datastore.h"
#include "dlgparametros.h"
#include "dlgsynchronization.h"
#include <QMessageBox>

// Printing
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QMdiSubWindow>
#include <QDebug>


MainWindow::MainWindow(int LoggedUser, QWidget *parent) :
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

    m_LoggedUser = LoggedUser;
    EnableActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    // Open Planification List
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getPlanificacionesDias(), false, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::print(QPrinter *printer)
{
    // Create Painter for drawing print page
    QPainter painter(printer);

    int w = printer->pageRect().width();
    int h = printer->pageRect().height();
    qDebug() << w;
    qDebug() << h;
    QRect page(0, 0, w, h);

    // Create a font approproate to page size
    QFont font = painter.font();
    font.setPixelSize((w+h)/100);
    painter.setFont(font);

    painter.drawText(page, Qt::AlignTop | Qt::AlignLeft, "QSimulate");

    GenericList *wnd  = qobject_cast<GenericList *>(ui->mdiArea->activeSubWindow()->widget());

    double xscale = w / double(wnd->width());
    double yscale = h / double(wnd->height());
    double scale = qMin(xscale, yscale);

    qDebug() << xscale;
    qDebug() << yscale;
    qDebug() << scale;

    painter.translate(printer->paperRect().x() + w / 2,
                      printer->paperRect().y() + h / 2);
    qDebug() << printer->paperRect().x() + w / 2;
    qDebug() << printer->paperRect().y() + h / 2;
    painter.scale(scale, scale);
//    painter.translate(w/2, h/2);

    wnd->render(&painter);

    //page.adjust(w/20, h/20, -2/20, -h/20);
/*    QPixmap p = QPixmap::grabWidget(wnd);
    painter.drawPixmap(0, 0, p);
    //wnd->render(&painter, page.topLeft());
    //m_sc*/
}

void MainWindow::on_actionPrint_triggered()
{
    // Prints planification
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        // Print
        print(&printer);
    }
}

void MainWindow::on_actionPrint_Preview_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog dlg(&printer, this);
    connect (&dlg, SIGNAL(paintRequested(QPrinter*)), SLOT(print(QPrinter*)));
    dlg.exec();
}


void MainWindow::on_actionExit_triggered()
{
    // Exits application
    QApplication::exit(0);
}

void MainWindow::on_actionView_triggered()
{
    // Open Employees list
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getEmpleados(), false, this);
    ui->mdiArea->addSubWindow(wnd);
    wnd->show();
    wnd->activateWindow();
}

void MainWindow::on_actionSetup_days_triggered()
{
    // Open days setup list.
    GenericList *wnd = new GenericList(m_LoggedUser, DataStore::instance()->getEstimacionesDias(), true, this);
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
    QMessageBox::about(this, tr("About B6P"), tr("B6Planner"));
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


void MainWindow::EnableActions()
{
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
    DlgSynchronization dlg;
    dlg.exec();
}


