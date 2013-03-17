#include "parametros.h"



const QString Parametros::OPEN_STORE("openStore");
const QString Parametros::CLOSE_STORE("closeStore");
const QString Parametros::MIN_WORKING_HOURS("MinWorkingHours");
const QString Parametros::EMPLOYEE_MIN_HOURS("Employee_minHours");
const QString Parametros::EMPLOYEE_MAX_HOURS("Employee_maxHours");
const QString Parametros::MAX_DAYS_BETWEEN_FREE_DAY("MaxDaysBetweenFreeDay");

const QString Parametros::LAST_SYNCHRO("LastSynchronization");
const QString Parametros::SERVER_NAME("Server Name");
const QString Parametros::DATABASE_NAME("Database Name");
const QString Parametros::USER_NAME("User Name");
const QString Parametros::PASSWORD("Password");

Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"),
                "Parameters", false, parent)
{
    m_recordsWereCreated = false;
}

QString Parametros::getSelectFromMainDB()
{
    return "";
}

QString Parametros::getSqlString()
{
    return "select Key, Value from parametros;";
}

void Parametros::addRecord(RecordPtr record)
{
    m_recordsWereCreated = true;
    m_Dictionary[(*record)["Key"].toString()] = (*record)["Value"].toString();
}

void Parametros::updateRecord(RecordPtr record)
{
}

void Parametros::deleteRecord(RecordPtr record)
{
}

bool Parametros::exists(RecordPtr record)
{
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

QString Parametros::getSQLExistsInMainDB()
{
    return "select Key, Value from Parametros where Key = :Key;";
}

RecordSet Parametros::getRecords(RecordStatus status)
{
    RecordSet rs = boost::make_shared<QList<RecordPtr> >();
    if (status == DELETED)
        return rs;

    if ((status == NEW) && m_recordsWereCreated)
        return rs;

    if ((status == MODIFIED) && !m_recordsWereCreated)
        return rs;

    foreach(QString key, m_Dictionary.keys())
    {
        RecordPtr r = boost::make_shared<Record>();
        (*r)["Key"] = key;
        (*r)["Value"] = m_Dictionary[key];
        rs->push_back(r);
    }
    m_recordsWereCreated = true;
    return rs;
}

RecordSet Parametros::getUnsent()
{
    return boost::make_shared<QList<RecordPtr> >();
}

void Parametros::defineHeaders(QStringList &)
{
}

void Parametros::fillData(QTreeWidget &)
{
}

bool Parametros::addNew()
{
    return false;
}

bool Parametros::edit(QVariant)
{
    return false;
}

bool Parametros::deleteElement(QVariant)
{
    return false;
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
