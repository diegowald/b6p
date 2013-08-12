#ifndef ACCESOS_H
#define ACCESOS_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "acollection.h"
#include "acceso.h"


class Accesos : public ACollection
{
    Q_OBJECT
private:
    enum ACCESS
    {
        CAN_READ,
        CAN_CREATE,
        CAN_UPDATE,
        CAN_DELETE
    };

public:
    explicit Accesos(QObject *parent = 0);

    bool canRead(int IDUser, QString &feature);
    bool canCreate(int IDUser, QString &feature);
    bool canUpdate(int IDUser, QString &feature);
    bool canDelete(int IDUser, QString &feature);
    bool canAccessApplication(int IDUser);

    virtual QString getSqlString();
    virtual void addRecord(RecordPtr record, bool setNew = true);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool exists(RecordPtr record);
    virtual bool isRecordUnsent(RecordPtr) { return false; }
    virtual RecordPtr getLocalRecord(RecordPtr) { return RecordPtr(); }
    virtual QStringList getFieldsToShowInMerge() { return QStringList(); }
    virtual bool printSelectedRecord(QVariant, QTextDocument &) { return false; }

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);
    virtual QString getTableName() { return "access"; }

    virtual QString getLocalDeleteStatement() { return ""; }
    virtual QString getLocalUpdateStatement() { return ""; }
    virtual QString getLocalInsertStatement() { return ""; }

    virtual QString getCentralDeleteStatement() { return ""; }
    virtual QString getCentralUpdateStatement() { return ""; }
    virtual QString getCentralInsertStatement() { return ""; }


    virtual QString getSQLExistsInMainDB() { return ""; }

    virtual RecordSet getRecords(RecordStatus, bool);
    virtual RecordSet getUnsent();
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual bool canBeDeleted(QVariant ID);

    virtual QString getSelectFromMainDB();

    virtual bool localRecordIsEqualsTo(RecordPtr record);

protected:
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *item);
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *item, QVariant ID);
    virtual bool deleteElement(QVariant ID);

private:
    bool get(int IDUser, QString &feature, ACCESS access);
    bool getBySector(int IDSector, QString &feature, ACCESS access);

    QMap<std::pair<int, QString>, AccesoPtr> m_AccessList;
};

typedef boost::shared_ptr<Accesos> AccesosPtr;
#endif // ACCESOS_H
