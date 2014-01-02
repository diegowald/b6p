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
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "dlglogin.h"
#include "datastore.h"

// Logging
#include <QsLog.h>
#include <QsLogDest.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QsLogging::Logger & logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    const QString logPath(QDir(a.applicationDirPath()).filePath("b6p.log"));


    // Create log destinations
    QsLogging::DestinationPtr fileDestination(
       QsLogging::DestinationFactory::MakeFileDestination(logPath) );
    QsLogging::DestinationPtr debugDestination(
       QsLogging::DestinationFactory::MakeDebugOutputDestination() );

    // set log destinations on the logger
    logger.addDestination(debugDestination);
    logger.addDestination(fileDestination);

    QTranslator appTranslator;

    if (appTranslator.load("b6p_esAR", a.applicationDirPath()))
    {
        a.installTranslator(&appTranslator);
    }
    /*else if (appTranslator.load("b6p_" + QLocale::system().name(), a.applicationDirPath()))
    {
        a.installTranslator(&appTranslator);
    }*/

    QLOG_INFO() << "Program started";

    DlgLogin dlg;
    int IDUser = 0;
    bool canAccessApp = false;
    if (dlg.hasUsers())
    {
        if (dlg.exec() == QDialog::Accepted)
        {
            IDUser = dlg.getIDUser();
            canAccessApp = DataStore::instance()->getAccesos()->canAccessApplication(IDUser);
        }
    }
    else
        canAccessApp = true;

    if (canAccessApp)
    {
        MainWindow w(IDUser);
        w.show();
        QFont font = a.font();
        font.setPixelSize(12);
        a.setFont(font);
        int result = a.exec();
        QLOG_INFO() << "Program ended: result = " << result;
        return result;
    }
    else
    {
        QLOG_INFO() << "Program can't run";
        return -1;
    }
}
