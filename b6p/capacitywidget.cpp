#include "capacitywidget.h"
#include "ui_capacitywidget.h"
#include "datastore.h"
#include <QsLog.h>


CapacityWidget::CapacityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CapacityWidget)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    llenarSectores();
    ui->lblValue->clear();
    ui->slideCapacity->setValue(0);
    on_slideCapacity_valueChanged(0);
    m_AlreadyCreated = false;
}

CapacityWidget::~CapacityWidget()
{
    QLOG_TRACE_FN();
    delete ui;
}

void CapacityWidget::on_slideCapacity_valueChanged(int value)
{
    QLOG_TRACE_FN();
    QString txtValue;
    switch (value)
    {
    case 0:
        txtValue = tr("Not available");
        break;
    case 1:
    case 2:
    case 3:
        txtValue =  tr("Regular (%1)").arg(value);
        break;
    case 4:
    case 5:
    case 6:
        txtValue = tr("Good (%1)").arg(value);
        break;
    case 7:
    case 8:
    case 9:
        txtValue = tr("Very Good (%1)").arg(value);
        break;
    default:
        txtValue = tr("Excellent (10)");
        break;
    }

    ui->lblValue->setText(txtValue);
}

void CapacityWidget::setIDSector(int IDSector)
{
    QLOG_TRACE_FN();
    ui->cboSectores->setCurrentIndex(ui->cboSectores->findData(IDSector, Qt::UserRole));
}

void CapacityWidget::setIDSubSector(int IDSubSector)
{
    QLOG_TRACE_FN();
    ui->cboSubSectores->setCurrentIndex(ui->cboSubSectores->findData(IDSubSector, Qt::UserRole));
}

void CapacityWidget::setCapacity(int capacity)
{
    QLOG_TRACE_FN();
    ui->slideCapacity->setValue(capacity);
}

int CapacityWidget::IDSector()
{
    QLOG_TRACE_FN();
    return ui->cboSectores->itemData(ui->cboSectores->currentIndex(), Qt::UserRole).toInt();
}

int CapacityWidget::IDSubSector()
{
    QLOG_TRACE_FN();
    return ui->cboSubSectores->itemData(ui->cboSubSectores->currentIndex(), Qt::UserRole).toInt();
}

int CapacityWidget::Capacity()
{
    QLOG_TRACE_FN();
    return ui->slideCapacity->value();
}

void CapacityWidget::llenarSectores()
{
    QLOG_TRACE_FN();
    ui->cboSectores->clear();
    SectorLst sectores = DataStore::instance()->getSectores()->getAll(false, false);
    foreach(SectorPtr s, *sectores)
    {
        ui->cboSectores->addItem(s->Nombre().value(), s->IDSector().value());
    }
}

void CapacityWidget::llenarSubSectores(int IDSector)
{
    QLOG_TRACE_FN();
    ui->cboSubSectores->clear();
    SubSectoresLst ss = DataStore::instance()->getSubSectores()->getAll(IDSector, false);
    foreach(SubSectorPtr ssp, *ss)
    {
        ui->cboSubSectores->addItem(ssp->Nombre().value(), ssp->IDSubsector().value());
    }
}

void CapacityWidget::on_cboSectores_currentIndexChanged(int index)
{
    QLOG_TRACE_FN();
    llenarSubSectores(ui->cboSectores->itemData(index, Qt::UserRole).toInt());
}

void CapacityWidget::setAlreadyCreated()
{
    QLOG_TRACE_FN();
    m_AlreadyCreated = true;
}

bool CapacityWidget::alreadyCreated()
{
    QLOG_TRACE_FN();
    return m_AlreadyCreated;
}
