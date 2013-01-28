#ifndef SECTOR_H
#define SECTOR_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"

class Sector : public QObject
{
    Q_OBJECT
public:
    explicit Sector(QObject *parent = 0);

    NullableField<int> IDSector();
    NullableField<QString> Nombre();
    NullableField<QString> Descripcion();

    void IDSector(NullableField<int> value);
    void Nombre(NullableField<QString> value);
    void Descripcion(NullableField<QString> value);

signals:
    
public slots:
    
private:
    NullableField<int> m_IDSector;
    NullableField<QString> m_Nombre;
    NullableField<QString> m_Descripcion;
};

typedef boost::shared_ptr<Sector> SectorPtr;

#endif // SECTOR_H
