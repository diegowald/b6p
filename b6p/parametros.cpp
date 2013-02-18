#include "parametros.h"
#include <QTime>


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
    m_Dictionary[record["Key"].toString()] = record["Value"].toString();
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

    foreach(QString key, m_Dictionary.keys())
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

QTime Parametros::getValue(QString key)
{
    QString v = getValue(key, "");
    QTime t(0, 0, 0, 0);
    t = t.addSecs(v.toInt());
    return t;
}

void Parametros::setValue(QString key, QTime value)
{
    int secs = value.hour() * 3600;
    secs += value.minute() * 60;
    secs += value.second();
    setValue(key, secs);
}

int Parametros::getValue(QString key, int defaultValue)
{
    QString v = getValue(key, "");
    if (v == "")
        return defaultValue;
    return v.toInt();
}

void Parametros::setValue(QString key, int value)
{
    setValue(key, QString::number(value));
}
