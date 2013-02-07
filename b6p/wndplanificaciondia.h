#ifndef WNDPLANIFICACIONDIA_H
#define WNDPLANIFICACIONDIA_H

#include <QMainWindow>

namespace Ui {
class WndPlanificacionDia;
}

class WndPlanificacionDia : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit WndPlanificacionDia(QWidget *parent = 0);
    ~WndPlanificacionDia();
    
private:
    Ui::WndPlanificacionDia *ui;
};

#endif // WNDPLANIFICACIONDIA_H
