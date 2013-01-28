#include "availabilitywidget.h"
#include "ui_availabilitywidget.h"

AvailabilityWidget::AvailabilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailabilityWidget)
{
    ui->setupUi(this);
}

AvailabilityWidget::~AvailabilityWidget()
{
    delete ui;
}
