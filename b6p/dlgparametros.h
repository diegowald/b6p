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
    
private:
    Ui::DlgParametros *ui;
};

#endif // DLGPARAMETROS_H