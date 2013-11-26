#include "dlglicencia.h"
#include "ui_dlglicencia.h"
#include "empleado.h"
#include "datastore.h"
#include "QsLog.h"

DlgLicencia::DlgLicencia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLicencia)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
}

DlgLicencia::~DlgLicencia()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgLicencia::setData(LicenciaEmpleadoPtr licencia)
{
    QLOG_TRACE_FN();
    EmpleadoPtr empleado = DataStore::instance()->getEmpleados()->getEmpleado(licencia->IDEmpleado().value(), false);
    idEmpleado = empleado->IDEmpleado().value();
    ui->lblEmployee->setText(QString("%1, %2").arg(empleado->Apellido().value(), empleado->Nombre().value()));
    if (!licencia->FechaDesde().isNull())
        ui->dateFrom->setDate(licencia->FechaDesde().value());
    if (!licencia->FechaHasta().isNull())
        ui->dateTo->setDate(licencia->FechaHasta().value());
    ui->cboType->setCurrentText(licencia->TipoLicencia().isNull() ? "" : licencia->TipoLicencia().value());
    ui->txtNotes->setText(licencia->Descripcion().isNull() ? "" : licencia->Descripcion().value());
}

int DlgLicencia::IDEmpleado()
{
    QLOG_TRACE_FN();
    return idEmpleado;
}

QDate DlgLicencia::FechaDesde()
{
    QLOG_TRACE_FN();
    return ui->dateFrom->date();
}

QDate DlgLicencia::FechaHasta()
{
    QLOG_TRACE_FN();
    return ui->dateTo->date();
}

QString DlgLicencia::TipoLicencia()
{
    QLOG_TRACE_FN();
    return ui->cboType->currentText();
}

QString DlgLicencia::Descripcion()
{
    QLOG_TRACE_FN();
    return ui->txtNotes->text();
}
