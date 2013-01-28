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
    
private:
    Ui::AvailabilityWidget *ui;
};

#endif // AVAILABILITYWIDGET_H
