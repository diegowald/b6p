#ifndef DLGEMPLEADOSLICENCIASPLANIFICACION_H
#define DLGEMPLEADOSLICENCIASPLANIFICACION_H

#include <QDialog>
#include <QDate>
#include "empleado.h"

namespace Ui {
class DlgEmpleadosLicenciasPlanificacion;
}

class DlgEmpleadosLicenciasPlanificacion : public QDialog
{
    Q_OBJECT

public:
    explicit DlgEmpleadosLicenciasPlanificacion(QWidget *parent = 0);
    ~DlgEmpleadosLicenciasPlanificacion();

    void setData(QDate currentDay, QList<int> employeesToExclude);

private slots:
    void on_btnAdd_2_clicked();

    void on_btnEdit_2_clicked();

    void on_btnDelete_2_clicked();

private:
    void addEmpleadoToTree(EmpleadoPtr empleado);
    void fillTree();

private:
    Ui::DlgEmpleadosLicenciasPlanificacion *ui;
    QDate m_CurrentDay;
    QList<int> m_EmployeesToExclude;
};

#endif // DLGEMPLEADOSLICENCIASPLANIFICACION_H
