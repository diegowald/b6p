#include "timeeditor.h"
#include "ui_timeeditor.h"

TimeEditor::TimeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeEditor)
{
    ui->setupUi(this);
    currentTime = 0;
    minValue = 0;
    maxValue = 0;
    ui->spinMinutes->setMinimum(0);
    ui->spinSeconds->setMinimum(0);
    ui->spinMinutes->setMaximum(59);
    ui->spinSeconds->setMaximum(59);
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
        emit timeChanged(Seconds2Time(currentTime));
    }

    if (arg1 > 9)
        control->setPrefix("");
    else
        control->setPrefix("0");
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
    currentTime = HHMMSS2Seconds(hh, mm, ss);
    ui->spinHours->setValue(hh);
    ui->spinMinutes->setValue(mm);
    ui->spinSeconds->setValue(ss);
}

void TimeEditor::setTime(QTime time)
{
    setTime(time.hour(), time.minute(), time.second());
}

QTime TimeEditor::time()
{
    return Seconds2Time(currentTime);
}

void TimeEditor::setMinTime(int hh, int mm, int ss)
{
    minValue = HHMMSS2Seconds(hh, mm, ss);
    ui->spinHours->setMinimum(hh);
}

void TimeEditor::setMinTime(QTime time)
{
    setMinTime(time.hour(), time.minute(), time.second());
}

QTime TimeEditor::minTime()
{
    return Seconds2Time(minValue);
}

void TimeEditor::setMaxTime(int hh, int mm, int ss)
{
    maxValue = HHMMSS2Seconds(hh, mm, ss);
    ui->spinHours->setMaximum(hh);
}

void TimeEditor::setMaxTime(QTime time)
{
    setMaxTime(time.hour(), time.minute(), time.second());
}

QTime TimeEditor::maxTime()
{
    return Seconds2Time(maxValue);
}

void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)
{
    setMinTime(hh1, mm1, ss1);
    setMaxTime(hh2, mm2, ss2);
}

void TimeEditor::setValidRange(QTime from, QTime To)
{
    setMinTime(from);
    setMaxTime(To);
}

void TimeEditor::SetSecondsVisisbility(bool visible)
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

QTime TimeEditor::Seconds2Time(int seconds)
{
    int t = seconds;
    int hh = t / 3600;
    t -= hh * 3600;
    int mm = t / 60;
    t -= mm * 60;
    int ss = t;
    return QTime(hh, mm, ss);
}

bool TimeEditor::checkTime(int hh, int mm, int ss)
{
    int secondsToCheck = HHMMSS2Seconds(hh, mm, ss);
    return (minValue <= secondsToCheck) && (secondsToCheck <= maxValue);
}
