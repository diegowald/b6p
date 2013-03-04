#ifndef DLGSYNCHRONIZATION_H
#define DLGSYNCHRONIZATION_H

#include <QDialog>
#include "SincroManager.h"

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
    boost::shared_ptr<SincroManager> sincro;
};

#endif // DLGSYNCHRONIZATION_H
