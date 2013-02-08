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
    displayPlannedHours(data->HorasPlanificadas());
}

void DlgPlanificacionDia::on_btnAdd_pressed()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(item);
    TimeAssignmentItemEdit *time = new TimeAssignmentItemEdit();
    ui->treeWidget->setItemWidget(item, 0, time);
    connect(time, SIGNAL(AssignmentChanged(QDateTime,QDateTime)), this, SLOT(slot_AssignmentChanged(QDateTime, QDateTime)));
}

void DlgPlanificacionDia::on_btnEdit_pressed()
{
}

void DlgPlanificacionDia::displayPlannedHours(double hours)
{
    ui->lblHorasPlanificadas->setText(tr("Planned: %1 hs").arg(QString::number(hours)));
}

void DlgPlanificacionDia::slot_AssignmentChanged(QDateTime from, QDateTime to)
{
    double CantHoras = 0;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        CantHoras += time->CantidadHoras();
    }
    displayPlannedHours(CantHoras);
}
