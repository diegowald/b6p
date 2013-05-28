#include "dlgparametros.h"
#include "ui_dlgparametros.h"
#include "datastore.h"
#include "sqlhandler.h"

DlgParametros::DlgParametros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgParametros)
{
    ui->setupUi(this);
    ui->timeOpen->SetSecondsVisibility(false);
    ui->timeClose->SetSecondsVisibility(false);
    ui->timeOpen->setValidRange(0, 0, 0, 24, 0, 0);
    ui->timeClose->setValidRange(0, 0, 0, 24, 0, 0);
    ui->timeOpen->setTime(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    ui->timeClose->setTime(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 24 * 3600));
    ui->MinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MIN_WORKING_HOURS, 4)));
    ui->employeeMinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MIN_HOURS, 4)));
    ui->employeeMaxWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MAX_HOURS, 8)));
    ui->employeeDaysBetweenFreeDay->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 6)));

    ui->txtServer->setText(DataStore::instance()->getParametros()->getValue(Parametros::SERVER_NAME, ""));
    ui->txtDatabase->setText(DataStore::instance()->getParametros()->getValue(Parametros::DATABASE_NAME, "b6p"));
    ui->txtUser->setText(DataStore::instance()->getParametros()->getValue(Parametros::USER_NAME, ""));
    ui->txtPassword->setText(DataStore::instance()->getParametros()->getValue(Parametros::PASSWORD, ""));
    ui->lblConnectionResult->clear();
}

DlgParametros::~DlgParametros()
{
    delete ui;
}

int DlgParametros::getCloseTime()
{
    int timeClose = ui->timeClose->timeSeconds();
    if (ui->chkNextDay->isChecked())
        timeClose += 86400; // Adding one day
    return timeClose;
}

void DlgParametros::accept()
{
    DataStore::instance()->getParametros()->setValue(Parametros::OPEN_STORE, ui->timeOpen->timeSeconds());
    DataStore::instance()->getParametros()->setValue(Parametros::CLOSE_STORE, getCloseTime());
    DataStore::instance()->getParametros()->setValue(Parametros::MIN_WORKING_HOURS, ui->MinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MIN_HOURS, ui->employeeMinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MAX_HOURS, ui->employeeMaxWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, ui->employeeDaysBetweenFreeDay->text().toInt());

    DataStore::instance()->getParametros()->setValue(Parametros::SERVER_NAME, ui->txtServer->text());
    DataStore::instance()->getParametros()->setValue(Parametros::DATABASE_NAME, ui->txtDatabase->text());
    DataStore::instance()->getParametros()->setValue(Parametros::USER_NAME, ui->txtUser->text());
    DataStore::instance()->getParametros()->setValue(Parametros::PASSWORD, ui->txtPassword->text());

    QDialog::accept();
}

void DlgParametros::on_pushButton_pressed()
{
    QString sql = "SELECT 1;";
    SQLHandler h(ui->txtServer->text(), ui->txtDatabase->text(), ui->txtUser->text(), ui->txtPassword->text());
    RecordSet rs = h.getAll(sql);
    if (rs->count() == 1)
        ui->lblConnectionResult->setText(tr("Connection OK"));
    else
        ui->lblConnectionResult->setText(tr("Please check connection parameters"));
}
