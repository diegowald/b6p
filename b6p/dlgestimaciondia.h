#ifndef DLGESTIMACIONDIA_H
#define DLGESTIMACIONDIA_H

#include <QDialog>
#include "estimaciondia.h"

namespace Ui {
class DlgEstimacionDia;
}

class DlgEstimacionDia : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgEstimacionDia(QWidget *parent = 0);
    ~DlgEstimacionDia();
    
    void setData(EstimacionDiaPtr data);

    QDate Dia();
    int EstimacionHoras();

private:
    Ui::DlgEstimacionDia *ui;
};

#endif // DLGESTIMACIONDIA_H
