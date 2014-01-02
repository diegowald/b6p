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
#include "dlgapproveplanifications.h"
#include "ui_dlgapproveplanifications.h"
#include <boost/make_shared.hpp>
#include "datastore.h"
#include <QsLog.h>

DlgApprovePlanifications::DlgApprovePlanifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgApprovePlanifications)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgApprovePlanifications::~DlgApprovePlanifications()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgApprovePlanifications::setData(PlanificacionDiaLst data)
{
    QLOG_TRACE_FN();
    ui->treePlanifications->setColumnCount(7);
    foreach(PlanificacionDiaPtr p, *data)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setCheckState(0, Qt::Unchecked);
        item->setText(0, p->Dia().value().toString(Qt::TextDate));
        item->setData(0, Qt::UserRole, p->Dia().value());
        if (p->IDSupervisor().isNull() || p->IDSupervisor().value() == -1)
            item->setText(1, "");
        else
            item->setText(1, p->Supervisor()->Apellido().value());
        item->setText(2, p->Notas().value());
        item->setText(3, QString::number(p->Estimacion()->EstimacionHoras().value()));
        item->setText(4, QString::number(p->HorasPlanificadas()));
        item->setText(5, p->Estado());
        item->setText(6, (p->isEverythingAssigned() ? tr("Yes") : tr("No")));
        ui->treePlanifications->insertTopLevelItem(0, item);
    }
}

PlanificacionDiaLst DlgApprovePlanifications::getPlanificacionToApprove()
{
    QLOG_TRACE_FN();
    PlanificacionDiaLst res = boost::make_shared<QList<PlanificacionDiaPtr> >();

    for (int i = 0; i < ui->treePlanifications->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem *item = ui->treePlanifications->topLevelItem(i);

        if (item->checkState(0))
            res->push_back(
                        DataStore::instance()->getPlanificacionesDias()->getByDay(
                            item->data(0, Qt::UserRole).toDate(), false
                            )
                        );
    }
    return res;
}
