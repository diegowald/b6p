#include "acollection.h"
#include <QDebug>

#include <QSqlRecord>
#include <QSqlField>

ACollection::ACollection(QString Name, QObject *parent) :
    QObject(parent), m_Name(Name), sqlEngine("./db.db")
{
}


void ACollection::load()
{
    emit loading(m_Name);

    QString sqlString = getSqlString();

    QSqlQuery query = sqlEngine.getAll(sqlString);
    while (query.next())
    {
        QSqlRecord rec = query.record();
        Record record;
        for (int i = 0; i < rec.count(); i++)
        {
            record[rec.fieldName(i)] = rec.field(i).value();
            addRecord(record);
        }
    }
    emit loaded(m_Name);
}

void ACollection::save()
{
    emit saving(m_Name);
    saveData();
    emit saved(m_Name);
}

QString ACollection::name() const
{
    return m_Name;
}
