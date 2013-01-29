#ifndef PLANIFICACIONESDIAS_H
#define PLANIFICACIONESDIAS_H

#include "acollection.h"
#include "planificaciondia.h"

class PlanificacionesDias : public ACollection
{
    Q_OBJECT
public:
    explicit PlanificacionesDias(QObject *parent = 0);
    virtual QString getSqlString();
    virtual void addRecord(Record &record);
    virtual void saveData();
    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual void edit(QVariant ID);
    virtual void deleteElement(QVariant ID);
signals:
    
public slots:
    
private:
    QMap<QDate, PlanificacionDiaPtr> m_Planificaciones;
};

typedef boost::shared_ptr<PlanificacionesDias> PlanificacionesDiasPtr;
#endif // PLANIFICACIONESDIAS_H
