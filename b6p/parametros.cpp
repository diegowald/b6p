/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
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
const QString Parametros::FRANCO_TYPE("RestType");

Parametros::Parametros(QObject *parent) :
    ACollection(tr("Parameters"),
                "Parameters", false, ACollection::MERGE_KEEP_LOCAL, parent)
{
    QLOG_TRACE_FN();
    m_recordsWereCreated = false;
}

QString Parametros::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return "";
}

QString Parametros::getSqlString()
{
    QLOG_TRACE_FN();
    return "select Key, Value from parametros;";
}

void Parametros::addRecord(RecordPtr record, bool)
{
    QLOG_TRACE_FN();
    m_recordsWereCreated = true;
    m_Dictionary[(*record)["Key"].toString()] = (*record)["Value"].toString();
}

void Parametros::updateRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

void Parametros::deleteRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

bool Parametros::exists(RecordPtr)
{
    QLOG_TRACE_FN();
    return true;
}

bool Parametros::localRecordIsEqualsTo(RecordPtr)
{
    QLOG_TRACE_FN();
    return true;
}


QString Parametros::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from parametros where Key = :Key;";
}

QString Parametros::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update parametros set Value = :Value where Key = :Key;";
}

QString Parametros::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return "insert into parametros (Key, Value) values (:Key, :Value);";
}

QString Parametros::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return "delete from parametros where Key = :Key;";
}

QString Parametros::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return "update parametros set Value = :Value where Key = :Key;";
}

QString Parametros::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return "insert into parametros (Key, Value) values (:Key, :Value);";
}


QString Parametros::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return "select Key, Value from Parametros where Key = :Key;";
}

RecordSet Parametros::getRecords(RecordStatus status, bool)
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    return boost::make_shared<QList<RecordPtr> >();
}

void Parametros::defineHeaders(QStringList &)
{
    QLOG_TRACE_FN();
}

boost::shared_ptr<QList<QStringList> > Parametros::getAll()
{
    QLOG_TRACE_FN();
    return boost::make_shared<QList<QStringList> >();
}

void Parametros::fillData(QTreeWidget &)
{
    QLOG_TRACE_FN();
}

bool Parametros::addNew()
{
    QLOG_TRACE_FN();
    return false;
}

bool Parametros::edit(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool Parametros::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

QString Parametros::getValue(QString key, QString defaultValue)
{
    QLOG_TRACE_FN();
    if (m_Dictionary.find(key) == m_Dictionary.end())
        return defaultValue;
    else
        return m_Dictionary[key];
}

void Parametros::setValue(QString key, QString value)
{
    QLOG_TRACE_FN();
    m_Dictionary[key] = value;
}

int Parametros::getValue(QString key, int defaultValue)
{
    QLOG_TRACE_FN();
    QString v = getValue(key, "");
    if (v == "")
        return defaultValue;
    return v.toInt();
}

void Parametros::setValue(QString key, int value)
{
    QLOG_TRACE_FN();
    setValue(key, QString::number(value));
}

QsLogging::Level Parametros::getLoggingLevel()
{
    QLOG_TRACE_FN();
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
    QLOG_TRACE_FN();
    QHostInfo hostInfo;
    hostInfo = QHostInfo::fromName(QHostInfo::localHostName());
    return hostInfo.hostName();
}

QString Parametros::getFrancoType()
{
    QLOG_TRACE_FN();
    QString type = getValue(FRANCO_TYPE, "Franco");
    return type;
}
