#ifndef PLANIFICACIONDIA_H
#define PLANIFICACIONDIA_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "empleado.h"
#include "estimaciondia.h"
#include "planificacionsubsector.h"

enum EstadosPlanificacion
{
    INPROGRESS,
    FINISHED,
    APPROVED
};

class PlanificacionDia : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit PlanificacionDia(QDate date, QObject *parent = 0);
    explicit PlanificacionDia(QObject *parent = 0);

    NullableField<QDate> &Dia();
    NullableField<QString> &Notas();
    NullableField<int> &IDSupervisor();
    int HorasPlanificadas();
    EmpleadoPtr Supervisor();
    EstimacionDiaPtr Estimacion();
    virtual RecordPtr asRecordPtr();
    QString Estado();

    void updatePlanificaciones(PlanificacionSubSectorLst dataFrom);

signals:
    
public slots:
    
private:
    NullableField<QDate> m_Dia;
    NullableField<QString> m_Notas;
    NullableField<int> m_IDSupervisor;
    NullableField<EstadosPlanificacion> m_EstadosPlanificacion;
};

typedef boost::shared_ptr<PlanificacionDia> PlanificacionDiaPtr;
typedef boost::shared_ptr<QList<PlanificacionDiaPtr> > PlanificacionDiaLst;

#endif // PLANIFICACIONDIA_H
