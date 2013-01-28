#ifndef PLANIFICACIONESDIASSUBSECTORES_H
#define PLANIFICACIONESDIASSUBSECTORES_H

#include "acollection.h"

class PlanificacionesDiasSubSectores : public ACollection
{
    Q_OBJECT
public:
    explicit PlanificacionesDiasSubSectores(QObject *parent = 0);
    virtual void loadData();
    virtual void saveData();
    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual void edit(QVariant ID);
    virtual void deleteElement(QVariant ID);
signals:
    
public slots:
    
};

typedef boost::shared_ptr<PlanificacionesDiasSubSectores> PlanificacionesSubSectoresPtr;
#endif // PLANIFICACIONESDIASSUBSECTORES_H
