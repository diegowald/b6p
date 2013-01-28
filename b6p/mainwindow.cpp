#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    ui->widget->setBackgroundColor(Qt::white);
    ui->widget->setTimeLineColor(Qt::lightGray);
    ui->widget->setTimeLineHeight(4);
    ui->widget->setAssignmentColor(Qt::darkRed);
    ui->widget->setAssignmentHeight(6);
    QDateTime dt = ui->widget->startAssignment();
    dt.setTime(QTime(10, 0, 0));
    ui->widget->setStartAssignment(dt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
