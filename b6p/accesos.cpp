#include "accesos.h"

Accesos::Accesos(QObject *parent)
    : ACollection(tr("Access"), false, parent)
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
