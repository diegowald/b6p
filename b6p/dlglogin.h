#ifndef DLGLOGIN_H
#define DLGLOGIN_H

#include <QDialog>

namespace Ui {
class DlgLogin;
}

class DlgLogin : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgLogin(QWidget *parent = 0);
    ~DlgLogin();
    bool hasUsers();
    int getIDUser();
private:
    void llenarComboUsuarios();
private:
    Ui::DlgLogin *ui;
};

#endif // DLGLOGIN_H
