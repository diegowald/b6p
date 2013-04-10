#ifndef DLGPLANIFICACIONDIA_H
#define DLGPLANIFICACIONDIA_H

#include <QDialog>
#include "planificaciondia.h"
#include "planificacionsubsector.h"

namespace Ui {
class DlgPlanificacionDia;
}

class DlgPlanificacionDia : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgPlanificacionDia(QWidget *parent = 0);
    ~DlgPlanificacionDia();
    void setData(PlanificacionDiaPtr data);
    QDate Dia();
    QString Notas();
    int IDSupervisor();
    PlanificacionSubSectorLst Planificaciones();
private:
    void displayPlannedHours(double hours);

private slots:
    void on_btnAdd_pressed();
    void on_btnEdit_pressed();
    void slot_AssignmentChanged(int from, int to);

    void on_btnDelete_pressed();
    void on_calcularHoras(int IDEmpleado, int& horas);
    void on_refreshColorAssignments(/*int IDEmpleado*/);
    void on_AllowOverWorkingForEmployee(int IDEmpleado);

private:
    Ui::DlgPlanificacionDia *ui;
    QDate m_Dia;
    int newID;
    QList<int> SubsectorsToDelete;
};

#endif // DLGPLANIFICACIONDIA_H
