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
    virtual void addRecord(RecordPtr record);

    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);

    virtual bool canBeDeleted(QVariant) { return false; }

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool) {}

    virtual QString getSelectFromMainDB();

    QString getValue(QString key, QString defaultValue);
    void setValue(QString key, QString value);

    int getValue(QString key, int defaultValue);
    void setValue(QString key, int value);


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

signals:
    
public slots:
private:
    QMap<QString, QString> m_Dictionary;
    bool m_recordsWereCreated;
};

typedef boost::shared_ptr<Parametros> ParametrosPtr;
#endif // PARAMETROS_H
