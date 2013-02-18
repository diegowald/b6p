#include "parametros.h"

const QString Parametros::OPEN_STORE("openStore");
const QString Parametros::CLOSE_STORE("closeStore");
const QString Parametros::MIN_WORKING_HOURS("MinWorkingHours");
const QString Parametros::EMPLOYEE_MIN_HOURS("Employee_minHours");
const QString Parametros::EMPLOYEE_MAX_HOURS("Employee_maxHours");
const QString Parametros::MAX_DAYS_BETWEEN_FREE_DAY("MaxDaysBetweenFreeDay");



Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"), false, parent)
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

QString Parametros::getDeleteStatement()
{
    return "delete from parametros where Key = :Key;";
}

QString Parametros::getUpdateStatement()
{
    return "update parametros set Value = :Value where Key = :Key;";
}

QString Parametros::getInsertStatement()
{
    return "insert into parametros (Key, Value) values (:Key, :Value);";
}

RecordSet Parametros::getRecords(RecordStatus status)
{
    RecordSet rs(new QList<RecordPtr>());
    if ((status == NEW) || (status == DELETED))
        return rs;

    foreach(QString key, m_Dictionary)
    {
        RecordPtr r(new Record());
        (*r)["Key"] = key;
        (*r)["Value"] = m_Dictionary[key];
        rs->push_back(r);
    }
    return rs;
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

bool Parametros::edit(QVariant)
{
}

bool Parametros::deleteElement(QVariant)
{
}

QString Parametros::getValue(QString key, QString defaultValue)
{
    if (m_Dictionary.find(key) == m_Dictionary.end())
        return defaultValue;
    else
        return m_Dictionary[key];
}

void Parametros::setValue(QString key, QString value)
{
    m_Dictionary[key] = value;
}
