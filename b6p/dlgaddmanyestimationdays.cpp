#include "dlgaddmanyestimationdays.h"
#include "ui_dlgaddmanyestimationdays.h"

DlgAddManyEstimationDays::DlgAddManyEstimationDays(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddManyEstimationDays)
{
    ui->setupUi(this);
}

DlgAddManyEstimationDays::~DlgAddManyEstimationDays()
{
    delete ui;
}

void DlgAddManyEstimationDays::setFrom(QDate fromDate)
{
    ui->dateFrom->setDate(fromDate);
}

void DlgAddManyEstimationDays::setTo(QDate toDate)
{
    ui->dateTo->setDate(toDate);
}

QDate DlgAddManyEstimationDays::From()
{
    return ui->dateFrom->date();
}

QDate DlgAddManyEstimationDays::To()
{
    return ui->dateTo->date();
}
