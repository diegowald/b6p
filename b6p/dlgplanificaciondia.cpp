#include "dlgplanificaciondia.h"
#include "ui_dlgplanificaciondia.h"
#include "timeassignmentitemedit.h"

DlgPlanificacionDia::DlgPlanificacionDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPlanificacionDia)
{
    ui->setupUi(this);
}

DlgPlanificacionDia::~DlgPlanificacionDia()
{
    delete ui;
}

void DlgPlanificacionDia::setData(PlanificacionDiaPtr data)
{
    ui->lblDia->setText(tr("Date: %1").arg(data->Dia().value().toString(Qt::TextDate)));
    ui->lblHorasEstimadas->setText(tr("Estimation: %1 hs").arg(QString::number(data->Estimacion()->EstimacionHoras().value())));
    ui->lblStatus->setText(tr("Status: %1").arg(data->Estado()));
    ui->lblHorasPlanificadas->setText(tr("Planned: %1 hs").arg(QString::number(data->HorasPlanificadas())));
}

void DlgPlanificacionDia::on_btnAdd_pressed()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(item);
    TimeAssignmentItemEdit *time = new TimeAssignmentItemEdit();
    ui->treeWidget->setItemWidget(item, 0, time);
}

void DlgPlanificacionDia::on_btnEdit_pressed()
{
}
