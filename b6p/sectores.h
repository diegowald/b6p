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
    virtual void edit(QVariant ID);
    virtual void deleteElement(QVariant ID);

    SectorPtr getSector(int IDSector);

signals:
    
public slots:
    
private:
    QMap<int, SectorPtr> m_Sectores;
};

typedef boost::shared_ptr<Sectores> SectoresPtr;
#endif // SECTORES_H
