#include "timeassignment.h"
#include "ui_timeassignment.h"

TimeAssignment::TimeAssignment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeAssignment)
{
    ui->setupUi(this);
}

TimeAssignment::~TimeAssignment()
{
    delete ui;
}
