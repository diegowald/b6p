#ifndef SUBSECTOR_H
#define SUBSECTOR_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"
#include "sector.h"
class SubSector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit SubSector(QObject *parent = 0);
    
    NullableField<int> &IDSector();
    NullableField<int> &IDSubsector();
    NullableField<QString> &Nombre();
    NullableField<QString> &Descripcion();

    /*void IDSector(NullableField<int> value);
    void IDSubsector(NullableField<int> value);
    void Nombre(NullableField<QString> value);
    void Descripcion(NullableField<QString> value);*/

    SectorPtr getSector();

    virtual RecordPtr asRecordPtr();
signals:
    
public slots:
    
private:
    NullableField<int> m_IDSector;
    NullableField<int> m_IDSubSector;
    NullableField<QString> m_Nombre;
    NullableField<QString> m_Descripcion;
};

typedef boost::shared_ptr<SubSector> SubSectorPtr;
typedef boost::shared_ptr<QList<SubSectorPtr> > SubSectoresLst;

#endif // SUBSECTOR_H
