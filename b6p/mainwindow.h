#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionOpen_triggered();

    void on_actionApprove_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionView_triggered();

    void on_actionParameters_triggered();

    void on_actionAbout_triggered();

    void datastore_loaded(QString name);
    void datastore_loading(QString name);
    void datastore_saved(QString name);
    void datastore_saving(QString name);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
