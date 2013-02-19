#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include <QWidget>
#include <QTime>
#include <QSpinBox>

namespace Ui {
class TimeEditor;
}

class TimeEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeEditor(QWidget *parent = 0);
    ~TimeEditor();

    void setTime(int hh, int mm, int ss);
    void setTime(QTime time);
    QTime time();

    void setMinTime(int hh, int mm, int ss);
    void setMinTime(QTime time);
    QTime minTime();

    void setMaxTime(int hh, int mm, int ss);
    void setMaxTime(QTime time);
    QTime maxTime();

    void setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2);
    void setValidRange(QTime from, QTime To);

    void SetSecondsVisisbility(bool visible);
    bool secondsVisibility();

private:
    bool checkTime(int hh, int mm, int ss);
    int HHMMSS2Seconds(int hh, int mm, int ss);
    QTime Seconds2Time(int seconds);
    void onValueChanged(QSpinBox *control, int arg1);
    
signals:
    void timeChanged(QTime newTime);

private slots:
    void on_spinHours_valueChanged(int arg1);
    void on_spinMinutes_valueChanged(int arg1);
    void on_spinSeconds_valueChanged(int arg1);

private:
    Ui::TimeEditor *ui;

    int currentTime; // Stored in seconds
    int minValue;
    int maxValue;
};

#endif // TIMEEDITOR_H
