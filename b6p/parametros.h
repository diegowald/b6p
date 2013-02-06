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
    virtual void addRecord(Record &record);

    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);

    virtual void defineHeaders(QStringList &list);
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool edit(QVariant ID);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int) {}
    virtual void saveDependants() {}
    QString getValue(QString key, QString defaultValue);

signals:
    
public slots:
private:
    QMap<QString, QString> m_Dictionary;
};

typedef boost::shared_ptr<Parametros> ParametrosPtr;
#endif // PARAMETROS_H
