#include "timeeditor.h"
#include "ui_timeeditor.h"
#include <QDebug>


TimeEditor::TimeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeEditor)
{
    ui->setupUi(this);
    setDefaultValues();
}

TimeEditor::~TimeEditor()
{
    delete ui;
}

void TimeEditor::onValueChanged(QSpinBox *control, int arg1)
{
    if (checkTime(ui->spinHours->value(), ui->spinMinutes->value(), ui->spinSeconds->value()))
    {
        currentTime = HHMMSS2Seconds(ui->spinHours->value(), ui->spinMinutes->value(), ui->spinSeconds->value());
        emit timeChanged(currentTime);
    }
    else
        qDebug() << "MAL";

/*    if (arg1 > 9)
        control->setPrefix("");
    else
        control->setPrefix("0");*/
}

void TimeEditor::on_spinHours_valueChanged(int arg1)
{
    onValueChanged(ui->spinHours, arg1);
}

void TimeEditor::on_spinMinutes_valueChanged(int arg1)
{
    onValueChanged(ui->spinMinutes, arg1);
}

void TimeEditor::on_spinSeconds_valueChanged(int arg1)
{
    onValueChanged(ui->spinSeconds, arg1);
}

void TimeEditor::setTime(int hh, int mm, int ss)
{
    setTime(HHMMSS2Seconds(hh, mm, ss));
}

void TimeEditor::setTime(int seconds)
{
    if (checkTime(seconds))
    {
        currentTime = seconds;
        ui->spinHours->setValue(getHours(seconds));
        ui->spinMinutes->setValue(getMinutes(seconds));
        ui->spinSeconds->setValue(getSeconds(seconds));
        emit timeChanged(currentTime);
    }
}

int TimeEditor::timeSeconds()
{
    return currentTime;
}

void TimeEditor::setMinTime(int hh, int mm, int ss)
{
    setMinTime(HHMMSS2Seconds(hh, mm, ss));
}

void TimeEditor::setMinTime(int seconds)
{
    minValue = seconds;
    ui->spinHours->setMinimum(getHours(seconds));
}

int TimeEditor::minTimeSeconds()
{
    return minValue;
}

void TimeEditor::setMaxTime(int hh, int mm, int ss)
{
    setMaxTime(HHMMSS2Seconds(hh, mm, ss));
}

void TimeEditor::setMaxTime(int seconds)
{
    maxValue = seconds;
    ui->spinHours->setMaximum(getHours(seconds));
}

int TimeEditor::maxTimeSeconds()
{
    return maxValue;
}

void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)
{
    setMinTime(hh1, mm1, ss1);
    setMaxTime(hh2, mm2, ss2);
}

void TimeEditor::setValidRange(int secondsFrom, int secondsTo)
{
    setMinTime(secondsFrom);
    setMaxTime(secondsTo);
}

void TimeEditor::SetSecondsVisibility(bool visible)
{
    ui->spinSeconds->setVisible(visible);
    int w = ui->spinHours->width() + ui->spinMinutes->width() + (visible ? ui->spinSeconds->width() : 0);
    int h = ui->spinHours->height();
    resize(w, h);
}

bool TimeEditor::secondsVisibility()
{
    return ui->spinSeconds->isVisible();
}

int TimeEditor::HHMMSS2Seconds(int hh, int mm, int ss)
{
    int seconds = ss;
    seconds += mm * 60;
    seconds += hh * 3600;
    return seconds;
}

bool TimeEditor::checkTime(int seconds)
{
    return (minValue <= seconds) && (seconds <= maxValue);
}

bool TimeEditor::checkTime(int hh, int mm, int ss)
{
    return checkTime(HHMMSS2Seconds(hh, mm, ss));
}

int TimeEditor::getHours(int seconds)
{
    return seconds / 3600;
}

int TimeEditor::getMinutes(int seconds)
{
    int hh = getHours(seconds);
    return (seconds - hh * 3600) / 60;
}

int TimeEditor::getSeconds(int seconds)
{
    return seconds % 60;
}


void TimeEditor::setDefaultValues()
{
    currentTime = 0;
    minValue = 0;
    maxValue = 24 * 3600;
    ui->spinHours->setMinimum(getHours(minValue));
    ui->spinHours->setMaximum(getHours(maxValue));
    ui->spinMinutes->setMinimum(0);
    ui->spinSeconds->setMinimum(0);
    ui->spinMinutes->setMaximum(59);
    ui->spinSeconds->setMaximum(59);
}
