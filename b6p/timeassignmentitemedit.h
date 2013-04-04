#ifndef TIMEASSIGNMENTITEMEDIT_H
#define TIMEASSIGNMENTITEMEDIT_H

#include <QWidget>
#include <QDate>
#include <QVariant>
#include "empleado.h"

namespace Ui {
class TimeAssignmentItemEdit;
}

class TimeAssignmentItemEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignmentItemEdit(QWidget *parent = 0);
    ~TimeAssignmentItemEdit();
    
    double CantidadHoras();

    int IDSector();
    bool isSubSectorEmpty();
    int IDSubSector();
    bool isEmpleadoEmpty();
    int IDEmpleado();
    int HoraInicio();
    int HoraFin();

    void setIDSector(int value);
    void setIDSectorNull();
    void setIDSubSector(int value);
    void setIDSubSectorNull();
    void setIDEmpleado(int value);
    void setIDEmpleadoNull();
    void setHoraInicio(int value);
    void setHoraFin(int value);

    void setData(QVariant data);
    QVariant data();

    QDate Date();
    void setDate(QDate value);


signals:
    void AssignmentChanged(int fromSeconds, int toSeconds);

protected:
    void llenarSectores();
    void llenarSubSectores(int IDSector);
    void llenarEmpleados();
private slots:
    void on_cboSectores_currentIndexChanged(int index);
    void on_timeInicio_TimeChanged(int newTime);
    void on_timeFin_TimeChanged(int newTime);

    void on_cboSubsectores_currentIndexChanged(int index);

    void on_cboEmpleado_currentIndexChanged(int index);

private:
    Ui::TimeAssignmentItemEdit *ui;
    QDate date;
    QVariant m_Data;
    EmployeeCalculatedCapacityLst emps;
    bool loadingData;
};

#endif // TIMEASSIGNMENTITEMEDIT_H
