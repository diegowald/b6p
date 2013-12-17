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

    void setbeyondThisDayVisibility(bool value);
    bool beyondThisDayVisibility();

    bool isBeyondThisDay() const;

private:
    bool checkTime(const QString& time);
    bool checkTime(int hh, int mm, int ss);
    bool checkTime(int seconds);
    int HHMMSS2Seconds(const QString &time, bool canBeBeyondThisDay);
    int HHMMSS2Seconds(int hh, int mm, int ss, bool canBeBeyondThisDay);
    int getHours(int seconds);
    int getMinutes(int seconds);
    int getSeconds(int seconds);
    void onValueChanged(QLineEdit *control, int arg1);
    void setDefaultValues();
signals:
    void timeChanged(int newTime);
    void IncorrectTime(const QString& cause);

private slots:
    void on_chkBeyondThisDay_clicked(bool checked);

    void on_lineTime_textChanged(const QString &arg1);

private:
    Ui::TimeEditor *ui;

    bool maxTimeBeyondThisDay;
    int currentTime; // Stored in seconds
    int minValue;
    int maxValue;
    int previouslySelectedHour;
};

#endif // TIMEEDITOR_H
