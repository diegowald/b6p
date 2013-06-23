#include "timeeditor.h"
#include "ui_timeeditor.h"
#include <QDebug>
#include <QIntValidator>

#include <QsLog.h>


TimeEditor::TimeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeEditor)
{
    QLOG_TRACE() << "TimeEditor::TimeEditor(QWidget *parent)";
    ui->setupUi(this);
    setDefaultValues();
}

TimeEditor::~TimeEditor()
{
    QLOG_TRACE() << "TimeEditor::~TimeEditor()";
    delete ui;
}

void TimeEditor::onValueChanged(QLineEdit *, int)
{
    QLOG_TRACE() << "void TimeEditor::onValueChanged(QLineEdit *, int)";
    if (checkTime(ui->lineHours->text().toInt(), ui->lineMinutes->text().toInt(), ui->lineSeconds->text().toInt()))
    {
        currentTime = HHMMSS2Seconds(ui->lineHours->text().toInt(), ui->lineMinutes->text().toInt(), ui->lineSeconds->text().toInt(), true);
        emit timeChanged(currentTime);
    }
    else
        emit IncorrectTime(tr("Time is incorrect"));
}

void TimeEditor::setTime(int hh, int mm, int ss)
{
    QLOG_TRACE() << "void TimeEditor::setTime(int hh, int mm, int ss)";
    setTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setTime(int seconds)
{
    QLOG_TRACE() << "void TimeEditor::setTime(int seconds)";
    int secondsOnSameDay = seconds % 86400;
    ui->chkBeyondThisDay->setChecked(seconds != secondsOnSameDay);
    if (checkTime(seconds))
    {
        currentTime = seconds;
        previouslySelectedHour = getHours(secondsOnSameDay);
        ui->lineHours->setText(QString::number(previouslySelectedHour));
        ui->lineMinutes->setText(QString::number(getMinutes(secondsOnSameDay)));
        ui->lineSeconds->setText(QString::number(getSeconds(secondsOnSameDay)));
        emit timeChanged(currentTime);
    }
}

int TimeEditor::timeSeconds()
{
    QLOG_TRACE() << "int TimeEditor::timeSeconds()";
    return currentTime;
}

void TimeEditor::setMinTime(int hh, int mm, int ss)
{
    QLOG_TRACE() << "void TimeEditor::setMinTime(int hh, int mm, int ss)";
    setMinTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMinTime(int seconds)
{
    QLOG_TRACE() << "void TimeEditor::setMinTime(int seconds)";
    minValue = seconds;
    QIntValidator* validator = new QIntValidator(getHours(seconds), getHours(maxValue), this);
    ui->lineHours->setValidator(validator);
}

int TimeEditor::minTimeSeconds()
{
    QLOG_TRACE() << "int TimeEditor::minTimeSeconds()";
    return minValue;
}

void TimeEditor::setMaxTime(int hh, int mm, int ss)
{
    QLOG_TRACE() << "void TimeEditor::setMaxTime(int hh, int mm, int ss)";
    setMaxTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMaxTime(int seconds)
{
    QLOG_TRACE() << "void TimeEditor::setMaxTime(int seconds)";
    maxValue = seconds;
    maxTimeBeyondThisDay = (maxValue > 86400);
    QIntValidator *validator = new QIntValidator(getHours(minValue), getHours(maxValue), this);
    ui->lineHours->setValidator(validator);
/*    if (maxTimeBeyondThisDay)
    {
        ui->spinHours->setMaximum(24);
    }
    else
    {
        int hours = getHours(seconds);
        hours = hours;
        //ui->spinHours->setMaximum(getHours(seconds));
        ui->spinHours->setMaximum(hours);
    }*/
}

int TimeEditor::maxTimeSeconds()
{
    QLOG_TRACE() << "int TimeEditor::maxTimeSeconds()";
    return maxValue;
}

void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)
{
    QLOG_TRACE() << "void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)";
    setMinTime(hh1, mm1, ss1);
    setMaxTime(hh2, mm2, ss2);
}

void TimeEditor::setValidRange(int secondsFrom, int secondsTo)
{
    QLOG_TRACE() << "void TimeEditor::setValidRange(int secondsFrom, int secondsTo)";
    setMinTime(secondsFrom);
    setMaxTime(secondsTo);
}

void TimeEditor::SetSecondsVisibility(bool visible)
{
    QLOG_TRACE() << "void TimeEditor::SetSecondsVisibility(bool visible)";
    ui->lineSeconds->setVisible(visible);
    int w = ui->lineHours->width() + ui->lineMinutes->width() + (visible ? ui->lineSeconds->width() : 0);
    int h = ui->lineHours->height();
    resize(w, h);
}

bool TimeEditor::secondsVisibility()
{
    QLOG_TRACE() << "bool TimeEditor::secondsVisibility()";
    return ui->lineSeconds->isVisible();
}

int TimeEditor::HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay)
{
    QLOG_TRACE() << "int TimeEditor::HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay)";
    int seconds = ss;
    seconds += mm * 60;
    seconds += hh * 3600;
    if (canBeBeyondThisDay && ui->chkBeyondThisDay->isChecked())
        seconds += 86400;
    return seconds;
}

bool TimeEditor::checkTime(int seconds)
{
    QLOG_TRACE() << "bool TimeEditor::checkTime(int seconds)";
    qDebug() << "minValue: " << minValue;
    qDebug() << "seconds: " << seconds;
    qDebug() << "maxValue: " << maxValue;
    return (minValue <= seconds) && (seconds <= maxValue);
}

bool TimeEditor::checkTime(int hh, int mm, int ss)
{
    QLOG_TRACE() << "bool TimeEditor::checkTime(int hh, int mm, int ss)";
    return checkTime(HHMMSS2Seconds(hh, mm, ss, true));
}

int TimeEditor::getHours(int seconds)
{
    QLOG_TRACE() << "int TimeEditor::getHours(int seconds)";
    return seconds / 3600;
}

int TimeEditor::getMinutes(int seconds)
{
    QLOG_TRACE() << "int TimeEditor::getMinutes(int seconds)";
    int hh = getHours(seconds);
    return (seconds - hh * 3600) / 60;
}

int TimeEditor::getSeconds(int seconds)
{
    QLOG_TRACE() << "int TimeEditor::getSeconds(int seconds)";
    return seconds % 60;
}

void TimeEditor::setDefaultValues()
{
    QLOG_TRACE() << "void TimeEditor::setDefaultValues()";
    currentTime = 0;
    previouslySelectedHour = 0;
    minValue = 0;
    maxValue = 24 * 3600;
    ui->chkBeyondThisDay->setChecked(false);
    maxTimeBeyondThisDay = false;
    QValidator *v = new QIntValidator(0, 24, this);
    ui->lineHours->setValidator(v);
    v = new QIntValidator(0, 59, this);
    ui->lineMinutes->setValidator(v);
    v = new QIntValidator(0, 59, this);
    ui->lineSeconds->setValidator(v);

}

bool TimeEditor::isBeyondThisDay() const
{
    QLOG_TRACE() << "bool TimeEditor::isBeyondThisDay() const";
    return ui->chkBeyondThisDay->isChecked();
}

void TimeEditor::on_lineHours_textChanged(const QString &arg1)
{
    QLOG_TRACE() << "void TimeEditor::on_lineHours_textChanged(const QString &arg1)";
    onValueChanged(ui->lineHours, arg1.toInt());
}

void TimeEditor::on_lineMinutes_textChanged(const QString &arg1)
{
    QLOG_TRACE() << "void TimeEditor::on_lineMinutes_textChanged(const QString &arg1)";
    onValueChanged(ui->lineMinutes, arg1.toInt());
}

void TimeEditor::on_lineSeconds_textChanged(const QString &arg1)
{
    QLOG_TRACE() << "void TimeEditor::on_lineSeconds_textChanged(const QString &arg1)";
    onValueChanged(ui->lineSeconds, arg1.toInt());
}

void TimeEditor::setbeyondThisDayVisibility(bool value)
{
    QLOG_TRACE() << "void TimeEditor::setbeyondThisDayVisibility(bool value)";
    ui->chkBeyondThisDay->setVisible(value);
}


bool TimeEditor::beyondThisDayVisibility()
{
    QLOG_TRACE() << "bool TimeEditor::beyondThisDayVisibility()";
    return ui->chkBeyondThisDay->isVisible();
}

void TimeEditor::on_chkBeyondThisDay_clicked(bool)
{
    QLOG_TRACE()  << "void TimeEditor::on_chkBeyondThisDay_clicked(bool)";
    onValueChanged(NULL, 0);
}
