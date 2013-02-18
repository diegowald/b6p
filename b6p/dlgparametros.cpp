#include "dlgparametros.h"
#include "ui_dlgparametros.h"
#include "datastore.h"

DlgParametros::DlgParametros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgParametros)
{
    ui->setupUi(this);

    ui->timeOpen->setTime(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE));
    ui->timeClose->setTime(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE));
    ui->MinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MIN_WORKING_HOURS, 4)));
    ui->employeeMinWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MIN_HOURS, 4)));
    ui->employeeMaxWorkingHours->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::EMPLOYEE_MAX_HOURS, 8)));
    ui->employeeDaysBetweenFreeDay->setText(QString::number(DataStore::instance()->getParametros()->getValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, 6)));
}

DlgParametros::~DlgParametros()
{
    delete ui;
}

void DlgParametros::accept()
{
    DataStore::instance()->getParametros()->setValue(Parametros::OPEN_STORE, ui->timeOpen->time());
    DataStore::instance()->getParametros()->setValue(Parametros::CLOSE_STORE, ui->timeClose->time());
    DataStore::instance()->getParametros()->setValue(Parametros::MIN_WORKING_HOURS, ui->MinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MIN_HOURS, ui->employeeMinWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::EMPLOYEE_MAX_HOURS, ui->employeeMaxWorkingHours->text().toInt());
    DataStore::instance()->getParametros()->setValue(Parametros::MAX_DAYS_BETWEEN_FREE_DAY, ui->employeeDaysBetweenFreeDay->text().toInt());

    QDialog::accept();
}
