#ifndef DLGFILESYNCHRONIZATION_H
#define DLGFILESYNCHRONIZATION_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class DlgFileSynchronization;
}

class DlgFileSynchronization : public QDialog
{
    Q_OBJECT

public:
    explicit DlgFileSynchronization(QWidget *parent = 0);
    ~DlgFileSynchronization();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DlgFileSynchronization *ui;
};

#endif // DLGFILESYNCHRONIZATION_H
