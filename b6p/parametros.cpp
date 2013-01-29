#include "parametros.h"

Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"), parent)
{
}

QString Parametros::getSqlString()
{
    return "select Key, Value from parametros;";
}

void Parametros::addRecord(Record &record)
{
    m_Dictionary["Key"] = record["Key"].toString();
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
