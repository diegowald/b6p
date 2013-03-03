#ifndef DATABASESYNCHRONIZATION_H
#define DATABASESYNCHRONIZATION_H

#include <QObject>
#include <boost/shared_ptr.hpp>

class DatabaseSynchronization;
typedef boost::shared_ptr<DatabaseSynchronization> DatabaseSynchronizationPtr;


class DatabaseSynchronization : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseSynchronization(QString Name, QObject *parent = 0);

    void getDataFromDB();
    void applyChanges();
    void checkConsistency();

    void sendData();
    
signals:
    void gettingDataFromCentralDB(QString &tableName);
    void applyingChanges(QString &tableName);
    void checkingChanges(QString &tableName);
    void sendingData(QString &tableName);

public slots:
    
private:
    QString name;
};

#endif // DATABASESYNCHRONIZATION_H
