#include "accesos.h"
#include "datastore.h"

Accesos::Accesos(QObject *parent)
    : ACollection(tr("Access"), "Access", false, parent)
{
}

QString Accesos::getSelectFromMainDB()
{
    return "";
}

QString Accesos::getSqlString()
{
    return QString("select IDSector, Feature, canRead, canCreate, canUpdate, canDelete, sent from access ");
//            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void Accesos::addRecord(RecordPtr record, bool)
{
    AccesoPtr a = boost::make_shared<Acceso>(this);

    a->IDSector().setValue((*record)["IDSector"].toInt());
    a->Feature().setValue((*record)["Feature"].toString());
    a->canCreate().setValue((*record)["canCreate"].toBool());
    a->canRead().setValue((*record)["canRead"].toBool());
    a->canUpdate().setValue((*record)["canUpdate"].toBool());
    a->canDelete().setValue((*record)["canDelete"].toBool());
    a->setSentStatus((*record)["sent"].toInt() == 1);

    a->setInitialized();

    std::pair<int, QString> id = std::make_pair(a->IDSector().value(), a->Feature().value());
    m_AccessList[id] = a;
}

void Accesos::updateRecord(RecordPtr)
{
}

void Accesos::deleteRecord(RecordPtr)
{
}

bool Accesos::exists(RecordPtr)
{
    return true;
}

RecordSet Accesos::getRecords(RecordStatus)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    return res;
}

RecordSet Accesos::getUnsent()
{
    return boost::make_shared<QList<RecordPtr> >();
}

void Accesos::defineHeaders(QStringList &)
{
}

boost::shared_ptr<QList<QStringList> > Accesos::getAll()
{
    return boost::shared_ptr<QList<QStringList> >();
}

void Accesos::fillData(QTreeWidget &)
{
}

bool Accesos::addNew()
{
    return false;
}

bool Accesos::addNew(QTreeWidgetItem *)
{
    return false;
}

bool Accesos::edit(QVariant)
{
    return false;
}

bool Accesos::edit(QTreeWidgetItem *, QVariant)
{
    return false;
}

bool Accesos::deleteElement(QVariant)
{
    return false;
}

bool Accesos::canBeDeleted(QVariant)
{
    return false;
}

void Accesos::setStatusToUnmodified(bool)
{
}

bool Accesos::canRead(int IDUser, QString &feature)
{
    return get(IDUser, feature, CAN_READ);
}

bool Accesos::canCreate(int IDUser, QString &feature)
{
    return get(IDUser, feature, CAN_CREATE);
}

bool Accesos::canUpdate(int IDUser, QString &feature)
{
    return get(IDUser, feature, CAN_UPDATE);
}

bool Accesos::canDelete(int IDUser, QString &feature)
{
    return get(IDUser, feature, CAN_DELETE);
}

bool Accesos::get(int IDUser, QString &feature, ACCESS access)
{
    CapacidadPersonaSectorLst caps = DataStore::instance()->getCapacidades()->getAll(IDUser, false);

    bool res = false;

    foreach (CapacidadPersonaSectorPtr c, *caps)
    {
        res = getBySector(c->IDSector().value(), feature, access);
        if (res)
            return res;
    }
    return res;
}

bool Accesos::getBySector(int IDSector, QString &feature, ACCESS access)
{
    bool res = false;

    std::pair<int, QString> id = std::make_pair(IDSector, feature);
    if (m_AccessList.find(id) != m_AccessList.end())
    {
        AccesoPtr a = m_AccessList[id];
        switch(access)
        {
        case CAN_READ:
            res = a->CanRead();
            break;
        case CAN_CREATE:
            res = a->CanCreate();
            break;
        case CAN_UPDATE:
            res = a->CanUpdate();
            break;
        case CAN_DELETE:
            res = a->CanDelete();
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool Accesos::canAccessApplication(int IDUser)
{
    QString feature = "whole application";
    return canRead(IDUser, feature);
}
