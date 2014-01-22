/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "dlgplanificaciondia.h"
#include "ui_dlgplanificaciondia.h"
#include <boost/make_shared.hpp>
#include <QFileDialog>
#include <QMessageBox>
#include "datastore.h"
#include "timehelper.h"
#include <QTextStream>
#include <QsLog.h>
#include <dlgempleadoslicenciasplanificacion.h>

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
    ui->lblDia->setText(tr("Date: %1").arg(data->Dia().value().toString(Qt::ISODate)));
    if (data->Estimacion())
    {
        ui->lblHorasEstimadas->setText(tr("Estimation: %1 hs").arg(QString::number(data->Estimacion()->EstimacionHoras().value())));
        m_HorasEstimadas = data->Estimacion()->EstimacionHoras().value();
    }
    else
    {
        ui->lblHorasEstimadas->setText(tr("Estimation: %1 hs").arg(QString::number(0)));
        m_HorasEstimadas = 0;
    }
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
    if (CantHoras > m_HorasEstimadas)
    {
        QMessageBox::warning(NULL,
                             tr("Overworking!"),
                             tr("Planned hours are greater than estimation!"));
    }
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

void DlgPlanificacionDia::on_toolButton_clicked()
{
    // Aca se abre una ventana con el listado de empleados que pueden trabajar ese dia, que aun no han trabajado,
    // y si tienen o no licencia
    QLOG_TRACE_FN();
    DlgEmpleadosLicenciasPlanificacion dlg(this);
    dlg.setData(m_Dia, getCurrentlyWorkingEmployees());
    if (dlg.exec() == QDialog::Accepted)
    {
        for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
        {
            QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
            TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
            time->recalculateAvailableEmployees();
        }
//        RecordPtr modifiedRec = dlg.mergedRecord();
//        m_Data->updateRecord(modifiedRec, false);
    }
}


QList<int> DlgPlanificacionDia::getCurrentlyWorkingEmployees()
{
    QMap<int, int> partialRes;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        TimeAssignmentItemEdit *time = qobject_cast<TimeAssignmentItemEdit*>(ui->treeWidget->itemWidget(item, 0));
        partialRes[time->IDEmpleado()] = time->IDEmpleado();
    }
    return partialRes.keys();
}
