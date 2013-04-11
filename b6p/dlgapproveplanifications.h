#ifndef DLGAPPROVEPLANIFICATIONS_H
#define DLGAPPROVEPLANIFICATIONS_H

#include <QDialog>
#include "planificaciondia.h"

namespace Ui {
class DlgApprovePlanifications;
}

class DlgApprovePlanifications : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgApprovePlanifications(QWidget *parent = 0);
    ~DlgApprovePlanifications();
    void setData(PlanificacionDiaLst data);
    PlanificacionDiaLst getPlanificacionToApprove();
private:
    Ui::DlgApprovePlanifications *ui;
};

#endif // DLGAPPROVEPLANIFICATIONS_H
