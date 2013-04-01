#ifndef SECTORES_H
#define SECTORES_H

#include "acollection.h"
#include "sector.h"
#include <QMap>

class Sectores : public ACollection
{
    Q_OBJECT
public:
    explicit Sectores(QObject *parent = 0);
    virtual QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);

    virtual QString getTableName() { return "sectores"; }
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement(bool IncludeIDs);
    virtual RecordSet getRecords(RecordStatus status);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted);

    SectorPtr getSector(int IDSector);
    SectorPtr getSector(QString SectorName);

    SectorLst getAll(bool includeShowInPlanification, bool includeDeleted);

signals:
    
public slots:
    
private:
    QMap<int, SectorPtr> m_Sectores;
};

typedef boost::shared_ptr<Sectores> SectoresPtr;
#endif // SECTORES_H
