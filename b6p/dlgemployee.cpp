#include "dlgemployee.h"
#include "ui_dlgemployee.h"

DlgEmployee::DlgEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgEmployee)
{
    ui->setupUi(this);
}

DlgEmployee::~DlgEmployee()
{
    delete ui;
}
