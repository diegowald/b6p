#include "dlgestimaciondia.h"
#include "ui_dlgestimaciondia.h"

DlgEstimacionDia::DlgEstimacionDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEstimacionDia)
{
    ui->setupUi(this);
}

DlgEstimacionDia::~DlgEstimacionDia()
{
    delete ui;
}

void DlgEstimacionDia::setData(EstimacionDiaPtr data)
{
    if (data->Dia().value() == QDateTime::fromMSecsSinceEpoch(0).date())
        ui->dateEdit->setDate(QDate::currentDate());
    else
        ui->dateEdit->setDate(data->Dia().value());

    ui->txtEstimation->setText(QString::number(data->EstimacionHoras().value()));
}

QDate DlgEstimacionDia::Dia()
{
    return ui->dateEdit->date();
}

int DlgEstimacionDia::EstimacionHoras()
{
    return ui->txtEstimation->text().toInt();
}
