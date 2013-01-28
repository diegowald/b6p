#ifndef EMPLEADOS_H
#define EMPLEADOS_H

#include <QObject>

#include "acollection.h"
#include "empleado.h"
#include <QMap>

class Empleados : public ACollection
{
    Q_OBJECT
public:
    explicit Empleados(QObject *parent = 0);
    virtual void loadData();
    virtual void saveData();

    EmpleadoPtr getEmpleado(int idEmpleado);
    EmpleadosLst getAll();
signals:
    
public slots:
    
private:
    QMap<int, EmpleadoPtr> m_Empleados;
};

typedef boost::shared_ptr<Empleados> EmpleadosPtr;
#endif // EMPLEADOS_H
