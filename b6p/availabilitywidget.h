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
    void setFrom(int value);
    void setTo(int value);

    void setDay(int day);
    int Day();
    int FromTime();
    int ToTime();

private:
    Ui::AvailabilityWidget *ui;
    int m_day;
};

#endif // AVAILABILITYWIDGET_H
