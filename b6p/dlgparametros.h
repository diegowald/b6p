#ifndef DLGPARAMETROS_H
#define DLGPARAMETROS_H

#include <QDialog>

namespace Ui {
class DlgParametros;
}

class DlgParametros : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgParametros(QWidget *parent = 0);
    ~DlgParametros();
    
    virtual void accept();
private slots:
    void on_pushButton_pressed();

private:
    Ui::DlgParametros *ui;
};

#endif // DLGPARAMETROS_H
