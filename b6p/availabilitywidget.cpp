#include "availabilitywidget.h"
#include "ui_availabilitywidget.h"

AvailabilityWidget::AvailabilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailabilityWidget)
{
    ui->setupUi(this);
    connect(ui->timeFrom, SIGNAL(dateTimeChanged(QDateTime)), ui->widget, SLOT(setStartAssignment(QDateTime)));
    connect(ui->timeTo, SIGNAL(dateTimeChanged(QDateTime)), ui->widget, SLOT(setEndAssignment(QDateTime)));
}

AvailabilityWidget::~AvailabilityWidget()
{
    delete ui;
}

void AvailabilityWidget::setLabel(QString value)
{
    ui->lblDay->setText(value);
}

void AvailabilityWidget::setAvailableFrom(QDateTime value)
{
}

void AvailabilityWidget::setAvailableTo(QDateTime value)
{
}

void AvailabilityWidget::setFrom(QDateTime value)
{
    ui->timeFrom->setDateTime(value);
}

void AvailabilityWidget::setTo(QDateTime value)
{
    ui->timeTo->setDateTime(value);
}
