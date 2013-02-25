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

    void setIDSector(int IDSector);
    void setIDSubSector(int IDSubSector);

    void setCapacity(int capacity);

    int IDSector();
    int IDSubSector();
    int Capacity();

    void setAlreadyCreated();
    bool alreadyCreated();
protected:
    void llenarSectores();
    void llenarSubSectores(int IDSector);
private slots:
    void on_slideCapacity_valueChanged(int value);

    void on_cboSectores_currentIndexChanged(int index);

private:
    Ui::CapacityWidget *ui;
    bool m_AlreadyCreated;
};

#endif // CAPACITYWIDGET_H
