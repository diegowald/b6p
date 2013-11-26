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
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool localRecordIsEqualsTo(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual QString getTableName() { return "subsectores"; }

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false;}
    virtual bool addNewWithAdditionalData(QVariant) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) { return false;}
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);


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
