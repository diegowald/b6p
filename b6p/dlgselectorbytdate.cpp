#include "dlgselectorbytdate.h"
#include "ui_dlgselectorbytdate.h"

DlgSelectorBytDate::DlgSelectorBytDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgSelectorBytDate)
{
    ui->setupUi(this);
}

DlgSelectorBytDate::~DlgSelectorBytDate()
{
    delete ui;
}

void DlgSelectorBytDate::setData(QList<QDate> &values)
{
    ui->cboValues->clear();
    foreach(QDate value, values)
    {
        ui->cboValues->addItem(value.toString(Qt::TextDate), value);
    }
    ui->cboValues->setCurrentIndex(0);
}

QDate DlgSelectorBytDate::selectedDay()
{
    return ui->cboValues->itemData(ui->cboValues->currentIndex(), Qt::UserRole).toDate();
}

void DlgSelectorBytDate::setTitle(QString txt)
{
    setWindowTitle(txt);
}

void DlgSelectorBytDate::setLabel(QString txt)
{
    ui->Label->setText(txt);
}
