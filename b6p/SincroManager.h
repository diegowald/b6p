#ifndef SINCROMANAGER_H
#define SINCROMANAGER_H

#include <QObject>
#include "databasesynchronization.h"
#include <boost/shared_ptr.hpp>
#include "sqlhandler.h"


class SincroManager : public QObject
{
    Q_OBJECT
public:
    explicit SincroManager(QObject *parent = 0);

    void runSincro();
    QStringList getSincroTableNames();
protected:
    void obtenerFechaUltimaSincronizacion();
    void obtenerActualizacionesDeBaseCentral();
    void obtenerFechaDesdeServerCentral();

    void enviarDatosADBCentral();

    void grabarFechaUltimaSincronizacion();

    void establishConnections();
    void establishConnections(DatabaseSynchronizationPtr db);
    bool conexionADBOK();

signals:
    void startingSynchro();
    void getDataFromCentralDB(QString &tableName);
    void applyingChanges(QString &tableName);
    void checkingChanges(QString &tableName);
    void sendingData(QString &tableName);
    void SynchroEnded();
public slots:
    

private:
    QString m_FechaUltimaSincronizacion;
    QList<DatabaseSynchronizationPtr> m_Synchronizationtables;
    boost::shared_ptr<SQLHandler> m_SQL;
    QString m_FechaSincro;
};

#endif // QMYSQL_H
