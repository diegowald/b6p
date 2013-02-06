#ifndef CAPACIDADPERSONASECTOR_H
#define CAPACIDADPERSONASECTOR_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
#include "subsector.h"

class CapacidadPersonaSector;

typedef boost::shared_ptr<CapacidadPersonaSector> CapacidadPersonaSectorPtr;
typedef boost::shared_ptr<QList<CapacidadPersonaSectorPtr> > CapacidadPersonaSectorLst;


class CapacidadPersonaSector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit CapacidadPersonaSector(QObject *parent = 0);

    
    NullableField<int> &IDSector();
    NullableField<int> &ID_SubSector();
    NullableField<int> &IDEmpleado();
    NullableField<int> &Capacidad();

    bool EqualsTo(CapacidadPersonaSectorPtr other);
    void updateWith(CapacidadPersonaSectorPtr other);

    /*void IDSector(NullableField<int> value);
    void IDSubSector(NullableField<int> value);
    void IDEmpleado(NullableField<int> value);
    void Capacidad(NullableField<int> value);*/

    SectorPtr getSector();
    SubSectorPtr getSubSector();

    virtual RecordPtr asRecordPtr();
    void updateIDEmpleado(int newId);
signals:
    
public slots:
    
private:
    NullableField<int> m_IDSector;
    NullableField<int> m_ID_SubSector;
    NullableField<int> m_IDEmpleado;
    NullableField<int> m_Capacidad;
};

#endif // CAPACIDADPERSONASECTOR_H
