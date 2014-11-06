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
#include "dlgemployee.h"
#include "ui_dlgemployee.h"
#include "capacitywidget.h"
#include "datastore.h"
#include <QsLog.h>
#include "licenciasempleados.h"

DlgEmployee::DlgEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEmployee)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    setupScreen();
}

DlgEmployee::~DlgEmployee()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgEmployee::setData(EmpleadoPtr empleado)
{
    QLOG_TRACE_FN();
    m_Empleado = empleado;
    // Informacion basica
    if (empleado->Legajo().isNull())
        ui->txtID->clear();
    else
        ui->txtID->setText(empleado->Legajo().value());

    if(empleado->Apellido().isNull())
        ui->txtLastName->clear();
    else
        ui->txtLastName->setText(empleado->Apellido().value());

    if (empleado->Nombre().isNull())
        ui->txtNames->clear();
    else
        ui->txtNames->setText(empleado->Nombre().value());

    if (empleado->FechaIngreso().isNull())
        ui->dateStart->clear();
    else
        ui->dateStart->setDate(empleado->FechaIngreso().value());

    // Sectores, subsectores y capacidades
    CapacidadPersonaSectorLst caps = empleado->Capacities();
    foreach (CapacidadPersonaSectorPtr cap, *caps.data())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        ui->treeCapacities->addTopLevelItem(item);
        CapacityWidget *w = new CapacityWidget();
        w->setIDSector(cap->IDSector().value());
        w->setAlreadyCreated();
        if (!cap->ID_SubSector().isNull())
            w->setIDSubSector(cap->ID_SubSector().value());
        w->setCapacity(cap->Capacidad().value());
        ui->treeCapacities->setItemWidget(item, 0, w);
    }

    // Disponibilidad de horarios
    CalendarioPersonaLst cals = empleado->Disponibilidades();
    foreach (CalendarioPersonaPtr cal, *cals.data())
    {
        AvailabilityWidget *w = NULL;
        switch (cal->Dia().value())
        {
        case 0:
            w = ui->TimeSunday;
            break;
        case 1:
            w = ui->TimeMonday;
            break;
        case 2:
            w = ui->TimeTuesday;
            break;
        case 3:
            w = ui->TimeWednesday;
            break;
        case 4:
            w = ui->TimeThrursday;
            break;
        case 5:
            w = ui->TimeFriday;
            break;
        case 6:
        default:
            w = ui->TimeSaturday;
            break;
        }
        w->setDay(cal->Dia().value());
        w->setFrom1(cal->HoraIngreso1().value());
        w->setTo1(cal->HoraEgreso1().value());
        w->setFrom2(cal->HoraIngreso2().value());
        w->setTo2(cal->HoraEgreso2().value());
    }

    // Francos
    ui->treeLicencias->clear();
    LicenciasEmpleadosLst licencias = empleado->LicenciasProgramadas();
    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        ui->treeLicencias->addTopLevelItem(item);

        item->setData(0, Qt::UserRole, empleado->IDEmpleado().value());
        item->setText(0, licencia->FechaDesde().value().toString(Qt::ISODate));
        item->setText(1, licencia->FechaDesde().value().toString("dddd"));
        item->setText(2, licencia->FechaHasta().value().toString(Qt::ISODate));
        item->setText(3, licencia->FechaHasta().value().toString("dddd"));
        item->setText(4, licencia->TipoLicencia().value());
        item->setText(5, licencia->Descripcion().value());
    }
}

void DlgEmployee::setupAssignment(AvailabilityWidget *w, int day)
{
    QLOG_TRACE_FN();
    w->setDay(day);
    w->setFrom1(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));
    w->setTo1(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 24 * 3600));
    w->setFrom2(0);
    w->setTo2(0);
}

void DlgEmployee::setupScreen()
{
    QLOG_TRACE_FN();
    ui->txtID->setText("");
    ui->txtLastName->setText("");
    ui->txtNames->setText("");
    setupAssignment(ui->TimeSunday, 0);
    setupAssignment(ui->TimeMonday, 1);
    setupAssignment(ui->TimeTuesday, 2);
    setupAssignment(ui->TimeWednesday, 3);
    setupAssignment(ui->TimeThrursday, 4);
    setupAssignment(ui->TimeFriday, 5);
    setupAssignment(ui->TimeSaturday, 6);
}


QString DlgEmployee::Apellido()
{
    QLOG_TRACE_FN();
    return ui->txtLastName->text();
}

QString DlgEmployee::Nombres()
{
    QLOG_TRACE_FN();
    return ui->txtNames->text();
}

QDate DlgEmployee::FechaIngreso()
{
    QLOG_TRACE_FN();
    return ui->dateStart->date();
}

QString DlgEmployee::Legajo()
{
    QLOG_TRACE_FN();
    return ui->txtID->text();
}

