#include "dlglogin.h"
#include "ui_dlglogin.h"
#include "datastore.h"

DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    ui->setupUi(this);
    llenarComboUsuarios();
}

DlgLogin::~DlgLogin()
{
    delete ui;
}

void DlgLogin::llenarComboUsuarios()
{
    EmpleadosLst emps = DataStore::instance()->getEmpleados()->getPowerUsers();
    foreach(EmpleadoPtr e, *emps)
    {
        ui->cboUsers->addItem(e->Apellido().value() + ", " + e->Nombre().value(), e->IDEmpleado().value());
    }
}

bool DlgLogin::hasUsers()
{
    return ui->cboUsers->count() > 0;
}

int DlgLogin::getIDUser()
{
    return ui->cboUsers->itemData(ui->cboUsers->currentIndex(), Qt::UserRole).toInt();
}
