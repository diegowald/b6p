#ifndef DATABASESYNCHRONIZATION_H
#define DATABASESYNCHRONIZATION_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "acollection.h"

class DatabaseSynchronization;
typedef boost::shared_ptr<DatabaseSynchronization> DatabaseSynchronizationPtr;


class DatabaseSynchronization : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseSynchronization(boost::shared_ptr<ACollection> data, boost::shared_ptr<SQLHandler> sqlHandler, QObject *parent = 0);

    void getDataFromDB(QString dateFrom);
    void applyChanges();
    void checkConsistency();

    void sendData();

    QString name();
    
protected:
    bool existsInMainDB(RecordPtr rec);
    void addRecord(RecordPtr rec);
    void updateRecord(RecordPtr rec);
    void deleteRecord(RecordPtr rec);

signals:
    void gettingDataFromCentralDB(QString &tableName);
    void applyingChanges(QString &tableName);
    void checkingChanges(QString &tableName);
    void sendingData(QString &tableName);

public slots:
    
private:
    boost::shared_ptr<ACollection> m_Data;
    boost::shared_ptr<SQLHandler> m_SQLHandler;
    RecordSet m_QueryResult;
};

#endif // DATABASESYNCHRONIZATION_H
