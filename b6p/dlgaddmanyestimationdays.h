#ifndef DLGADDMANYESTIMATIONDAYS_H
#define DLGADDMANYESTIMATIONDAYS_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DlgAddManyEstimationDays;
}

class DlgAddManyEstimationDays : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgAddManyEstimationDays(QWidget *parent = 0);
    ~DlgAddManyEstimationDays();

    void setFrom(QDate fromDate);
    void setTo(QDate toDate);
    QDate From();
    QDate To();
    
private:
    Ui::DlgAddManyEstimationDays *ui;
};

#endif // DLGADDMANYESTIMATIONDAYS_H
