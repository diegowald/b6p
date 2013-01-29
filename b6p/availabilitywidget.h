#ifndef AVAILABILITYWIDGET_H
#define AVAILABILITYWIDGET_H

#include <QWidget>
#include <QDateTime>
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
    void setAvailableFrom(QDateTime value);
    void setAvailableTo(QDateTime value);
    void setFrom(QDateTime value);
    void setFrom(QTime value);
    void setTo(QDateTime value);
    void setTo(QTime value);

private:
    Ui::AvailabilityWidget *ui;
};

#endif // AVAILABILITYWIDGET_H
