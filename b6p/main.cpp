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

    /*if (appTranslator.load("b6p_esAR", a.applicationDirPath()))
    {
        a.installTranslator(&appTranslator);
    }
    else */if (appTranslator.load("b6p_" + QLocale::system().name(), a.applicationDirPath()))
    {
        a.installTranslator(&appTranslator);
    }

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
