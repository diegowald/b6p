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
#ifndef PARAMETROS_H
#define PARAMETROS_H
#include "acollection.h"
#include <QMap>

class Parametros : public ACollection
{
    Q_OBJECT
public:
    explicit Parametros(QObject *parent = 0);

    virtual QString getSqlString();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr) { return false; }
    virtual RecordPtr getLocalRecord(RecordPtr) { return RecordPtr(); }
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }


    virtual QString getTableName() { return "parametros"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();

    virtual bool canBeDeleted(QVariant) { return false; }

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool, bool, bool) {}

    virtual QString getSelectFromMainDB();

    QString getValue(QString key, QString defaultValue);
    void setValue(QString key, QString value);

    int getValue(QString key, int defaultValue);
    void setValue(QString key, int value);

    QsLogging::Level getLoggingLevel();
    QString getLocalMachine() const;

private:

    QString getDatabaseName(const QString& machineName);
public:
    QString getLocalDatabaseName();
    QString getDatabaseNamePath(const QString& machineName);


    QString getFrancoType();

    static const QString OPEN_STORE;
    static const QString CLOSE_STORE;
    static const QString MIN_WORKING_HOURS;
    static const QString EMPLOYEE_MIN_HOURS;
    static const QString EMPLOYEE_MAX_HOURS;
    static const QString MAX_DAYS_BETWEEN_FREE_DAY;

    static const QString LAST_SYNCHRO;
    static const QString SERVER_NAME;
    static const QString DATABASE_NAME;
    static const QString USER_NAME;
    static const QString PASSWORD;
    static const QString LOG_LEVEL;
    static const QString FRANCO_TYPE;

    static const QString SYNCHRO_FOLDER;
    static const QString USE_FILE_SYNCHRO;

signals:
    
public slots:
private:
    QMap<QString, QString> m_Dictionary;
    bool m_recordsWereCreated;
};

typedef boost::shared_ptr<Parametros> ParametrosPtr;
#endif // PARAMETROS_H
