#ifndef PLANIFICACIONSUBSECTOR_H
#define PLANIFICACIONSUBSECTOR_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
#include "subsector.h"
#include "empleado.h"

class PlanificacionSubSector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit PlanificacionSubSector(QObject *parent = 0);

    NullableField<QDate> Dia();
    NullableField<int> IDSector();
    NullableField<int> IDSubSector();
    NullableField<int> IDEmpleado();
    NullableField<QTime> HoraInicio();
    NullableField<QTime> HoraFin();

    void Dia(NullableField<QDate> value);
    void IDSector(NullableField<int> value);
    void IDSubSector(NullableField<int> value);
    void IDEmpleado(NullableField<int> value);
    void HoraInicio(NullableField<QTime> value);
    void HoraFin(NullableField<QTime> value);

    SectorPtr getSector();
    SubSectorPtr getSubsector();
    EmpleadoPtr getEmpleado();
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

typedef boost::shared_ptr<PlanificacionSubSector> PlanificacionSubSectorPtr;
typedef boost::shared_ptr<QList<PlanificacionSubSectorPtr> > PlanificacionSubSectorLst;

#endif // PLANIFICACIONSUBSECTOR_H
