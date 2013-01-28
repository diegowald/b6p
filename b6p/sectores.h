#ifndef SECTORES_H
#define SECTORES_H

#include "acollection.h"
#include "sector.h"
#include <QMap>

class Sectores : public ACollection
{
    Q_OBJECT
public:
    explicit Sectores(QObject *parent = 0);
    virtual void loadData();
    virtual void saveData();

    SectorPtr getSector(int IDSector);

signals:
    
public slots:
    
private:
    QMap<int, SectorPtr> m_Sectores;
};

typedef boost::shared_ptr<Sectores> SectoresPtr;
#endif // SECTORES_H
