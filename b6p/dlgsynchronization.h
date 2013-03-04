#ifndef DLGSYNCHRONIZATION_H
#define DLGSYNCHRONIZATION_H

#include <QDialog>
#include "qmysql.h"

namespace Ui {
class DlgSynchronization;
}

class DlgSynchronization : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgSynchronization(QWidget *parent = 0);
    ~DlgSynchronization();

private slots:
    void on_btnStartSynchro_pressed();

private:
    void fillData();
private:
    Ui::DlgSynchronization *ui;
    boost::shared_ptr<QMysql> sincro;
};

#endif // DLGSYNCHRONIZATION_H
