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
#ifndef ESTIMACIONESDIAS_H
#define ESTIMACIONESDIAS_H

#include "acollection.h"
#include <QMap>
#include "estimaciondia.h"

class EstimacionesDias : public ACollection
{
    Q_OBJECT
public:
    EstimacionesDias(const QString &dbName, QObject *parent = 0);
    virtual QString getSqlString();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual QString getTableName() { return "planificaciondias"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();


    virtual QString getSelectFromMainDB();

    virtual void defineHeaders(QStringList &list);
    virtual QSharedPointer<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool isColumnEditable(QVariant ID, int column);
    virtual QSharedPointer<QList<QAction *> > getActions();

    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *item);
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *item, QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);

    EstimacionDiaLst getAll(bool includeDeleted);
    EstimacionDiaPtr get(QDate dia, bool includeDeleted);
    EstimacionDiaLst getUnplanned(bool includeDeleted);

public slots:
    void addManyDays();
    void approveSelected();

private:
    QMap<QDate, EstimacionDiaPtr> m_Estimaciones;
};

typedef QSharedPointer<EstimacionesDias> EstimacionesDiasPtr;
#endif // ESTIMACIONESDIAS_H
