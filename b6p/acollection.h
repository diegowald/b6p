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
#ifndef ACOLLECTION_H
#define ACOLLECTION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QTreeWidget>
#include "sqlhandler.h"
#include "IRecord.h"
#include <QAction>
#include <QList>
#include <QTextDocument>
#include <QsLogLevel.h>

class ACollection : public QObject
{
    Q_OBJECT
public:

    enum MERGE_STRATEGY
    {
        MERGE_KEEP_MAIN,
        MERGE_KEEP_LOCAL,
        MERGE_MANUAL
    };

    explicit ACollection(const QString& Name, const QString &InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, const QString &dbName, QObject *parent = 0);
    
    virtual void exportTo(const QString &filename);
    virtual void load();
    virtual void save();
    virtual void saveLocally();
    virtual QString asHTML();
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc) = 0;

    QString &name();
    QString invariableName() const;

    virtual QString suggestedFileName() { return name(); }
    virtual QString getSqlString() = 0;
    virtual void addRecord(RecordPtr record, bool setNew = false) = 0;

    virtual bool exists(RecordPtr record) = 0;
    virtual void updateRecord(RecordPtr record, bool isFromSincro) = 0;
    virtual void deleteRecord(RecordPtr record, bool isFromSincro) = 0;
    virtual bool isRecordUnsent(RecordPtr record) = 0;
    virtual RecordPtr getLocalRecord(RecordPtr record) = 0;
    virtual QStringList getFieldsToShowInMerge() = 0;
    virtual ACollection::MERGE_STRATEGY mergeStrategy() const;

    virtual void defineHeaders(QStringList &list) = 0;
    virtual boost::shared_ptr<QList<QStringList> > getAll() = 0;
    virtual void fillData(QTreeWidget &tree) = 0;
    virtual bool isColumnEditable(QVariant, int) { return false; }
    virtual boost::shared_ptr<QList<QAction*> > getActions() { return boost::make_shared<QList<QAction*> >(); }
    bool addNewRecord();
    bool addNewRecordWithAuxiliarydata(QVariant data);
    bool addNewRecord(QTreeWidgetItem *item);
    bool editRecord(QVariant ID);
    bool editRecord(QTreeWidgetItem *item, QVariant ID);
    bool deleteRecord(QVariant ID);
    void setLocalStatusToUnmodified();
    void setInMemoryStatusToUnmodified();

    virtual QString getTableName() = 0;

    virtual QString getLocalDeleteStatement() = 0;
    virtual QString getLocalUpdateStatement() = 0;
    virtual QString getLocalInsertStatement() = 0;

    virtual QString getCentralDeleteStatement() = 0;
    virtual QString getCentralUpdateStatement() = 0;
    virtual QString getCentralInsertStatement() = 0;


    virtual QString getSQLExistsInMainDB() = 0;
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory) = 0;
    virtual RecordSet getUnsent() = 0;

    virtual void refreshID(int oldID, int newRecordId) = 0;
    virtual void saveDependants() = 0;
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal) = 0;
    virtual bool canBeDeleted(QVariant ID) = 0;

    virtual QString getSelectFromMainDB() = 0;

    virtual bool localRecordIsEqualsTo(RecordPtr record) = 0;

    virtual bool isReadOnly();

protected:
    virtual bool addNew() = 0;
    virtual bool addNewWithAdditionalData(QVariant data) = 0;
    virtual bool addNew(QTreeWidgetItem *item) = 0;
    virtual bool edit(QVariant ID) = 0;
    virtual bool edit(QTreeWidgetItem *item, QVariant ID) = 0;
    virtual bool deleteElement(QVariant ID) = 0;

signals:
    void loaded(QString name);
    void loading(QString name);
    void saved(QString name);
    void saving(QString name);
    void dataUpdated();

public slots:

protected:
    virtual void deleteRecordsLocally();
    virtual void updateRecordsLocally();
    virtual void addNewRecordsLocally();

    virtual void deleteRecordsCentralDB();
    virtual void updateRecordsCentralDB();
    virtual void addNewRecordsCentralDB();

    virtual void executeCommand(QString cmd, RecordStatus status, bool impactLocalDatabase);
private:
    QString m_Name;
    QString m_InvariableName;
    SQLHandler sqlEngine;
    bool usesLastInsertedId;
    MERGE_STRATEGY m_MergeStrategy;
    QString m_dbName;
};

#endif // ACOLLECTION_H
