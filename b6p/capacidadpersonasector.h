#ifndef CAPACIDADPERSONASECTOR_H
#define CAPACIDADPERSONASECTOR_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
#include "subsector.h"
#include "empleado.h"

class CapacidadPersonaSector : public QObject
{
    Q_OBJECT
public:
    explicit CapacidadPersonaSector(QObject *parent = 0);

    
    NullableField<int> IDSector();
    NullableField<int> ID_SubSector();
    NullableField<int> IDEmpleado();
    NullableField<float> Capacidad();

    void IDSector(NullableField<int> value);
    void IDSubSector(NullableField<int> value);
    void IDEmpleado(NullableField<int> value);
    void Capacidad(NullableField<float> value);

    SectorPtr getSector();
    SubSectorPtr getSubSector();
    EmpleadoPtr getEmpleado();

signals:
    
public slots:
    
private:
    NullableField<int> m_IDSector;
    NullableField<int> m_ID_SubSector;
    NullableField<int> m_IDEmpleado;
    NullableField<float> m_Capacidad;
};

typedef boost::shared_ptr<CapacidadPersonaSector> CapacidadPersonaSectorPtr;
#endif // CAPACIDADPERSONASECTOR_H
