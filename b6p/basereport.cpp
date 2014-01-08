#include "basereport.h"
#include "QsLog.h"

BaseReport::BaseReport(QString Name, QString InvariableName, bool useLastInsertId, MERGE_STRATEGY MergeStrategy, QObject *parent) :
    ACollection(Name, InvariableName, useLastInsertId, MergeStrategy, parent)
{
    QLOG_TRACE_FN();
}

BaseReport::~BaseReport()
{
    QLOG_TRACE_FN();
}


QString BaseReport::getSqlString()
{
    QLOG_TRACE_FN();
    return "";
}

void BaseReport::addRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

void BaseReport::updateRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

void BaseReport::deleteRecord(RecordPtr, bool)
{
    QLOG_TRACE_FN();
}

bool BaseReport::exists(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::localRecordIsEqualsTo(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::isRecordUnsent(RecordPtr)
{
    QLOG_TRACE_FN();
    return false;
}

RecordPtr BaseReport::getLocalRecord(RecordPtr)
{
    QLOG_TRACE_FN();
    return RecordPtr();
}

QStringList BaseReport::getFieldsToShowInMerge()
{
    QLOG_TRACE_FN();
    return QStringList();
}

bool BaseReport::printSelectedRecord(QVariant IDElement, QTextDocument &textDoc)
{
    QLOG_TRACE_FN();
    return false;
}


bool BaseReport::addNew()
{
    QLOG_TRACE_FN();
}

bool BaseReport::addNew(QTreeWidgetItem *)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::addNewWithAdditionalData(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::edit(QVariant ID)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::edit(QTreeWidgetItem *, QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

bool BaseReport::deleteElement(QVariant)
{
    QLOG_TRACE_FN();
    return false;
}

void BaseReport::refreshID(int, int)
{
    QLOG_TRACE_FN();
}

void BaseReport::saveDependants()
{
    QLOG_TRACE_FN();
}

void BaseReport::setStatusToUnmodified(bool, bool, bool)
{
    QLOG_TRACE_FN();
}

bool BaseReport::canBeDeleted(QVariant ID)
{
    QLOG_TRACE_FN();
}

QString BaseReport::getTableName()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalDeleteStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalUpdateStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getLocalInsertStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralDeleteStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralUpdateStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getCentralInsertStatement()
{
    QLOG_TRACE_FN();
    return "";
}

QString BaseReport::getSQLExistsInMainDB()
{
    QLOG_TRACE_FN();
    return "";
}

RecordSet BaseReport::getRecords(RecordStatus, bool)
{
    QLOG_TRACE_FN();
    return RecordSet();
}

RecordSet BaseReport::getUnsent()
{
    QLOG_TRACE_FN();
    return RecordSet();
}

QString BaseReport::getSelectFromMainDB()
{
    QLOG_TRACE_FN();
    return "";
}

boost::shared_ptr<QList<QAction*> > BaseReport::getActions()
{
    QLOG_TRACE_FN();
    boost::shared_ptr<QList<QAction*> >actions = boost::make_shared<QList<QAction*> >();

    QAction* action = new QAction(tr("Filter..."), NULL);

    QIcon icon;
    icon.addFile(QString::fromUtf8(":/img/magnet"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon);
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
    connect(action, SIGNAL(triggered()), this, SLOT(filter()));
    actions->push_back(action);

/*    action = new QAction(tr("Approve"), NULL);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/img/approve"), QSize(), QIcon::Normal, QIcon::Off);
    action->setIcon(icon2);
    connect(action, SIGNAL(triggered()), this, SLOT(approveSelected()));
    actions->push_back(action);*/

    return actions;
}


void BaseReport::filter()
{
    QLOG_TRACE_FN();
    Q_ASSERT(1 == 0);
}
