#ifndef AVAILABILITYWIDGET_H
#define AVAILABILITYWIDGET_H

#include <QWidget>


namespace Ui {
class AvailabilityWidget;
}

class AvailabilityWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit AvailabilityWidget(QWidget *parent = 0);
    ~AvailabilityWidget();
    void setLabel(QString value);
    void setFrom1(int value);
    void setTo1(int value);
    void setFrom2(int value);
    void setTo2(int value);

    void setDay(int day);
    int Day();
    int FromTime1();
    int ToTime1();
    int FromTime2();
    int ToTime2();

private:
    Ui::AvailabilityWidget *ui;
    int m_day;
};

#endif // AVAILABILITYWIDGET_H
