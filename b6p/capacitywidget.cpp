#include "capacitywidget.h"
#include "ui_capacitywidget.h"

CapacityWidget::CapacityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CapacityWidget)
{
    ui->setupUi(this);
    ui->lblSector->clear();
    ui->lblSubSector->clear();
    ui->lblValue->clear();
}

CapacityWidget::~CapacityWidget()
{
    delete ui;
}

void CapacityWidget::on_slideCapacity_valueChanged(int value)
{
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

void CapacityWidget::setSector(QString Sector)
{
    ui->lblSector->setText(Sector);
}

void CapacityWidget::setSubSector(QString SubSector)
{
    ui->lblSubSector->setText(SubSector);
}

void CapacityWidget::setCapacity(int capacity)
{
    ui->slideCapacity->setValue(capacity);
}

QString CapacityWidget::Sector()
{
    return ui->lblSector->text();
}

QString CapacityWidget::SubSector()
{
    return ui->lblSubSector->text();
}

int CapacityWidget::Capacity()
{
    return ui->slideCapacity->value();
}
