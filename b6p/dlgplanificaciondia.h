#ifndef DLGPLANIFICACIONDIA_H
#define DLGPLANIFICACIONDIA_H

#include <QDialog>
#include "planificaciondia.h"

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

private:
    void displayPlannedHours(double hours);

private slots:
    void on_btnAdd_pressed();
    void on_btnEdit_pressed();
    void slot_AssignmentChanged(QDateTime from, QDateTime to);

private:
    Ui::DlgPlanificacionDia *ui;
};

#endif // DLGPLANIFICACIONDIA_H
