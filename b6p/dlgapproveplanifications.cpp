#include "dlgapproveplanifications.h"
#include "ui_dlgapproveplanifications.h"
#include <boost/make_shared.hpp>
#include "datastore.h"
#include <QsLog.h>

DlgApprovePlanifications::DlgApprovePlanifications(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgApprovePlanifications)
{
    QLOG_TRACE() << "DlgApprovePlanifications::DlgApprovePlanifications(QWidget *parent)";
    ui->setupUi(this);
}

DlgApprovePlanifications::~DlgApprovePlanifications()
{
    QLOG_TRACE() << "DlgApprovePlanifications::~DlgApprovePlanifications()";
    delete ui;
}

void DlgApprovePlanifications::setData(PlanificacionDiaLst data)
{
    QLOG_TRACE() << "void DlgApprovePlanifications::setData(PlanificacionDiaLst data)";
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
    QLOG_TRACE() << "PlanificacionDiaLst DlgApprovePlanifications::getPlanificacionToApprove()";
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
