#include "dlgparametros.h"
#include "ui_dlgparametros.h"

DlgParametros::DlgParametros(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgParametros)
{
    ui->setupUi(this);
}

DlgParametros::~DlgParametros()
{
    delete ui;
}
