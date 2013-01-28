#include "parametros.h"

Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"), parent)
{
}

void Parametros::loadData()
{
}

void Parametros::saveData()
{
}

void Parametros::defineHeaders(QStringList &)
{
}

void Parametros::fillData(QTreeWidget &)
{
}

bool Parametros::addNew()
{
}

void Parametros::edit(QVariant)
{
}

void Parametros::deleteElement(QVariant)
{
}

QString Parametros::getValue(QString key, QString defaultValue)
{
    if (m_Dictionary.find(key) == m_Dictionary.end())
        return defaultValue;
    else
        return m_Dictionary[key];
}
