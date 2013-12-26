#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//Printing
#include <QtPrintSupport/QPrinter>
#include "genericlist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(int LoggedUser, QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void EnableActions();
private slots:
    void on_actionOpen_triggered();
    void on_actionPrint_triggered();
    void on_actionExit_triggered();
    void on_actionView_triggered();
    void on_actionParameters_triggered();
    void on_actionAbout_triggered();
    void datastore_loaded(QString name);
    void datastore_loading(QString name);
    void datastore_saved(QString name);
    void datastore_saving(QString name);
    void on_actionSetup_days_triggered();

    void on_actionSynchronize_triggered();

    void on_actionPrint_Preview_triggered();

    void print(QPrinter *printer);
    void printSelected(QPrinter *printer);

    void on_actionPrint_Selected_triggered();

    void on_actionPrint_Preview_Selected_Record_triggered();

    void on_actionHours_by_Sector_and_Subsector_triggered();

    void on_actionPlanned_hours_day_by_day_triggered();

    void on_actionHours_planned_by_employee_triggered();

    void on_actionPlanned_rests_triggered();

private:
    Ui::MainWindow *ui;
    int m_LoggedUser;
    GenericList *selectedWindowToPrint;
};

#endif // MAINWINDOW_H
