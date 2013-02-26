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
    virtual void addRecord(Record &record);
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual void defineHeaders(QStringList &list);
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

    SectorLst getAll(bool includeDeleted);

signals:
    
public slots:
    
private:
    QMap<int, SectorPtr> m_Sectores;
};

typedef boost::shared_ptr<Sectores> SectoresPtr;
#endif // SECTORES_H
