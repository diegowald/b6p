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

#ifndef ACCESOS_H
#define ACCESOS_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "acollection.h"
#include "acceso.h"


class Accesos : public ACollection
{
    Q_OBJECT
private:
    enum ACCESS
    {
        CAN_READ,
        CAN_CREATE,
        CAN_UPDATE,
        CAN_DELETE
    };

public:
    explicit Accesos(QObject *parent = 0);

    bool canRead(int IDUser, QString &feature);
    bool canCreate(int IDUser, QString &feature);
    bool canUpdate(int IDUser, QString &feature);
    bool canDelete(int IDUser, QString &feature);
    bool canAccessApplication(int IDUser);

    virtual QString getSqlString();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr) { return false; }
    virtual RecordPtr getLocalRecord(RecordPtr) { return RecordPtr(); }
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual QString getTableName() { return "access"; }

    virtual QString getLocalDeleteStatement() { return ""; }
    virtual QString getLocalUpdateStatement() { return ""; }
    virtual QString getLocalInsertStatement() { return ""; }

    virtual QString getCentralDeleteStatement() { return ""; }
    virtual QString getCentralUpdateStatement() { return ""; }
    virtual QString getCentralInsertStatement() { return ""; }


    virtual QString getSQLExistsInMainDB() { return ""; }

    virtual RecordSet getRecords(RecordStatus, bool);
    virtual RecordSet getUnsent();
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual bool canBeDeleted(QVariant ID);

    virtual QString getSelectFromMainDB();

    virtual bool localRecordIsEqualsTo(RecordPtr record);

protected:
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *item);
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *item, QVariant ID);
    virtual bool deleteElement(QVariant ID);

private:
    bool get(int IDUser, QString &feature, ACCESS access);
    bool getBySector(int IDSector, QString &feature, ACCESS access);

    QMap<std::pair<int, QString>, AccesoPtr> m_AccessList;
};

typedef boost::shared_ptr<Accesos> AccesosPtr;
#endif // ACCESOS_H
