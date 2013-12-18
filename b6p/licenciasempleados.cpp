#include "licenciasempleados.h"
#include <QsLog.h>

#include <QDateTime>
#include "dlglicencia.h"
#include "datastore.h"

LicenciasEmpleados::LicenciasEmpleados(QObject *parent) :
    ACollection(tr("RestDays"), "RestDays", true, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
}

LicenciasEmpleados::~LicenciasEmpleados()
{
    QLOG_TRACE_FN();
}

QString LicenciasEmpleados::getSqlString()
{
    QLOG_TRACE_FN();

    return QString("select ID, IDEmpleado, FechaDesde, FechaHasta, tipoLicencia, descripcion, sent, RecordStatus from licenciasEmpleados");
}

QString LicenciasEmpleados::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID, IDEmpleado, FechaDesde, FechaHasta, tipoLicencia, descripcion, sent, RecordStatus from licenciasEmpleados "
                   " where LastUpdate >= :LASTUPDATE AND SenderMachine <> :SenderMachine;");
}

bool LicenciasEmpleados::printSelectedRecord(QVariant, QTextDocument &)
{
    /*QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (IDElement.toInt() == -1)
        return false;
    else
        licencia = getLicencia(IDElement.toInt(), false);

    return licencia->print(textDoc);*/
    return false;
}

void LicenciasEmpleados::addRecord(RecordPtr record, bool setNew)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = boost::make_shared<LicenciaEmpleado>(false, this);
    licencia->ID().setValue((*record)["ID"].toInt());
    licencia->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    licencia->FechaDesde().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaDesde"].toLongLong()).date());
    licencia->FechaHasta().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaHasta"].toLongLong()).date());
    licencia->TipoLicencia().setValue((*record)["tipoLicencia"].toString());
    licencia->Descripcion().setValue((*record)["descripcion"].toString());
    licencia->setLocalRecordStatus((RecordStatus)((*record)["RecordStatus"].toInt()));

    if (setNew)
        licencia->setNew();
    else
    {
        licencia->setInitialized();
    }

    m_Licencias[licencia->ID().value()] = licencia;
}

bool LicenciasEmpleados::exists(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return (licencia != LicenciaEmpleadoPtr());
}

void LicenciasEmpleados::updateRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    licencia->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    licencia->FechaDesde().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaDesde"].toLongLong()).date());
    licencia->FechaHasta().setValue(QDateTime::fromMSecsSinceEpoch((*record)["FechaHasta"].toLongLong()).date());
    licencia->TipoLicencia().setValue((*record)["TipoLicencia"].toString());
    licencia->Descripcion().setValue((*record)["Descripcion"].toString());
    if (isFromSincro)
    {
        licencia->setInMemoryRecordStatus(UNMODIFIED);
        licencia->setLocalRecordStatus(UNMODIFIED);
    }
}

void LicenciasEmpleados::deleteRecord(RecordPtr record, bool isFromSincro)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    licencia->setDeleted();// setValue(true);
    if (isFromSincro)
    {
        licencia->setInMemoryRecordStatus(UNMODIFIED);
        licencia->setLocalRecordStatus(UNMODIFIED);
    }
}

bool LicenciasEmpleados::isRecordUnsent(RecordPtr record)
{
    QLOG_TRACE_FN();
    if (!exists(record))
        return false;
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return licencia->isUnSent();
}

RecordPtr LicenciasEmpleados::getLocalRecord(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    return licencia->asRecordPtr();
}

QStringList LicenciasEmpleados::getFieldsToShowInMerge()
{
    QLOG_TRACE_FN();
    return QStringList();
}


void LicenciasEmpleados::defineHeaders(QStringList &list)
{
    QLOG_TRACE_FN();
    list << tr("Lastname")
         << tr("Firstname")
         << tr("ID")
         << tr("From")
         << tr("To")
         << tr("Type")
         << tr("Notes");
}


