#ifndef ESTIMACIONESDIAS_H
#define ESTIMACIONESDIAS_H
#include "acollection.h"

class EstimacionesDias : public ACollection
{
    Q_OBJECT
public:
    EstimacionesDias(QObject *parent = 0);
    virtual void loadData();
    virtual void saveData();


};

typedef boost::shared_ptr<EstimacionesDias> EstimacionesDiasPtr;
#endif // ESTIMACIONESDIAS_H
