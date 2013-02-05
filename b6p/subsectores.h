#ifndef SUBSECTORES_H
#define SUBSECTORES_H

#include "acollection.h"
#include "subsector.h"
#include <QMap>

class SubSectores : public ACollection
{
    Q_OBJECT
public:
    explicit SubSectores(QObject *parent = 0);
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


    SubSectorPtr getSubSector(int idSubSector);
    SubSectorPtr getSubSector(int idSector, QString SubSectorName);

    SubSectoresLst getAll();
    SubSectoresLst getAll(int IDSector);

signals:
    
public slots:
    
private:
    QMap<int, SubSectorPtr> m_SubSectores;
};

typedef boost::shared_ptr<SubSectores> SubSectoresPtr;
#endif // SUBSECTORES_H
