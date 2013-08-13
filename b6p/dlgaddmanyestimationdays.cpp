#include "dlgaddmanyestimationdays.h"
#include "ui_dlgaddmanyestimationdays.h"
#include <QsLog.h>

DlgAddManyEstimationDays::DlgAddManyEstimationDays(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddManyEstimationDays)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgAddManyEstimationDays::~DlgAddManyEstimationDays()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgAddManyEstimationDays::setFrom(QDate fromDate)
{
    QLOG_TRACE_FN();
    ui->dateFrom->setDate(fromDate);
}

void DlgAddManyEstimationDays::setTo(QDate toDate)
{
    QLOG_TRACE_FN();
    ui->dateTo->setDate(toDate);
}

QDate DlgAddManyEstimationDays::From()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgAddManyEstimationDays::To()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}
