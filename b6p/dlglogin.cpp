#include "dlglogin.h"
#include "ui_dlglogin.h"
#include "datastore.h"
#include <QsLog.h>


DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    QLOG_TRACE_FN();
    ui->setupUi(this);
    llenarComboUsuarios();
}

DlgLogin::~DlgLogin()
{
    QLOG_TRACE_FN();
    delete ui;
}

void DlgLogin::llenarComboUsuarios()
{
    QLOG_TRACE_FN();
    EmpleadosLst emps = DataStore::instance()->getEmpleados()->getPowerUsers();
    foreach(EmpleadoPtr e, *emps)
    {
        ui->cboUsers->addItem(e->Apellido().value() + ", " + e->Nombre().value(), e->IDEmpleado().value());
    }
}

bool DlgLogin::hasUsers()
{
    QLOG_TRACE_FN();
    return ui->cboUsers->count() > 0;
}

int DlgLogin::getIDUser()
{
    QLOG_TRACE_FN();
    return ui->cboUsers->itemData(ui->cboUsers->currentIndex(), Qt::UserRole).toInt();
}
