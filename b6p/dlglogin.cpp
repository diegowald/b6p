#include "dlglogin.h"
#include "ui_dlglogin.h"
#include "datastore.h"
#include <QsLog.h>


DlgLogin::DlgLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgLogin)
{
    QLOG_TRACE() << "DlgLogin::DlgLogin(QWidget *parent)";
    ui->setupUi(this);
    llenarComboUsuarios();
}

DlgLogin::~DlgLogin()
{
    QLOG_TRACE() << "DlgLogin::~DlgLogin()";
    delete ui;
}

void DlgLogin::llenarComboUsuarios()
{
    QLOG_TRACE() << "void DlgLogin::llenarComboUsuarios()";
    EmpleadosLst emps = DataStore::instance()->getEmpleados()->getPowerUsers();
    foreach(EmpleadoPtr e, *emps)
    {
        ui->cboUsers->addItem(e->Apellido().value() + ", " + e->Nombre().value(), e->IDEmpleado().value());
    }
}

bool DlgLogin::hasUsers()
{
    QLOG_TRACE() << "bool DlgLogin::hasUsers()";
    return ui->cboUsers->count() > 0;
}

int DlgLogin::getIDUser()
{
    QLOG_TRACE() << "int DlgLogin::getIDUser()";
    return ui->cboUsers->itemData(ui->cboUsers->currentIndex(), Qt::UserRole).toInt();
}
