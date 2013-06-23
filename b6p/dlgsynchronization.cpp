#include "dlgsynchronization.h"
#include "ui_dlgsynchronization.h"
#include "datastore.h"
#include "SincroManager.h"
#include <QsLog.h>


DlgSynchronization::DlgSynchronization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSynchronization)
{
    QLOG_TRACE() << "DlgSynchronization::DlgSynchronization(QWidget *parent)";
    ui->setupUi(this);
    sincro = boost::make_shared<SincroManager>(this);
    fillData();

    connect(sincro.get(), SIGNAL(startingSynchro()),
            this, SLOT(on_startingSynchro()));

    connect(sincro.get(), SIGNAL(getDataFromCentralDB(QString &Name)),
            this, SLOT(on_getDataFromCentralDB(QString&)));

    connect(sincro.get(), SIGNAL(applyingChanges(QString &)),
            this, SLOT(on_applyingChanges(QString&)));

    connect(sincro.get(), SIGNAL(checkingChanges(QString &)),
            this, SLOT(on_checkingChanges(QString&)));

    connect(sincro.get(), SIGNAL(sendingData(QString &)),
            this, SLOT(on_sendingData(QString&)));

    connect(sincro.get(), SIGNAL(SynchroEnded()),
            this, SLOT(on_SynchroEnded()));

}

DlgSynchronization::~DlgSynchronization()
{
    QLOG_TRACE() << "DlgSynchronization::~DlgSynchronization()";
    delete ui;
}

void DlgSynchronization::fillData()
{
    QLOG_TRACE() << "void DlgSynchronization::fillData()";
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
    QLOG_TRACE() << "void DlgSynchronization::on_btnStartSynchro_pressed()";
    ui->buttonBox->setEnabled(false);

    sincro->runSincro();

    ui->buttonBox->setEnabled(true);
}

void DlgSynchronization::on_startingSynchro()
{
    QLOG_TRACE() << "void DlgSynchronization::on_startingSynchro()";
    for (int i = 0; i < ui->treeSyncrhonizationStatus->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treeSyncrhonizationStatus->topLevelItem(i);
        item->setText(1, tr("Starting..."));
    }
}

void DlgSynchronization::on_getDataFromCentralDB(QString &tableName)
{
    QLOG_TRACE() << "void DlgSynchronization::on_getDataFromCentralDB(QString &tableName)";
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Getting data"));
    }
}

void DlgSynchronization::on_applyingChanges(QString &tableName)
{
    QLOG_TRACE() << "void DlgSynchronization::on_applyingChanges(QString &tableName)";
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Applying changes"));
    }
}

void DlgSynchronization::on_checkingChanges(QString &tableName)
{
    QLOG_TRACE() << "void DlgSynchronization::on_checkingChanges(QString &tableName)";
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Checking..."));
    }
}

void DlgSynchronization::on_sendingData(QString &tableName)
{
    QLOG_TRACE() << "void DlgSynchronization::on_sendingData(QString &tableName)";
    QList<QTreeWidgetItem*> items = ui->treeSyncrhonizationStatus->findItems(tableName, Qt::MatchExactly, 0);
    foreach(QTreeWidgetItem* item, items)
    {
        item->setText(1, tr("Sending data"));
    }
}

void DlgSynchronization::on_SynchroEnded()
{
    QLOG_TRACE() << "void DlgSynchronization::on_SynchroEnded()";
    for (int i = 0; i < ui->treeSyncrhonizationStatus->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treeSyncrhonizationStatus->topLevelItem(i);
        item->setText(1, "");
    }
}
