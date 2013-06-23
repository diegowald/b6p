#include "availabilitywidget.h"
#include "ui_availabilitywidget.h"
#include "datastore.h"
#include <QsLog.h>


AvailabilityWidget::AvailabilityWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailabilityWidget)
{
    QLOG_TRACE() << "AvailabilityWidget::AvailabilityWidget(QWidget *parent)";
    ui->setupUi(this);
    connect(ui->timeFrom, SIGNAL(timeChanged(int)), ui->widget, SLOT(setStartAssignment(int)));
    connect(ui->timeTo, SIGNAL(timeChanged(int)),ui->widget, SLOT(setEndAssignment(int)));

    ui->timeFrom->SetSecondsVisibility(false);
    ui->timeTo->SetSecondsVisibility(false);
    ui->timeFrom->setbeyondThisDayVisibility(false);

    ui->timeFrom->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
    ui->timeTo->setValidRange(
                DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0),
                DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));

    ui->widget->setInitialTimeline(DataStore::instance()->getParametros()->getValue(Parametros::OPEN_STORE, 0));

    ui->widget->setFinalTimeline(DataStore::instance()->getParametros()->getValue(Parametros::CLOSE_STORE, 86400));
}

AvailabilityWidget::~AvailabilityWidget()
{
    QLOG_TRACE() << "AvailabilityWidget::~AvailabilityWidget()";
    delete ui;
}

void AvailabilityWidget::setLabel(QString value)
{
    QLOG_TRACE() << "void AvailabilityWidget::setLabel(QString value)";
    ui->lblDay->setText(value);
}

void AvailabilityWidget::setFrom(int value)
{
    QLOG_TRACE() << "void AvailabilityWidget::setFrom(int value)";
    ui->timeFrom->setTime(value);
}

void AvailabilityWidget::setTo(int value)
{
    QLOG_TRACE() << "void AvailabilityWidget::setTo(int value)";
    ui->timeTo->setTime(value);
}

void AvailabilityWidget::setDay(int day)
{
    QLOG_TRACE() << "void AvailabilityWidget::setDay(int day)";
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
    QLOG_TRACE() << "int AvailabilityWidget::Day()";
    return m_day;
}

int AvailabilityWidget::FromTime()
{
    QLOG_TRACE() << "int AvailabilityWidget::FromTime()";
    return ui->timeFrom->timeSeconds();
}

int AvailabilityWidget::ToTime()
{
    QLOG_TRACE() << "int AvailabilityWidget::ToTime()";
    return ui->timeTo->timeSeconds();
}
