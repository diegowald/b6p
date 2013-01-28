#ifndef DLGEMPLOYEE_H
#define DLGEMPLOYEE_H

#include <QDialog>

namespace Ui {
class DlgEmployee;
}

class DlgEmployee : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgEmployee(QWidget *parent = 0);
    ~DlgEmployee();
    
private:
    Ui::DlgEmployee *ui;
};

#endif // DLGEMPLOYEE_H
