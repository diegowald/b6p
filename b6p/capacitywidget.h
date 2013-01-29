#ifndef CAPACITYWIDGET_H
#define CAPACITYWIDGET_H

#include <QWidget>

namespace Ui {
class CapacityWidget;
}

class CapacityWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CapacityWidget(QWidget *parent = 0);
    ~CapacityWidget();

    void setSector(QString Sector);
    void setSubSector(QString SubSector);
    void setCapacity(int capacity);
private slots:
    void on_slideCapacity_valueChanged(int value);

private:
    Ui::CapacityWidget *ui;
};

#endif // CAPACITYWIDGET_H
