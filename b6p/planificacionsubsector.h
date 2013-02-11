#ifndef PLANIFICACIONSUBSECTOR_H
#define PLANIFICACIONSUBSECTOR_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
#include "subsector.h"
#include "empleado.h"

class PlanificacionSubSector;
typedef boost::shared_ptr<PlanificacionSubSector> PlanificacionSubSectorPtr;
typedef boost::shared_ptr<QList<PlanificacionSubSectorPtr> > PlanificacionSubSectorLst;


class PlanificacionSubSector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit PlanificacionSubSector(QObject *parent = 0);

    NullableField<QDate> &Dia();
    NullableField<int> &IDSector();
    NullableField<int> &IDSubSector();
    NullableField<int> &IDEmpleado();
    NullableField<QTime> &HoraInicio();
    NullableField<QTime> &HoraFin();

    SectorPtr getSector();
    SubSectorPtr getSubsector();
    EmpleadoPtr getEmpleado();

    bool isEqualsTo(PlanificacionSubSectorPtr other);
    void updateWith(PlanificacionSubSectorPtr other);

    virtual RecordPtr asRecordPtr();

    double CantidadHoras();

signals:
    
public slots:
    
private:
    NullableField<QDate> m_Dia;
    NullableField<int> m_IDSector;
    NullableField<int> m_IDSubSector;
    NullableField<int> m_IDEmpleado;
    NullableField<QTime> m_HoraInicio;
    NullableField<QTime> m_HoraFin;
};


#endif // PLANIFICACIONSUBSECTOR_H
