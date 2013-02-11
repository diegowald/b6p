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

    int IDSector();
    bool isSubSectorEmpty();
    int IDSubSector();
    bool isEmpleadoEmpty();
    int IDEmpleado();
    QTime HoraInicio();
    QTime HoraFin();

    void setIDSector(int value);
    void setIDSectorNull();
    void setIDSubSector(int value);
    void setIDSubSectorNull();
    void setIDEmpleado(int value);
    void setIDEmpleadoNull();
    void setHoraInicio(QTime value);
    void setHoraFin(QTime value);


    QDate Date();
    void setDate(QDate value);


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
    QDate date;
};

#endif // TIMEASSIGNMENTITEMEDIT_H