boost::shared_ptr<QList<QStringList> > LicenciasEmpleados::getAll()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QStringList> > res = boost::make_shared<QList<QStringList> >();

    LicenciasEmpleadosLst list = getAllLicencias();

    foreach(LicenciaEmpleadoPtr l, *list)
    {
        QStringList r;

        r << QString::number(l->IDEmpleado().value())
          << l->FechaDesde().value().toString()
          << l->FechaHasta().value().toString()
          << l->TipoLicencia().value()
          << l->Descripcion().value();
        res->push_back(r);
    }

    return res;
}

void LicenciasEmpleados::fillData(QTreeWidget &tree)
{
    QLOG_TRACE_FN();
    tree.clear();
    LicenciasEmpleadosLst licencias = this->getAllLicencias();
    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, QString::number(licencia->IDEmpleado().value()));
        item->setData(0, Qt::UserRole, licencia->ID().value());

        item->setText(1, licencia->FechaDesde().value().toString(Qt::TextDate));
        item->setText(2, licencia->FechaHasta().value().toString(Qt::TextDate));

        item->setText(3, licencia->TipoLicencia().value());
        item->setText(4, licencia->Descripcion().value());
        tree.insertTopLevelItem(0, item);
    }
}

QString LicenciasEmpleados::getTableName()
{
    return "licenciasempleados";
}

QString LicenciasEmpleados::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasempleados set RecordStatus = %1, sent = 0 where ID = :RECORD_ID;").arg(DELETED);
}

QString LicenciasEmpleados::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasempleados set RecordStatus = %1, sent = 0, "
                   " IDEmpleado = :IDEmpleado, FechaDesde = :FechaDesde, FechaHasta = :FechaHasta, "
                   " tipoLicencia = :tipoLicencia, descripcion = :descripcion WHERE ID = :RECORD_ID").arg(MODIFIED);
}

QString LicenciasEmpleados::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("IDEmpleado");
    parameters.append(":IDEmpleado");

    fields.append("FechaDesde");
    parameters.append(":FechaDesde");

    fields.append("FechaHasta");
    parameters.append(":FechaHasta");

    fields.append("tipoLicencia");
    parameters.append(":tipoLicencia");

    fields.append("descripcion");
    parameters.append(":descripcion");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));


    fields.append("sent");
    parameters.append("0");

    QString sql = "insert into licenciasEmpleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}

QString LicenciasEmpleados::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasempleados set RecordStatus = %1, sent = 0, SenderMachine = :SenderMachine where ID = :RECORD_ID;").arg(DELETED);
}

QString LicenciasEmpleados::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return QString("update licenciasempleados set RecordStatus = %1, sent = 0, "
                   " IDEmpleado = :IDEmpleado, FechaDesde = :FechaDesde, FechaHasta = :FechaHasta, "
                   " tipoLicencia = :tipoLicencia, descripcion = :descripcion, "
                   " SenderMachine = :SenderMachine WHERE ID = :RECORD_ID").arg(MODIFIED);
}

QString LicenciasEmpleados::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    QStringList fields;
    QStringList parameters;

    fields.append("ID");
    parameters.append(":RECORD_ID");

    fields.append("IDEmpleado");
    parameters.append(":IDEmpleado");

    fields.append("FechaDesde");
    parameters.append(":FechaDesde");

    fields.append("FechaHasta");
    parameters.append(":FechaHasta");

    fields.append("tipoLicencia");
    parameters.append(":tipoLicencia");

    fields.append("descripcion");
    parameters.append(":descripcion");

    fields.append("RecordStatus");
    parameters.append(QString::number(NEW));

    fields.append("sent");
    parameters.append("0");

    fields.append("SenderMachine");
    parameters.append(":SenderMachine");

    QString sql = "insert into licenciasEmpleados ("
            + fields.join(", ")
            + ") VALUES ("
            + parameters.join(", ")
            + ");";

    return sql;
}


QString LicenciasEmpleados::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return QString("select ID from licenciasempleados "
                   " where ID = :RECORD_ID ;");
}

