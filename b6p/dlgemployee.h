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
    EmpleadoPtr getData();

protected:
    void setupScreen();
    void setupAssignment(AvailabilityWidget* w, QString label);

private:
    Ui::DlgEmployee *ui;
};

#endif // DLGEMPLOYEE_H
