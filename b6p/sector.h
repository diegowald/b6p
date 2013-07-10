#ifndef SECTOR_H
#define SECTOR_H

#include <QObject>
#include "IRecord.h"

#include <boost/shared_ptr.hpp>
#include "nullablefield.h"

class Sector : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit Sector(QObject *parent = 0);

    NullableField<int> &IDSector();
    NullableField<QString> &Nombre();
    NullableField<QString> &Descripcion();
    NullableField<bool> &ShowInPlanification();

    virtual RecordPtr asRecordPtr();
    virtual bool isEqualsTo(RecordPtr record);

signals:
    
public slots:
    
private:
    NullableField<int> m_IDSector;
    NullableField<QString> m_Nombre;
    NullableField<QString> m_Descripcion;
    NullableField<bool> m_ShowInPlanification;
};

typedef boost::shared_ptr<Sector> SectorPtr;
typedef boost::shared_ptr<QList<SectorPtr> > SectorLst;

#endif // SECTOR_H