RecordSet LicenciasEmpleados::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        switch (status)
        {
        case NEW:
            if (licencia->isNew(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        case MODIFIED:
            if (licencia->isModified(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        case DELETED:
            if (licencia->isDeleted(fromMemory))
                res->push_back(licencia->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

RecordSet LicenciasEmpleados::getUnsent()
{
    QLOG_TRACE_FN();
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (licencia->isUnSent())
            res->push_back(licencia->asRecordPtr());
    }
    return res;
}

void LicenciasEmpleados::refreshID(int oldID, int newRecordId)
{
    QLOG_TRACE_FN();
    QLOG_TRACE() << oldID;
    QLOG_TRACE() << m_Licencias.count();
    LicenciaEmpleadoPtr licencia = m_Licencias[-1];
    licencia->updateID(newRecordId);
    m_Licencias.remove(oldID);
    m_Licencias[newRecordId] = licencia;
}

void LicenciasEmpleados::saveDependants()
{
}

void LicenciasEmpleados::setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal)
{
    QLOG_TRACE_FN();
    QList<int> toDelete;
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (removeDeleted && licencia->isDeleted(true))
            toDelete.push_back(licencia->ID().value());
        else
        {
            if (impactInMemmory)
                licencia->setInMemoryRecordStatus(UNMODIFIED);
            if (impactLocal)
                licencia->setLocalRecordStatus(UNMODIFIED);
        }
    }
    foreach(int id, toDelete)
        m_Licencias.remove(id);
}

bool LicenciasEmpleados::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Licencias.find(ID.toInt()) != m_Licencias.end())
    {
        result = m_Licencias[ID.toInt()]->canBeDeleted();
    }
    return result;
}

bool LicenciasEmpleados::localRecordIsEqualsTo(RecordPtr record)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia = getLicencia((*record)["ID"].toInt(), true);
    if (licencia != LicenciaEmpleadoPtr())
    {
        return licencia->isEqualsTo(record, getFieldsToShowInMerge());
    }
    else
        return false;
}

bool LicenciasEmpleados::addNew()
{
    QLOG_TRACE_FN();
    int id = -1;
    return edit(id);
}

bool LicenciasEmpleados::addNewWithAdditionalData(QVariant data)
{
    QLOG_TRACE_FN();
    int id = -1;
    return editWithIDEmpleado(id, data.toInt());
}

bool LicenciasEmpleados::edit(QVariant ID)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (ID == -1)
        licencia = boost::make_shared<LicenciaEmpleado>(true, this);
    else
        licencia = getLicencia(ID.toInt(), false);
    DlgLicencia dlg;
    dlg.setData(licencia);
    if (dlg.exec() == QDialog::Accepted)
    {
        licencia->IDEmpleado().setValue(dlg.IDEmpleado());
        licencia->FechaDesde().setValue(dlg.FechaDesde());
        licencia->FechaHasta().setValue(dlg.FechaHasta());
        licencia->TipoLicencia().setValue(dlg.TipoLicencia());
        licencia->Descripcion().setValue(dlg.Descripcion());

        m_Licencias[licencia->ID().value()] = licencia;
        return true;
    }
    return false;
}

bool LicenciasEmpleados::editWithIDEmpleado(int ID, int idEmpleado)
{
    QLOG_TRACE_FN();
    LicenciaEmpleadoPtr licencia;
    if (ID == -1)
    {
        licencia = boost::make_shared<LicenciaEmpleado>(true, this);
        licencia->IDEmpleado().setValue(idEmpleado);
    }
    else
        licencia = getLicencia(ID, false);
    DlgLicencia dlg;
    dlg.setData(licencia);
    if (dlg.exec() == QDialog::Accepted)
    {
        licencia->IDEmpleado().setValue(dlg.IDEmpleado());
        licencia->FechaDesde().setValue(dlg.FechaDesde());
        licencia->FechaHasta().setValue(dlg.FechaHasta());
        licencia->TipoLicencia().setValue(dlg.TipoLicencia());
        licencia->Descripcion().setValue(dlg.Descripcion());
        QLOG_TRACE() << licencia->ID().value();
        m_Licencias[licencia->ID().value()] = licencia;
        return true;
    }
    return false;
}

bool LicenciasEmpleados::addNew(QTreeWidgetItem *)
{
    return false;
}

