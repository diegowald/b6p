#include "timeassignmentitemedit.h"
#include "ui_timeassignmentitemedit.h"

TimeAssignmentItemEdit::TimeAssignmentItemEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeAssignmentItemEdit)
{
    ui->setupUi(this);
}

TimeAssignmentItemEdit::~TimeAssignmentItemEdit()
{
    delete ui;
}
