#include "dlgplanificaciondia.h"
#include "ui_dlgplanificaciondia.h"
#include <boost/make_shared.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include "datastore.h"
#include "timehelper.h"
#include <QTextStream>
#include <QsLog.h>


DlgPlanificacionDia::DlgPlanificacionDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgPlanificacionDia)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    newID = 0;
    SubsectorsToDelete.clear();
    ui->btnEdit->setVisible(false);
}

DlgPlanificacionDia::~DlgPlanificacionDia()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgPlanificacionDia::setData(PlanificacionDiaPtr data)
{
    QLOG_TRACE_FN();
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
        connect(time, SIGNAL(refreshColorAssignments()), this, SLOT(on_refreshColorAssignments()));
        connect(time, SIGNAL(AllowOverWorkingForEmployee(int)), this, SLOT(on_AllowOverWorkingForEmployee(int)));
        time->setDate(m_Dia);
        time->setData(plan->IDRecord().value());

        time->setAllowOverWorking(plan->AllowOverWorking().value());

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
    if (data->EstadoPlanificacion().value() == APPROVED)
        setReadOnly();
}

void DlgPlanificacionDia::on_btnAdd_pressed()
{
    QLOG_TRACE_FN();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    ui->treeWidget->addTopLevelItem(item);
    TimeAssignmentItemEdit *time = new TimeAssignmentItemEdit();
    connect(time, SIGNAL(calcularHoras(int,int&)), this, SLOT(on_calcularHoras(int,int&)));
    connect(time, SIGNAL(refreshColorAssignments()), this, SLOT(on_refreshColorAssignments()));
    connect(time, SIGNAL(AllowOverWorkingForEmployee(int)), this, SLOT(on_AllowOverWorkingForEmployee(int)));
    time->setDate(m_Dia);
    newID++;
    time->setData(-newID);
    ui->treeWidget->setItemWidget(item, 0, time);
    connect(time, SIGNAL(AssignmentChanged(int,int)), this, SLOT(slot_AssignmentChanged(int, int)));
}

void DlgPlanificacionDia::on_btnEdit_pressed()
{
    QLOG_TRACE_FN();
}

void DlgPlanificacionDia::displayPlannedHours(double hours)
{
    QLOG_TRACE_FN();
    ui->lblHorasPlanificadas->setText(tr("Planned: %1 hs").arg(QString::number(hours)));
}

void DlgPlanificacionDia::slot_AssignmentChanged(int, int)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    return m_Dia;
}

QString DlgPlanificacionDia::Notas()
{
    QLOG_TRACE_FN();
    return ui->txtNotes->text();
}

int DlgPlanificacionDia::IDSupervisor()
{
    QLOG_TRACE_FN();
    return -1;
}

PlanificacionSubSectorLst DlgPlanificacionDia::Planificaciones()
{
    QLOG_TRACE_FN();
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
        ptr->AllowOverWorking().setValue(time->AllowOverWorking());
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

void DlgPlanificacionDia::setReadOnly()
{
    QLOG_TRACE_FN();
    ui->btnAdd->setEnabled(false);
    ui->btnDelete->setEnabled(false);
    ui->btnEdit->setEnabled(false);

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        time->setEnabled(false);
    }
}

void DlgPlanificacionDia::on_btnDelete_pressed()
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));

        if (time && (time->IDEmpleado() == IDEmpleado))
            horas += (time->HoraFin() - time->HoraInicio()) / 3600;
    }
}

void DlgPlanificacionDia::on_refreshColorAssignments()
{
    QLOG_TRACE_FN();
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        if (time)
            time->recalculateColorAssignments(time->IDEmpleado());
    }
}

void DlgPlanificacionDia::on_AllowOverWorkingForEmployee(int IDEmpleado)
{
    QLOG_TRACE_FN();
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        if (time && (time->IDEmpleado() == IDEmpleado))
            time->setAllowOverWorking(true);
    }
}

void DlgPlanificacionDia::on_btnExport_pressed()
{
    QLOG_TRACE_FN();
    QString suggestedName = "export"; //model->suggestedFileName();

    QString filename =
            QFileDialog::getSaveFileName(this, tr("Export to..."),
                                         "./" + suggestedName,
                                         tr("CSV Files (*.csv)"));

    if (filename.size() > 0)
    {
        QString fileName = (filename.toLower().endsWith(".csv") ? filename: filename + ".csv");
        QFile file(fileName);
        if (file.open(QFile::WriteOnly))
        {
            QTextStream st(&file);
            QStringList headers = getHeaders();
            QString r = "\"" + headers.join("\",\"") + "\"";
            st << r << endl;

            boost::shared_ptr<QList<QStringList> > records = getAll();

            foreach(QStringList record, *records)
            {
                QString r = "\"" + record.join("\",\"") + "\"";
                st << r << endl;
            }
            QMessageBox::information(NULL,
                                     tr("Export to CSV"),
                                     tr("Successfuly exported!"));
        }
        else
        {
            QMessageBox::information(NULL,
                                     tr("Export to CSV Error"),
                                     tr("Couldn't open file."));
        }
    }
}

QStringList DlgPlanificacionDia::getHeaders()
{
    QLOG_TRACE_FN();
    QStringList res;
    res << tr("Sector") << tr("SubSector")
        << tr("From") << tr("To")
        << tr("Employee") << tr("OverWork");
    return res;
}

boost::shared_ptr<QList<QStringList> > DlgPlanificacionDia::getAll()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        res->push_back(getRecord(time));
    }

    return res;
}

QStringList DlgPlanificacionDia::getRecord(TimeAssignmentItemEdit *time)
{
    QLOG_TRACE_FN();
    QStringList res;

    res << DataStore::instance()->getSectores()->getSector(time->IDSector())->Nombre().value();
    res << ((time->IDSubSector() == 0) ? ""
                                        : DataStore::instance()->getSubSectores()->getSubSector(time->IDSubSector())->Nombre().value());

    res << TimeHelper::SecondsToString(time->HoraInicio());
    res << TimeHelper::SecondsToString(time->HoraFin());
    if (time->IDEmpleado() == 0)
    {
        res << "";
    }
    else
    {
        EmpleadoPtr e = DataStore::instance()->getEmpleados()->getEmpleado(time->IDEmpleado(), true);
        res << QString("%1, %2").arg(e->Apellido().value()).arg(e->Nombre().value());
    }
    res << (time->AllowOverWorking() ? tr("OverWork") : "");
    return res;
}
