#include "dlgestimaciondia.h"
#include "ui_dlgestimaciondia.h"
#include <QsLog.h>


DlgEstimacionDia::DlgEstimacionDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEstimacionDia)
{
    QLOG_TRACE() << "DlgEstimacionDia::DlgEstimacionDia(QWidget *parent)";
    ui->setupUi(this);
}

DlgEstimacionDia::~DlgEstimacionDia()
{
    QLOG_TRACE() << "DlgEstimacionDia::~DlgEstimacionDia()";
    delete ui;
}

void DlgEstimacionDia::setData(EstimacionDiaPtr data)
{
    QLOG_TRACE() << "void DlgEstimacionDia::setData(EstimacionDiaPtr data)";
    if (data->Dia().value() == QDateTime::fromMSecsSinceEpoch(0).date())
        ui->dateEdit->setDate(QDate::currentDate());
    else
        ui->dateEdit->setDate(data->Dia().value());

    ui->txtEstimation->setText(QString::number(data->EstimacionHoras().value()));
}

QDate DlgEstimacionDia::Dia()
{
    QLOG_TRACE() << "QDate DlgEstimacionDia::Dia()";
    return ui->dateEdit->date();
}

int DlgEstimacionDia::EstimacionHoras()
{
    QLOG_TRACE() << "int DlgEstimacionDia::EstimacionHoras()";
    return ui->txtEstimation->text().toInt();
}
