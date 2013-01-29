#ifndef CAPACIDADESPERSONASECTOR_H
#define CAPACIDADESPERSONASECTOR_H

#include <QObject>
#include "acollection.h"
#include "capacidadpersonasector.h"

class CapacidadesPersonaSector : public ACollection
{
    Q_OBJECT
public:
    explicit CapacidadesPersonaSector(QObject *parent = 0);

    virtual void loadData();
    virtual void saveData();
    virtual void defineHeaders(QStringList &list) ;
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual void edit(QVariant ID);
    virtual void deleteElement(QVariant ID);

    CapacidadPersonaSectorLst getAll(int IDEmpleado);
signals:
    
public slots:
    
private:
    QList<CapacidadPersonaSectorPtr> m_Capacidades;
};

typedef boost::shared_ptr<CapacidadesPersonaSector> CapacidadesPersonaSectorPtr;

#endif // CAPACIDADESPERSONASECTOR_H
