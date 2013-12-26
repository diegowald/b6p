#include "dlgdaterangefilter.h"
#include "ui_dlgdaterangefilter.h"
#include "QsLog.h"


DlgDateRangeFilter::DlgDateRangeFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgDateRangeFilter)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    ui->dateFrom->setDate(QDate::currentDate().addDays(-7));
    ui->dateTo->setDate(QDate::currentDate());
}

DlgDateRangeFilter::~DlgDateRangeFilter()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgDateRangeFilter::setDateFrom(const QDate &from)
{
    QLOG_TRACE_FN();
    ui->dateFrom->setDate(from);
}


void DlgDateRangeFilter::setDateTo(const QDate &to)
{
    QLOG_TRACE_FN();
    ui->dateTo->setDate(to);
}

QDate DlgDateRangeFilter::dateFrom()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgDateRangeFilter::dateTo()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}
