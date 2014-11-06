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
#ifndef PLANIFICACIONESDIAS_H
#define PLANIFICACIONESDIAS_H

#include "acollection.h"
#include "planificaciondia.h"

class PlanificacionesDias : public ACollection
{
    Q_OBJECT
public:
    explicit PlanificacionesDias(const QString &dbName, QObject *parent = 0);
    virtual QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc);

    virtual QString getTableName() { return "planificaciondia"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();


    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list);
    virtual QSharedPointer<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int oldID, int newRecordId);
    virtual void saveDependants();
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual QSharedPointer<QList<QAction*> > getActions();

    PlanificacionDiaLst getAll(bool includeDeleted);
    PlanificacionDiaPtr getByDay(QDate day, bool includeDeleted);
    PlanificacionDiaLst getAllReadyForApproval();
signals:
    
public slots:
    
private:
    QMap<QDate, PlanificacionDiaPtr> m_Planificaciones;
};

typedef QSharedPointer<PlanificacionesDias> PlanificacionesDiasPtr;
#endif // PLANIFICACIONESDIAS_H