CapacidadPersonaSectorLst DlgEmployee::Capacities()
{
    QLOG_TRACE_FN();
    CapacidadPersonaSectorLst res = CapacidadPersonaSectorLst(new QList<CapacidadPersonaSectorPtr>());

    for (int i = 0; i < ui->treeCapacities->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *treeitem = ui->treeCapacities->topLevelItem(i);
        CapacityWidget * w = qobject_cast<CapacityWidget *>(ui->treeCapacities->itemWidget(treeitem, 0));
        CapacidadPersonaSectorPtr p = CapacidadPersonaSectorPtr::create();

        p->IDEmpleado().setValue(m_Empleado->IDEmpleado().value());
        p->IDSector().setValue(w->IDSector());
        p->ID_SubSector().setValue(w->IDSubSector());
        p->Capacidad().setValue(w->Capacity());

        QLOG_TRACE() << m_Empleado->IDEmpleado().value();
        QLOG_TRACE() << p->IDEmpleado().value();
        QLOG_TRACE() << p->IDSector().value();
        if (p->ID_SubSector().isNull())
            QLOG_TRACE() << "null";
        else
            QLOG_TRACE() << p->ID_SubSector().value();
        QLOG_TRACE() << p->Capacidad().value();
        res->push_back(p);
    }

    return res;
}

CalendarioPersonaPtr DlgEmployee::getAssignment(AvailabilityWidget *w)
{
    QLOG_TRACE_FN();
    CalendarioPersonaPtr p = CalendarioPersonaPtr::create();

    p->IDEmpleado().setValue(m_Empleado->IDEmpleado().value());

    p->HoraIngreso1().setValue(w->FromTime1());
    p->HoraEgreso1().setValue(w->ToTime1());
    p->HoraIngreso2().setValue(w->FromTime2());
    p->HoraEgreso2().setValue(w->ToTime2());
    p->Dia().setValue(w->Day());

    return p;
}

CalendarioPersonaLst DlgEmployee::Disponibilidades()
{
    QLOG_TRACE_FN();
    CalendarioPersonaLst res = CalendarioPersonaLst::create();

    res->push_back(getAssignment(ui->TimeSunday));
    res->push_back(getAssignment(ui->TimeMonday));
    res->push_back(getAssignment(ui->TimeTuesday));
    res->push_back(getAssignment(ui->TimeWednesday));
    res->push_back(getAssignment(ui->TimeThrursday));
    res->push_back(getAssignment(ui->TimeFriday));
    res->push_back(getAssignment(ui->TimeSaturday));

    return res;
}

void DlgEmployee::on_btnAdd_pressed()
{
    QLOG_TRACE_FN();
    QTreeWidgetItem *item = new QTreeWidgetItem();
    ui->treeCapacities->addTopLevelItem(item);
    CapacityWidget *w = new CapacityWidget();
    ui->treeCapacities->setItemWidget(item, 0, w);
}

void DlgEmployee::on_btnDelete_pressed()
{
    QLOG_TRACE_FN();
    QTreeWidgetItem *item = ui->treeCapacities->currentItem();
    if (item)
    {
        CapacityWidget *w = qobject_cast<CapacityWidget *>(ui->treeCapacities->itemWidget(item, 0));
        if (w->alreadyCreated())
        {
            CapacidadPersonaSectorPtr c = DataStore::instance()->getCapacidades()->get(
                        m_Empleado->IDEmpleado().value(),
                        w->IDSector(),
                        w->IDSubSector(), false);
            if (c.data())
            {
                c->setDeleted();
            }
        }
        delete item;
    }
}

void DlgEmployee::on_btnAdd_2_clicked()
{
    QLOG_TRACE_FN();
    DataStore::instance()->getLicencias()->addNewRecordWithAuxiliarydata(m_Empleado->IDEmpleado().value());
}

void DlgEmployee::on_btnEdit_2_clicked()
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> selectedItems = ui->treeLicencias->selectedItems();
    if (selectedItems.count() > 0)
    {
        QTreeWidgetItem * selectedItem = selectedItems.at(0);
        int IDLicencia = selectedItem->data(1, Qt::UserRole).toInt();
        DataStore::instance()->getLicencias()->editRecord(IDLicencia);
    }
}

void DlgEmployee::on_btnDelete_2_clicked()
{
    QLOG_TRACE_FN();
    QList<QTreeWidgetItem*> selectedItems = ui->treeLicencias->selectedItems();
    if (selectedItems.count() > 0)
    {
        QTreeWidgetItem * selectedItem = selectedItems.at(0);
        QVariant IDLicencia = selectedItem->data(1, Qt::UserRole);
        ((ACollection*)DataStore::instance()->getLicencias().data())->deleteRecord(IDLicencia);
    }
}
