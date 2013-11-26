#ifndef DLGLICENCIA_H
#define DLGLICENCIA_H

#include <QDialog>
#include "licenciaempleado.h"

namespace Ui {
class DlgLicencia;
}

class DlgLicencia : public QDialog
{
    Q_OBJECT

public:
    explicit DlgLicencia(QWidget *parent = 0);
    ~DlgLicencia();

    void setData(LicenciaEmpleadoPtr licencia);

    int IDEmpleado();
    QDate FechaDesde();
    QDate FechaHasta();
    QString TipoLicencia();
    QString Descripcion();

private:
    Ui::DlgLicencia *ui;
    int idEmpleado;
};

#endif // DLGLICENCIA_H