bool LicenciasEmpleados::edit(QTreeWidgetItem *, QVariant)
{
    return false;
}

bool LicenciasEmpleados::deleteElement(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (m_Licencias.find(ID.toInt()) != m_Licencias.end())
    {
        m_Licencias[ID.toInt()]->setDeleted();
        result = true;
    }
    return result;
}


LicenciaEmpleadoPtr LicenciasEmpleados::getLicencia(int idLicencia, bool /*includeDeleted*/)
{
    QLOG_TRACE_FN();
    if (m_Licencias.find(idLicencia) == m_Licencias.end())
        return LicenciaEmpleadoPtr();
    else
    {
        LicenciaEmpleadoPtr licencia = m_Licencias[idLicencia];
        return licencia;
    }
}


LicenciasEmpleadosLst LicenciasEmpleados::getAllLicencias()
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        licencias->push_back(licencia);
    }
    return licencias;
}

LicenciasEmpleadosLst LicenciasEmpleados::getFrancos(QDate &date)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    QString TipoFranco = DataStore::instance()->getParametros()->getFrancoType();
    foreach(LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->FechaDesde().value() <= date) && (date <= licencia->FechaHasta().value()) && (licencia->TipoLicencia().value() == TipoFranco))
        {
            licencias->push_back(licencia);
        }
    }
    return licencias;
}

LicenciasEmpleadosLst LicenciasEmpleados::getAllLicenciasEmpleado(int idEmpleado)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if (licencia->IDEmpleado().value() == idEmpleado)
            licencias->push_back(licencia);
    }
    return licencias;
}

LicenciaEmpleadoPtr LicenciasEmpleados::getLicenciaEmpleado(int idEmpleado, QDate &date)
{
    QLOG_TRACE_FN();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->IDEmpleado().value() == idEmpleado) && (licencia->contains(date)))
        {
            return licencia;
        }
    }
    return LicenciaEmpleadoPtr();
}

LicenciaEmpleadoPtr LicenciasEmpleados::getUltimoFranco(int idEmpleado, QDate& date)
{
    QLOG_TRACE_FN();
    LicenciasEmpleadosLst licencias = getAllLicenciasEmpleado(idEmpleado);
    LicenciasEmpleadosLst licenciasPreviasAFecha = boost::make_shared<QList<LicenciaEmpleadoPtr> >();
    QString ultimoFrancoType = DataStore::instance()->getParametros()->getFrancoType();
    foreach (LicenciaEmpleadoPtr licencia, *licencias)
    {
        if ((licencia->FechaDesde().value() <= date) && (date <= licencia->FechaHasta().value())
                && (licencia->TipoLicencia().value() == ultimoFrancoType))
        {
            licenciasPreviasAFecha->push_back(licencia);
        }
    }

    LicenciaEmpleadoPtr ultimaLicencia = LicenciaEmpleadoPtr();
    if (licenciasPreviasAFecha->count() > 0)
    {
        ultimaLicencia = licenciasPreviasAFecha->at(0);
        foreach (LicenciaEmpleadoPtr licencia, *licenciasPreviasAFecha)
        {
            if (ultimaLicencia->FechaHasta().value() < licencia->FechaHasta().value())
            {
                ultimaLicencia = licencia;
            }
        }
    }
    return ultimaLicencia;
}

bool LicenciasEmpleados::isOnLicence(int idEmpleado, QDate &date)
{
    QLOG_TRACE_FN();
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        if ((licencia->IDEmpleado().value() == idEmpleado) && (licencia->contains(date)))
        {
            return true;
        }
    }
    return false;
}

QStringList LicenciasEmpleados::getDistinctLicenceType()
{
    QLOG_TRACE_FN();
    QSet<QString> set;
    foreach (LicenciaEmpleadoPtr licencia, m_Licencias.values())
    {
        QLOG_TRACE() << licencia->TipoLicencia().value();
        if ((!licencia->TipoLicencia().isNull()) && (licencia->TipoLicencia().value() != ""))
            set.insert(licencia->TipoLicencia().value());
    }
    return set.toList();
}
