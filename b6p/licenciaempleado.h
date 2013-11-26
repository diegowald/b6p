#ifndef LICENCIAEMPLEADP_H
#define LICENCIAEMPLEADP_H

#include <QObject>
#include "IRecord.h"
#include "nullablefield.h"
#include <QTextDocument>
#include <QDate>

class LicenciaEmpleado : public QObject, public IRecord
{
    Q_OBJECT
public:

    explicit LicenciaEmpleado(bool isNew, QObject *parent = 0);

    NullableField<int> &ID();
    NullableField<int> &IDEmpleado();
    NullableField<QDate> &FechaDesde();
    NullableField<QDate> &FechaHasta();
    NullableField<QString> &TipoLicencia();
    NullableField<QString> &Descripcion();

    bool print(QTextDocument &textDoc);

    virtual RecordPtr asRecordPtr();
    virtual void updateID(int newRecordId);
    virtual bool canBeDeleted();
    virtual bool isEqualsTo(RecordPtr record, const QStringList &fieldsToMerge);
    virtual bool contains(QDate &date);

signals:

public slots:

private:
    NullableField<int> id;
    NullableField<int> idEmpleado;
    NullableField<QDate> fechaDesde;
    NullableField<QDate> fechaHasta;
    NullableField<QString> tipoLicencia;
    NullableField<QString> descripcion;

};

typedef boost::shared_ptr<LicenciaEmpleado> LicenciaEmpleadoPtr;
typedef boost::shared_ptr<QList<LicenciaEmpleadoPtr> > LicenciasEmpleadosLst;

#endif // LICENCIAEMPLEADP_H
