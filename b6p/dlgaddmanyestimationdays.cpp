#include "dlgaddmanyestimationdays.h"
#include "ui_dlgaddmanyestimationdays.h"
#include <QsLog.h>

DlgAddManyEstimationDays::DlgAddManyEstimationDays(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAddManyEstimationDays)
{
    QLOG_TRACE() << "DlgAddManyEstimationDays::DlgAddManyEstimationDays(QWidget *parent)";
    ui->setupUi(this);
}

DlgAddManyEstimationDays::~DlgAddManyEstimationDays()
{
    QLOG_TRACE() << "DlgAddManyEstimationDays::~DlgAddManyEstimationDays()";
    delete ui;
}

void DlgAddManyEstimationDays::setFrom(QDate fromDate)
{
    QLOG_TRACE() << "void DlgAddManyEstimationDays::setFrom(QDate fromDate)";
    ui->dateFrom->setDate(fromDate);
}

void DlgAddManyEstimationDays::setTo(QDate toDate)
{
    QLOG_TRACE() << "void DlgAddManyEstimationDays::setTo(QDate toDate)";
    ui->dateTo->setDate(toDate);
}

QDate DlgAddManyEstimationDays::From()
{
    QLOG_TRACE() << "QDate DlgAddManyEstimationDays::From()";
    return ui->dateFrom->date();
}

QDate DlgAddManyEstimationDays::To()
{
    QLOG_TRACE() << "QDate DlgAddManyEstimationDays::To()";
    return ui->dateTo->date();
}
