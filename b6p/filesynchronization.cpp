#include "filesynchronization.h"
#include <QsLog.h>
#include <QDir>
#include <QMessageBox>
#include "datastore.h"
#include <QFile>

FileSynchronization::FileSynchronization(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE_FN();
}

void FileSynchronization::doSynchro()
{
    QLOG_TRACE_FN();
    if (DataStore::instance()->getParametros()->getValue(Parametros::USE_FILE_SYNCHRO, 1) == 1)
    {
        QDir dir(DataStore::instance()->getParametros()->getValue(Parametros::SYNCHRO_FOLDER, ""));
        if (!dir.exists())
        {
            QLOG_ERROR() << dir.dirName() << " no existe.";
            QMessageBox::warning(NULL, tr("File synchronization"), tr("Synchronization folder doesn't exist."));
            return;
        }

        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QFileInfoList list = dir.entryInfoList();

        QString myDatabase = DataStore::instance()->getParametros()->getLocalDatabaseName();
        foreach (QFileInfo file, list)
        {
            if (file.fileName() != myDatabase)
            {
                getFile(file);
            }
        }

        putFile(myDatabase);

        DataStore::instance()->refreshData();
        QMessageBox::information(NULL, tr("File synchronization"), tr("Synchronization OK!"));
    }
}

void FileSynchronization::getFile(QFileInfo& file)
{
    QLOG_TRACE_FN();
    QFile::copy(file.absoluteFilePath(), "./" + file.fileName());
}

void FileSynchronization::putFile(QString &file)
{
    QLOG_TRACE_FN();
    QFile::copy("./" + file, DataStore::instance()->getParametros()->getValue(Parametros::SYNCHRO_FOLDER, "") + file);
}
