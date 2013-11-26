#include "licenciaempleado.h"
#include<QsLog.h>
#include <boost/make_shared.hpp>
#include "datastore.h"

LicenciaEmpleado::LicenciaEmpleado(bool isNew, QObject *parent)
    : QObject(parent)
{
    QLOG_TRACE_FN();
    if (isNew)
        id.setValue(-1);
    else
        id.setNull();
}

RecordPtr LicenciaEmpleado::asRecordPtr()
{
    QLOG_TRACE_FN();
    RecordPtr res = boost::make_shared<Record>();

    (*res)["ID"] = id.toVariant();
    (*res)["IDEmpleado"] = idEmpleado.toVariant();
    (*res)["FechaDesde"] = fechaDesde.toVariant();
    (*res)["FechaHasta"] = fechaHasta.toVariant();
    (*res)["TipoLicencia"] = tipoLicencia.toVariant();
    (*res)["Descripcion"] = descripcion.toVariant();

    (*res)["RecordStatus"] = getLocalRecordStatus(); // Capaz que es inmemoryRecordStatus



    (*res)[RECORD_ID] = idEmpleado.toVariant();
    return res;
}

void LicenciaEmpleado::updateID(int newRecordId)
{
    QLOG_TRACE_FN();
    id.setValue(newRecordId);
}

bool LicenciaEmpleado::canBeDeleted()
{
    return true;
}

bool LicenciaEmpleado::isEqualsTo(RecordPtr record, const QStringList &fieldsToMerge)
{
    QLOG_TRACE_FN();
    bool res = true;
    RecordPtr localRec = asRecordPtr();
    foreach (QString fld, fieldsToMerge) {
        res &= ((*record)[fld] == (*localRec)[fld]);
    }
    res &= ((*record)["RecordStatus"] == (*localRec)["RecordStatus"]);
    return res;
}

NullableField<int> &LicenciaEmpleado::ID()
{
    return id;
}

NullableField<int> &LicenciaEmpleado::IDEmpleado()
{
    return idEmpleado;
}

NullableField<QDate> &LicenciaEmpleado::FechaDesde()
{
    return fechaDesde;
}

NullableField<QDate> &LicenciaEmpleado::FechaHasta()
{
    return fechaHasta;
}

NullableField<QString> &LicenciaEmpleado::TipoLicencia()
{
    return tipoLicencia;
}

NullableField<QString> &LicenciaEmpleado::Descripcion()
{
    return descripcion;
}

bool LicenciaEmpleado::contains(QDate &date)
{
    bool from = fechaDesde.isNull() ? true : (fechaDesde.value() <= date);
    bool to = fechaHasta.isNull() ? true : (date <= fechaHasta.value());

    return from && to;
}
