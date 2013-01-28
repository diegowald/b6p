#include "acollection.h"

ACollection::ACollection(QString Name, QObject *parent) :
    QObject(parent), m_Name(Name)
{
}


void ACollection::load()
{
    emit loading(m_Name);
    loadData();
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
