#ifndef QMYSQL_H
#define QMYSQL_H

#include <QObject>
#include "databasesynchronization.h"
#include <boost/shared_ptr.hpp>

class QMysql : public QObject
{
    Q_OBJECT
public:
    explicit QMysql(QObject *parent = 0);

    void runSincro();
protected:
    void obtenerFechaUltimaSincronizacion();
    void obtenerActualizacionesDeBaseCentral();

    void enviarDatosADBCentral();

    void grabarFechaUltimaSincronizacion();

    void establishConnections(DatabaseSynchronizationPtr db);

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
};

#endif // QMYSQL_H
