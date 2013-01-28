#ifndef SUBSECTORES_H
#define SUBSECTORES_H

#include "acollection.h"
#include "subsector.h"
#include <QMap>

class SubSectores : public ACollection
{
    Q_OBJECT
public:
    explicit SubSectores(QObject *parent = 0);
    virtual void loadData();
    virtual void saveData();

    SubSectorPtr getSubSector(int idSubSector);

    SubSectoresLst getAll();
    SubSectoresLst getAll(int IDSector);

signals:
    
public slots:
    
private:
    QMap<int, SubSectorPtr> m_SubSectores;
};

typedef boost::shared_ptr<SubSectores> SubSectoresPtr;
#endif // SUBSECTORES_H
