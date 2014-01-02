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
#include "acollection.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QsLog.h>


ACollection::ACollection(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent) :
    QObject(parent),
    m_Name(Name),
    m_InvariableName(InvariableName),
    sqlEngine("./planning.b6p"),
    usesLastInsertedId(useLastInsertId),
    m_MergeStrategy(MergeStrategy)
{
    QLOG_TRACE_FN();
}


void ACollection::load()
{
    QLOG_TRACE_FN();
    emit loading(m_Name);

    QString sqlString = getSqlString();
    if (sqlString.size() > 0)
    {
        RecordSet resp = sqlEngine.getAll(sqlString);

        foreach (RecordPtr record, *resp)
        {
            addRecord(record);
        }
    }
    emit loaded(m_Name);
}

void ACollection::save()
{
    QLOG_TRACE_FN();
    emit saving(m_Name);

    deleteRecordsLocally();
    updateRecordsLocally();
    addNewRecordsLocally();
    saveDependants();
    setStatusToUnmodified(false, true, false);
    emit dataUpdated();
    emit saved(m_Name);
}

void ACollection::saveLocally()
{
    QLOG_TRACE_FN();
    emit saving(m_Name);

    deleteRecordsLocally();
    updateRecordsLocally();
    addNewRecordsLocally();
    saveDependants();
    setStatusToUnmodified(false, true, false);
    emit dataUpdated();
    emit saved(m_Name);
}

void ACollection::deleteRecordsLocally()
{
    QLOG_TRACE_FN();
    executeCommand(getLocalDeleteStatement(), DELETED, true);
}

void ACollection::updateRecordsLocally()
{
    QLOG_TRACE_FN();
    executeCommand(getLocalUpdateStatement(), MODIFIED, true);
}

void ACollection::addNewRecordsLocally()
{
    QLOG_TRACE_FN();
    executeCommand(getLocalInsertStatement(), NEW, true);
}

void ACollection::deleteRecordsCentralDB()
{
    QLOG_TRACE_FN();
    executeCommand(getCentralDeleteStatement(), DELETED, false);
}

void ACollection::updateRecordsCentralDB()
{
    QLOG_TRACE_FN();
    executeCommand(getCentralUpdateStatement(), MODIFIED, false);
}

void ACollection::addNewRecordsCentralDB()
{
    QLOG_TRACE_FN();
    executeCommand(getCentralInsertStatement(), NEW, false);
}


void ACollection::executeCommand(QString cmd, RecordStatus status, bool impactLocalDatabase)
{
    QLOG_TRACE_FN();
    if (cmd.size() > 0)
    {
        RecordSet set = getRecords(status, impactLocalDatabase);
        foreach(RecordPtr r, *set)
        {
            int newID = sqlEngine.executeQuery(cmd, r, usesLastInsertedId);
            if ((status == NEW) && usesLastInsertedId)
                refreshID((*r)[RECORD_ID].toInt(), newID);
        }
    }
}

bool ACollection::addNewRecord(QTreeWidgetItem *item)
{
    QLOG_TRACE_FN();
    bool result = addNew(item);
    if (result)
        save();
    return result;
}

bool ACollection::addNewRecord()
{
    QLOG_TRACE_FN();
    bool result = addNew();
    if (result)
        save();
    return result;
}

bool ACollection::addNewRecordWithAuxiliarydata(QVariant data)
{
    QLOG_TRACE_FN();
    bool result = addNewWithAdditionalData(data);
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QTreeWidgetItem *item, QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = edit(item, ID);
    if (result)
        save();
    return result;
}

bool ACollection::editRecord(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = edit(ID);
    if (result)
        save();
    return result;
}

bool ACollection::deleteRecord(QVariant ID)
{
    QLOG_TRACE_FN();
    bool result = false;
    if (canBeDeleted(ID))
    {
        QMessageBox msg;
        msg.setText(tr("Delete element"));
        msg.setInformativeText(tr("Do you want to remove it?"));
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg.setDefaultButton(QMessageBox::No);
        if (msg.exec() == QMessageBox::Yes)
        {
            result = deleteElement(ID);
            if (result)
                save();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText(tr("Delete element"));
        msg.setInformativeText(tr("Unable to delete element."));
        msg.setStandardButtons(QMessageBox::Ok);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.exec();
        result = false;
    }
    return result;
}

QString &ACollection::name()
{
    QLOG_TRACE_FN();
    return m_Name;
}

QString ACollection::invariableName() const
{
    QLOG_TRACE_FN();
    return m_InvariableName;
}

void ACollection::setLocalStatusToUnmodified()
{
    QLOG_TRACE_FN();
    QString sql = "UPDATE %1 set RecordStatus = %2;";
    sql = sql.arg(getTableName()).arg(UNMODIFIED);
    sqlEngine.executeCommand(sql);
    setStatusToUnmodified(false, false, true);
}

void ACollection::setInMemoryStatusToUnmodified()
{
    QLOG_TRACE_FN();
    setStatusToUnmodified(false, true, false);
}

void ACollection::exportTo(const QString &filename)
{
    QLOG_TRACE_FN();
    QString fileName = (filename.toLower().endsWith(".csv") ? filename: filename + ".csv");
    QFile file(fileName);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream st(&file);
        QStringList headers;
        defineHeaders(headers);
        QString r = "\"" + headers.join("\",\"") + "\"";
        st << r << endl;

        boost::shared_ptr<QList<QStringList> > records = getAll();

        foreach(QStringList record, *records)
        {
            QString r = "\"" + record.join("\",\"") + "\"";
            st << r << endl;
        }
        QMessageBox::information(NULL,
                                 tr("Export to CSV"),
                                 tr("Successfuly exported!"));
    }
    else
    {
        QMessageBox::information(NULL,
                                 tr("Export to CSV Error"),
                                 tr("Couldn't open file."));
    }
}

QString ACollection::asHTML()
{
    QLOG_TRACE_FN();
    QString html("<table width=\"100%\" border=1 cellspacing=0>\n");
    // Escribo el header
    QStringList headers;
    defineHeaders(headers);
    html += "<tr>";
    foreach(QString header, headers) {
        html += "<td bgcolor=\"lightgray\"><font size=\"+1\">";
        html += "<b><i>" + header + "</i></b></font>\n</td>";
    }
    html += "</tr>";

    boost::shared_ptr<QList<QStringList> > records = getAll();
    foreach(QStringList record, *records) {
        html += "<tr>";
        foreach(QString field, record) {
            html += "<td>" + field + "</td>";
        }
        html += "</tr>";
    }

    html += "\n</table>\n<br>\n";
    return html;
}

ACollection::MERGE_STRATEGY ACollection::mergeStrategy() const
{
    QLOG_TRACE_FN();
    return m_MergeStrategy;
}
