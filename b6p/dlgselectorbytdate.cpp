#include "dlgselectorbytdate.h"
#include "ui_dlgselectorbytdate.h"
#include <QsLog.h>


DlgSelectorBytDate::DlgSelectorBytDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSelectorBytDate)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgSelectorBytDate::~DlgSelectorBytDate()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgSelectorBytDate::setData(QList<QDate> &values)
{
    QLOG_TRACE_FN();
    ui->cboValues->clear();
    foreach(QDate value, values)
    {
        ui->cboValues->addItem(value.toString(Qt::TextDate), value);
    }
    ui->cboValues->setCurrentIndex(0);
}

QDate DlgSelectorBytDate::selectedDay()
{
    QLOG_TRACE_FN();
    return ui->cboValues->itemData(ui->cboValues->currentIndex(), Qt::UserRole).toDate();
}

void DlgSelectorBytDate::setTitle(QString txt)
{
    QLOG_TRACE_FN();
    setWindowTitle(txt);
}

void DlgSelectorBytDate::setLabel(QString txt)
{
    QLOG_TRACE_FN();
    ui->Label->setText(txt);
}
