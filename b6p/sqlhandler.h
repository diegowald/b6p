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
#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include "IRecord.h"

class SQLHandler
{
public:
    SQLHandler(QString database);
    SQLHandler(QString Server, QString Database, QString User, QString Password);

    RecordSet getAll(QString &query);
    RecordSet getAll(QString &query, RecordPtr record);
    int executeQuery(QString &cmd, RecordPtr record, bool returnLastInsertedID);
    void executeCommand(QString &cmd);
    bool checkConnection();
protected:
    void addParameters(QSqlQuery &query, QString &SQL, RecordPtr record);
    bool tryReconnect();

private:
    QString m_database;
    QSqlDatabase db;
    QString m_Server;
    QString m_User;
    QString m_Password;
    bool m_UsingSQLITE;
};

#endif // SQLHANDLER_H
