#include "dlgsynchronization.h"
#include "ui_dlgsynchronization.h"
#include "datastore.h"
#include "SincroManager.h"

DlgSynchronization::DlgSynchronization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSynchronization)
{
    ui->setupUi(this);
    sincro = boost::make_shared<SincroManager>(this);
    fillData();
}

DlgSynchronization::~DlgSynchronization()
{
    delete ui;
}

void DlgSynchronization::fillData()
{
    ui->lblLastSynchronization->setText(DataStore::instance()->getParametros()->getValue(Parametros::LAST_SYNCHRO, ""));
    ui->lblServerName->setText(DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, ""));
    ui->lblDatabase->setText(DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, ""));
    ui->lblUser->setText(DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, ""));
    QStringList tables = sincro->getSincroTableNames();
    foreach(QString table, tables)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, table);
        item->setData(0, Qt::UserRole, table);
        ui->treeSyncrhonizationStatus->addTopLevelItem(item);
    }
}

void DlgSynchronization::on_btnStartSynchro_pressed()
{
    ui->buttonBox->setEnabled(false);

    sincro->runSincro();

    ui->buttonBox->setEnabled(true);
}
