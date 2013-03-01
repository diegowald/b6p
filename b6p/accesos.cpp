#include "accesos.h"
#include "datastore.h"

Accesos::Accesos(QObject *parent)
    : ACollection(tr("Access"), "Access", false, parent)
{
}

QString Accesos::getSqlString()
{
    return QString("select IDSector, Feature, canRead, canCreate, canUpdate, canDelete from accesos ");
//            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void Accesos::addRecord(Record &record)
{
    AccesoPtr a = boost::make_shared<Acceso>(this);

    a->IDSector().setValue(record["IDSector"].toInt());
    a->Feature().setValue(record["Feature"].toString());
    a->canCreate().setValue(record["canCreate"].toBool());
    a->canRead().setValue(record["canRead"].toBool());
    a->canUpdate().setValue(record["canUpdate"].toBool());
    a->canDelete().setValue(record["canDelete"].toBool());

    a->setInitialized();

    std::pair<int, QString> id = std::make_pair(a->IDSector().value(), a->Feature().value());
    m_AccessList[id] = a;

}

RecordSet Accesos::getRecords(RecordStatus)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    return res;
}

void Accesos::defineHeaders(QStringList &)
{
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
        std::pair<int, QString> id = std::make_pair(c->IDSector().value(), feature);
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
        if (res)
            return res;
    }
    return res;
}

bool Accesos::canAccessApplication(int IDUser)
{
    QString feature = "whole application";
    CapacidadPersonaSectorLst caps = DataStore::instance()->getCapacidades()->getAll(IDUser, false);
    foreach(CapacidadPersonaSectorPtr c, *caps)
    {
        if (canRead(c->IDSector().value(), feature))
            return true;
    }
    return false;
}
