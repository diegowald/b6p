#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <QObject>
#include <boost/shared_ptr.hpp>

#include "nullablefield.h"
#include <QDate>

class Empleado : public QObject
{
    Q_OBJECT
public:
    explicit Empleado(QObject *parent = 0);
    
    NullableField<int> IDEmpleado();
    NullableField<QString> Apellido();
    NullableField<QString> Nombre();
    NullableField<QDate> FechaIngreso();

    void IDEmpleado(NullableField<int> value);
    void Apellido(NullableField<QString> value);
    void Nombre(NullableField<QString> value);
    void FechaIngreso(NullableField<QDate> value);

signals:
    
public slots:
    
private:
    NullableField<int> idEmpleado;
    NullableField<QString> apellido;
    NullableField<QString> nombre;
    NullableField<QDate> fechaIngreso;
};

typedef boost::shared_ptr<Empleado> EmpleadoPtr;
typedef boost::shared_ptr<QList<EmpleadoPtr> > EmpleadosLst;

#endif // EMPLEADO_H
