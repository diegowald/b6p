#ifndef DLGEMPLOYEE_H
#define DLGEMPLOYEE_H

#include <QDialog>
#include "empleado.h"
#include "availabilitywidget.h"

namespace Ui {
class DlgEmployee;
}

class DlgEmployee : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgEmployee(QWidget *parent = 0);
    ~DlgEmployee();

    void setData(EmpleadoPtr empleado);

    QString Apellido();
    QString Nombres();
    QDate FechaIngreso();
    QString Legajo();
    CapacidadPersonaSectorLst Capacities();
    CalendarioPersonaLst Disponibilidades();

protected:
    void setupScreen();
    void setupAssignment(AvailabilityWidget* w, int day);
    CalendarioPersonaPtr getAssignment(AvailabilityWidget *w);

private slots:
    void on_btnAdd_pressed();

    void on_btnDelete_pressed();

    void on_btnAdd_2_clicked();

    void on_btnEdit_2_clicked();

    void on_btnDelete_2_clicked();

private:
    Ui::DlgEmployee *ui;
    EmpleadoPtr m_Empleado;
};

#endif // DLGEMPLOYEE_H
