#include "timeeditor.h"
#include "ui_timeeditor.h"
#include <QDebug>
#include <QIntValidator>

#include <QsLog.h>


TimeEditor::TimeEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeEditor)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    setDefaultValues();
}

TimeEditor::~TimeEditor()
{
    QLOG_TRACE_FN();
    delete ui;
}

void TimeEditor::onValueChanged(QLineEdit *, int)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    setTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setTime(int seconds)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    return currentTime;
}

void TimeEditor::setMinTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    setMinTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMinTime(int seconds)
{
    QLOG_TRACE_FN();
    minValue = seconds;
    QIntValidator* validator = new QIntValidator(getHours(seconds), getHours(maxValue), this);
    ui->lineHours->setValidator(validator);
}

int TimeEditor::minTimeSeconds()
{
    QLOG_TRACE_FN();
    return minValue;
}

void TimeEditor::setMaxTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    setMaxTime(HHMMSS2Seconds(hh, mm, ss, false));
}

void TimeEditor::setMaxTime(int seconds)
{
    QLOG_TRACE_FN();
    maxValue = seconds;
    maxTimeBeyondThisDay = (maxValue > 86400);
    QIntValidator *validator = new QIntValidator(getHours(minValue), getHours(maxValue), this);
    ui->lineHours->setValidator(validator);
}

int TimeEditor::maxTimeSeconds()
{
    QLOG_TRACE_FN();
    return maxValue;
}

void TimeEditor::setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2)
{
    QLOG_TRACE_FN();
    setMinTime(hh1, mm1, ss1);
    setMaxTime(hh2, mm2, ss2);
}

void TimeEditor::setValidRange(int secondsFrom, int secondsTo)
{
    QLOG_TRACE_FN();
    setMinTime(secondsFrom);
    setMaxTime(secondsTo);
}

void TimeEditor::SetSecondsVisibility(bool visible)
{
    QLOG_TRACE_FN();
    ui->lineSeconds->setVisible(visible);
    int w = ui->lineHours->width() + ui->lineMinutes->width() + (visible ? ui->lineSeconds->width() : 0);
    int h = ui->lineHours->height();
    resize(w, h);
}

bool TimeEditor::secondsVisibility()
{
    QLOG_TRACE_FN();
    return ui->lineSeconds->isVisible();
}

int TimeEditor::HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay)
{
    QLOG_TRACE_FN();
    int seconds = ss;
    seconds += mm * 60;
    seconds += hh * 3600;
    if (canBeBeyondThisDay && ui->chkBeyondThisDay->isChecked())
        seconds += 86400;
    return seconds;
}

bool TimeEditor::checkTime(int seconds)
{
    QLOG_TRACE_FN();
    qDebug() << "minValue: " << minValue;
    qDebug() << "seconds: " << seconds;
    qDebug() << "maxValue: " << maxValue;
    return (minValue <= seconds) && (seconds <= maxValue);
}

bool TimeEditor::checkTime(int hh, int mm, int ss)
{
    QLOG_TRACE_FN();
    return checkTime(HHMMSS2Seconds(hh, mm, ss, true));
}

int TimeEditor::getHours(int seconds)
{
    QLOG_TRACE_FN();
    return seconds / 3600;
}

int TimeEditor::getMinutes(int seconds)
{
    QLOG_TRACE_FN();
    int hh = getHours(seconds);
    return (seconds - hh * 3600) / 60;
}

int TimeEditor::getSeconds(int seconds)
{
    QLOG_TRACE_FN();
    return seconds % 60;
}

void TimeEditor::setDefaultValues()
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    return ui->chkBeyondThisDay->isChecked();
}

void TimeEditor::on_lineHours_textChanged(const QString &arg1)
{
    QLOG_TRACE_FN();
    onValueChanged(ui->lineHours, arg1.toInt());
}

void TimeEditor::on_lineMinutes_textChanged(const QString &arg1)
{
    QLOG_TRACE_FN();
    onValueChanged(ui->lineMinutes, arg1.toInt());
}

void TimeEditor::on_lineSeconds_textChanged(const QString &arg1)
{
    QLOG_TRACE_FN();
    onValueChanged(ui->lineSeconds, arg1.toInt());
}

void TimeEditor::setbeyondThisDayVisibility(bool value)
{
    QLOG_TRACE_FN();
    ui->chkBeyondThisDay->setVisible(value);
}


bool TimeEditor::beyondThisDayVisibility()
{
    QLOG_TRACE_FN();
    return ui->chkBeyondThisDay->isVisible();
}

void TimeEditor::on_chkBeyondThisDay_clicked(bool)
{
    QLOG_TRACE_FN();
    onValueChanged(NULL, 0);
}
