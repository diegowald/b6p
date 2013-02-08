#ifndef TIMEASSIGNMENTITEMEDIT_H
#define TIMEASSIGNMENTITEMEDIT_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class TimeAssignmentItemEdit;
}

class TimeAssignmentItemEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignmentItemEdit(QWidget *parent = 0);
    ~TimeAssignmentItemEdit();
    
    double CantidadHoras();

signals:
    void AssignmentChanged(QDateTime from, QDateTime to);

protected:
    void llenarSectores();
    void llenarSubSectores(int IDSector);
    void llenarEmpleados();
private slots:
    void on_cboSectores_currentIndexChanged(int index);
    void on_timeInicio_dateTimeChanged(const QDateTime &dateTime);
    void on_timeFin_dateTimeChanged(const QDateTime &dateTime);

    void on_cboSubsectores_currentIndexChanged(int index);

private:
    Ui::TimeAssignmentItemEdit *ui;
};

#endif // TIMEASSIGNMENTITEMEDIT_H
