#include "dlgfilesynchronization.h"
#include "ui_dlgfilesynchronization.h"
#include "datastore.h"
#include <QsLog.h>
#include <QDir>
#include "filesynchronization.h"

DlgFileSynchronization::DlgFileSynchronization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgFileSynchronization)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);

    ui->lblFolder->setText(DataStore::instance()->getParametros()->getValue(Parametros::SYNCHRO_FOLDER, ""));
}

DlgFileSynchronization::~DlgFileSynchronization()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgFileSynchronization::on_buttonBox_clicked(QAbstractButton *button)
{
    QLOG_TRACE_FN();
    QString x =button->text();
    if (button->text()==tr("&OK"))
    {
        FileSynchronization fileSynchro(this);
        fileSynchro.doSynchro();
    }
}
