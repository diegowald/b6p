#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include <QWidget>
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
    void setTime(int seconds);
    int timeSeconds();

    void setMinTime(int hh, int mm, int ss);
    void setMinTime(int seconds);
    int minTimeSeconds();

    void setMaxTime(int hh, int mm, int ss);
    void setMaxTime(int seconds);
    int maxTimeSeconds();

    void setValidRange(int hh1, int mm1, int ss1, int hh2, int mm2, int ss2);
    void setValidRange(int secondsFrom, int secondsTo);

    void SetSecondsVisibility(bool visible);
    bool secondsVisibility();

private:
    bool checkTime(int hh, int mm, int ss);
    bool checkTime(int seconds);
    int HHMMSS2Seconds(int hh, int mm, int ss);
    int getHours(int seconds);
    int getMinutes(int seconds);
    int getSeconds(int seconds);
    void onValueChanged(QSpinBox *control, int arg1);
    void setDefaultValues();
signals:
    void timeChanged(int newTime);

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
