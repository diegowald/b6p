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
    virtual void addRecord(RecordPtr record);

    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual QString getSelectFromMainDB();

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


    SubSectorPtr getSubSector(int idSubSector);
    SubSectorPtr getSubSector(int idSector, QString SubSectorName);

    SubSectoresLst getAll(bool includeDeleted);
    SubSectoresLst getAll(int IDSector, bool includeDeleted);

signals:
    
public slots:
    
private:
    QMap<int, SubSectorPtr> m_SubSectores;
};

typedef boost::shared_ptr<SubSectores> SubSectoresPtr;
#endif // SUBSECTORES_H
