#include "parametros.h"

#include <QsLog.h>
#include <QtNetwork/QHostInfo>

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

const QString Parametros::LOG_LEVEL("LOG_LEVEL");

Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"),
                "Parameters", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE() << "Parametros::Parametros(QObject *parent)";
    m_recordsWereCreated = false;
}

QString Parametros::getSelectFromMainDB()
{
    QLOG_TRACE() << "QString Parametros::getSelectFromMainDB()";
    return "";
}

QString Parametros::getSqlString()
{
    QLOG_TRACE() << "QString Parametros::getSqlString()";
    return "select Key, Value from parametros;";
}

void Parametros::addRecord(RecordPtr record, bool)
{
    QLOG_TRACE() << "void Parametros::addRecord(RecordPtr record, bool)";
    m_recordsWereCreated = true;
    m_Dictionary[(*record)["Key"].toString()] = (*record)["Value"].toString();
}

void Parametros::updateRecord(RecordPtr, bool)
{
    QLOG_TRACE() << "void Parametros::updateRecord(RecordPtr, bool)";
}

void Parametros::deleteRecord(RecordPtr, bool)
{
    QLOG_TRACE() << "void Parametros::deleteRecord(RecordPtr, bool)";
}

bool Parametros::exists(RecordPtr)
{
    QLOG_TRACE() << "bool Parametros::exists(RecordPtr)";
    return true;
}

bool Parametros::localRecordIsEqualsTo(RecordPtr)
{
    QLOG_INFO() << "virtual bool Parametros::localRecordIsEqualsTo(RecordPtr record)";
    return true;
}


QString Parametros::getLocalDeleteStatement()
{
    QLOG_TRACE() << "QString Parametros::getLocalDeleteStatement()";
    return "delete from parametros where Key = :Key;";
}

QString Parametros::getLocalUpdateStatement()
{
    QLOG_TRACE() << "QString Parametros::getLocalUpdateStatement()";
    return "update parametros set Value = :Value where Key = :Key;";
}

QString Parametros::getLocalInsertStatement()
{
    QLOG_TRACE() << "QString Parametros::getLocalInsertStatement()";
    return "insert into parametros (Key, Value) values (:Key, :Value);";
}

QString Parametros::getCentralDeleteStatement()
{
    QLOG_TRACE() << "QString Parametros::getCentralDeleteStatement()";
    return "delete from parametros where Key = :Key;";
}

QString Parametros::getCentralUpdateStatement()
{
    QLOG_TRACE() << "QString Parametros::getCentralUpdateStatement()";
    return "update parametros set Value = :Value where Key = :Key;";
}

QString Parametros::getCentralInsertStatement()
{
    QLOG_TRACE() << "QString Parametros::getCentralInsertStatement()";
    return "insert into parametros (Key, Value) values (:Key, :Value);";
}


QString Parametros::getSQLExistsInMainDB()
{
    QLOG_TRACE() << "QString Parametros::getSQLExistsInMainDB()";
    return "select Key, Value from Parametros where Key = :Key;";
}

RecordSet Parametros::getRecords(RecordStatus status, bool fromMemory)
{
    QLOG_TRACE() << "RecordSet Parametros::getRecords(RecordStatus status)";
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
    QLOG_TRACE() << "RecordSet Parametros::getUnsent()";
    return boost::make_shared<QList<RecordPtr> >();
}

void Parametros::defineHeaders(QStringList &)
{
    QLOG_TRACE() << "void Parametros::defineHeaders(QStringList &)";
}

boost::shared_ptr<QList<QStringList> > Parametros::getAll()
{
    QLOG_TRACE() << "boost::shared_ptr<QList<QStringList> > Parametros::getAll()";
    return boost::make_shared<QList<QStringList> >();
}

void Parametros::fillData(QTreeWidget &)
{
    QLOG_TRACE() << "void Parametros::fillData(QTreeWidget &)";
}

bool Parametros::addNew()
{
    QLOG_TRACE() << "bool Parametros::addNew()";
    return false;
}

bool Parametros::edit(QVariant)
{
    QLOG_TRACE() << "bool Parametros::edit(QVariant)";
    return false;
}

bool Parametros::deleteElement(QVariant)
{
    QLOG_TRACE() << "bool Parametros::deleteElement(QVariant)";
    return false;
}

QString Parametros::getValue(QString key, QString defaultValue)
{
    QLOG_TRACE() << "QString Parametros::getValue(QString key, QString defaultValue)";
    if (m_Dictionary.find(key) == m_Dictionary.end())
        return defaultValue;
    else
        return m_Dictionary[key];
}

void Parametros::setValue(QString key, QString value)
{
    QLOG_TRACE() << "void Parametros::setValue(QString key, QString value)";
    m_Dictionary[key] = value;
}

int Parametros::getValue(QString key, int defaultValue)
{
    QLOG_TRACE() << "int Parametros::getValue(QString key, int defaultValue)";
    QString v = getValue(key, "");
    if (v == "")
        return defaultValue;
    return v.toInt();
}

void Parametros::setValue(QString key, int value)
{
    QLOG_TRACE() << "void Parametros::setValue(QString key, int value)";
    setValue(key, QString::number(value));
}

QsLogging::Level Parametros::getLoggingLevel()
{
    QLOG_TRACE() << "QsLogging::Level Parametros::getLoggingLever()";
    QString v = getValue(LOG_LEVEL, "0");

    if (v == "")
        return QsLogging::TraceLevel;

    int logLevel = v.toInt();
    if ((logLevel < 0) || (logLevel > 6))
        logLevel = 6;

    return (QsLogging::Level)logLevel;
}

QString Parametros::getLocalMachine() const
{
    QLOG_TRACE() << "QString Parametros::getLocalMachine() const";
    QHostInfo hostInfo;
    hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    return hostInfo.hostName();
}
