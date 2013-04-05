#include "dlgplanificaciondia.h"
#include "ui_dlgplanificaciondia.h"
#include "timeassignmentitemedit.h"
#include <boost/make_shared.hpp>

DlgPlanificacionDia::DlgPlanificacionDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPlanificacionDia)
{
    ui->setupUi(this);
    newID = 0;
    SubsectorsToDelete.clear();
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
    m_Dia = data->Dia().value();

    ui->txtNotes->clear();
    if (!data->Notas().isNull())
        ui->txtNotes->setText(data->Notas().value());

    PlanificacionSubSectorLst planes = data->getPlanificaciones();
    foreach (PlanificacionSubSectorPtr plan, *planes)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        ui->treeWidget->addTopLevelItem(item);
        TimeAssignmentItemEdit *time = new TimeAssignmentItemEdit();
        connect(time, SIGNAL(calcularHoras(int,int&)), this, SLOT(on_calcularHoras(int,int&)));
        time->setDate(m_Dia);
        time->setData(plan->IDRecord().value());

        if (plan->IDSector().isNull())
            time->setIDSectorNull();
        else
            time->setIDSector(plan->IDSector().value());
        if (plan->IDSubSector().isNull())
            time->setIDSubSectorNull();
        else
            time->setIDSubSector(plan->IDSubSector().value());

        time->setHoraInicio(plan->HoraInicio().value());
        time->setHoraFin(plan->HoraFin().value());

        if (plan->IDEmpleado().isNull())
            time->setIDEmpleadoNull();
        else
            time->setIDEmpleado(plan->IDEmpleado().value());

        ui->treeWidget->setItemWidget(item, 0, time);
        connect(time, SIGNAL(AssignmentChanged(int,int)), this, SLOT(slot_AssignmentChanged(int,int)));
    }
}

void DlgPlanificacionDia::on_btnAdd_pressed()
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(item);
    TimeAssignmentItemEdit *time = new TimeAssignmentItemEdit();
    connect(time, SIGNAL(calcularHoras(int,int&)), this, SLOT(on_calcularHoras(int,int&)));
    time->setDate(m_Dia);
    newID++;
    time->setData(-newID);
    ui->treeWidget->setItemWidget(item, 0, time);
    connect(time, SIGNAL(AssignmentChanged(int,int)), this, SLOT(slot_AssignmentChanged(int, int)));
}

void DlgPlanificacionDia::on_btnEdit_pressed()
{
}

void DlgPlanificacionDia::displayPlannedHours(double hours)
{
    ui->lblHorasPlanificadas->setText(tr("Planned: %1 hs").arg(QString::number(hours)));
}

void DlgPlanificacionDia::slot_AssignmentChanged(int, int)
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

QDate DlgPlanificacionDia::Dia()
{
    return m_Dia;
}

QString DlgPlanificacionDia::Notas()
{
    return ui->txtNotes->text();
}

int DlgPlanificacionDia::IDSupervisor()
{
    return -1;
}

PlanificacionSubSectorLst DlgPlanificacionDia::Planificaciones()
{
    PlanificacionSubSectorLst res = boost::make_shared<QList<PlanificacionSubSectorPtr> >();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        PlanificacionSubSectorPtr ptr = boost::make_shared<PlanificacionSubSector>();

        ptr->IDRecord().setValue(time->data().toInt());
        ptr->Dia().setValue(m_Dia);
        ptr->IDSector().setValue(time->IDSector());
        if (time->isSubSectorEmpty())
            ptr->IDSubSector().setNull();
        else
            ptr->IDSubSector().setValue(time->IDSubSector());
        ptr->IDEmpleado().setValue(time->IDEmpleado());
        ptr->HoraInicio().setValue(time->HoraInicio());
        ptr->HoraFin().setValue(time->HoraFin());
        if (ptr->IDRecord().value() < 0)
            ptr->setNew();
        else
            ptr->setModified();
        res->push_back(ptr);
    }

    foreach(int id, SubsectorsToDelete)
    {
        PlanificacionSubSectorPtr ptr = boost::make_shared<PlanificacionSubSector>();
        ptr->IDRecord().setValue(id);
        ptr->Dia().setValue(m_Dia);
        ptr->setDeleted();
        res->push_back(ptr);
    }

    return res;
}

void DlgPlanificacionDia::on_btnDelete_pressed()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item)
    {
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        if (time->data().toInt() > 0)
        {
            SubsectorsToDelete.push_back(time->data().toInt());
        }
        delete item;
    }
}

void DlgPlanificacionDia::on_calcularHoras(int IDEmpleado, int &horas)
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        PlanificacionSubSectorPtr ptr = boost::make_shared<PlanificacionSubSector>();

        if (time->IDEmpleado() == IDEmpleado)
            horas += (time->HoraFin() - time->HoraInicio()) / 3600;
    }
}
