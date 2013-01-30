#include "sectores.h"

Sectores::Sectores(QObject *parent) :
    ACollection(tr("Sectors"), parent)
{
}

QString Sectores::getSqlString()
{
    return "select ID, Nombre, Descripcion from sectores;";
}

void Sectores::addRecord(Record &record)
{
    SectorPtr s(new Sector(this));

    s->IDSector(NullableField<int>(record["ID"].toInt()));
    s->Nombre(NullableField<QString>(record["Nombre"].toString()));
    s->Descripcion(NullableField<QString>(record["Descripcion"].toString()));

    m_Sectores[s->IDSector().value()] = s;
}

QString Sectores::getDeleteStatement()
{
    return "delete from sectores where ID = :ID;";
}

QString Sectores::getUpdateStatement()
{
    return "update sectores set Nombre = :Nombre, Descripcion = :Descripcion where ID = :ID;";
}

QString Sectores::getInsertStatement()
{
    return "insert into sectores "
            " (Nombre, Descripcion) "
            " values "
            " (:Nombre, :Descripcion);";
}

RecordSet Sectores::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(SectorPtr s, m_Sectores.values())
    {
        switch (status)
        {
        case NEW:
            if (s->isNew())
                res->push_back(s->asRecordPtr());
            break;
        case MODIFIED:
            if (s->isModified())
                res->push_back(s->asRecordPtr());
            break;
        case DELETED:
            if (s->isDeleted())
                res->push_back(s->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

SectorPtr Sectores::getSector(int IDSector)
{
    if (m_Sectores.find(IDSector) == m_Sectores.end())
        return SectorPtr();
    else
        return m_Sectores[IDSector];
}

void Sectores::defineHeaders(QStringList &list)
{
}

void Sectores::fillData(QTreeWidget &tree)
{
}

bool Sectores::addNew()
{
}

void Sectores::edit(QVariant ID)
{
}

void Sectores::deleteElement(QVariant ID)
{
}
