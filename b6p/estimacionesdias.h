#ifndef ESTIMACIONESDIAS_H
#define ESTIMACIONESDIAS_H

#include "acollection.h"
#include <QMap>
#include "estimaciondia.h"

class EstimacionesDias : public ACollection
{
    Q_OBJECT
public:
    EstimacionesDias(QObject *parent = 0);
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
    virtual void refreshID(int newRecordId);
    virtual void saveDependants() {}

    EstimacionDiaLst getAll();
    EstimacionDiaPtr get(QDate dia);

private:
    QMap<QDate, EstimacionDiaPtr> m_Estimaciones;
};

typedef boost::shared_ptr<EstimacionesDias> EstimacionesDiasPtr;
#endif // ESTIMACIONESDIAS_H
