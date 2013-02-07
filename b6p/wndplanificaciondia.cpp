#include "wndplanificaciondia.h"
#include "ui_wndplanificaciondia.h"

WndPlanificacionDia::WndPlanificacionDia(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WndPlanificacionDia)
{
    ui->setupUi(this);
}

WndPlanificacionDia::~WndPlanificacionDia()
{
    delete ui;
}
