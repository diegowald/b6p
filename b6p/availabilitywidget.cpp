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

void AvailabilityWidget::setFrom(QTime value)
{
    QDateTime dt;
    dt.setDate(QDate::currentDate());
    dt.setTime(value);
    setFrom(dt);
}

void AvailabilityWidget::setTo(QDateTime value)
{
    ui->timeTo->setDateTime(value);
}

void AvailabilityWidget::setTo(QTime value)
{
    QDateTime dt;
    dt.setDate(QDate::currentDate());
    dt.setTime(value);
    setTo(dt);
}

void AvailabilityWidget::setDay(int day)
{
    QString lbl;
    switch(day)
    {
    case 0:
        lbl = tr("Sunday");
        break;
    case 1:
        lbl = tr("Monday");
        break;
    case 2:
        lbl = tr("Tuesday");
        break;
    case 3:
        lbl = tr("Wednesday");
        break;
    case 4:
        lbl = tr("Thursday");
        break;
    case 5:
        lbl = tr("Friday");
        break;
    case 6:
    default:
        lbl = tr("Saturday");
        break;
    }
    ui->lblDay->setText(lbl);
    m_day = day;
}

int AvailabilityWidget::Day()
{
    return m_day;
}

QDateTime AvailabilityWidget::FromTime()
{
    return ui->timeFrom->dateTime();
}

QDateTime AvailabilityWidget::ToTime()
{
    return ui->timeTo->dateTime();
}
