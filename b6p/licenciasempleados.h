#ifndef LICENCIASEMPLEADOS_H
#define LICENCIASEMPLEADOS_H

#include "acollection.h"
#include "licenciaempleado.h"

class LicenciasEmpleados : public ACollection
{
    Q_OBJECT
public:
    explicit LicenciasEmpleados(QObject *parent = 0);
    virtual ~LicenciasEmpleados();

    virtual QString getSqlString();
    virtual QString getSelectFromMainDB();

    virtual bool printSelectedRecord(QVariant IDElement, QTextDocument &textDoc);
    virtual void addRecord(RecordPtr record, bool setNew);
    virtual bool exists(RecordPtr record);
    virtual void updateRecord(RecordPtr record, bool isFromSincro);
    virtual void deleteRecord(RecordPtr record, bool isFromSincro);
    virtual bool isRecordUnsent(RecordPtr record);
    virtual RecordPtr getLocalRecord(RecordPtr record);
    virtual QStringList getFieldsToShowInMerge();

    virtual void defineHeaders(QStringList &list);
    virtual boost::shared_ptr<QList<QStringList> > getAll();
    virtual void fillData(QTreeWidget &tree);

    virtual QString getTableName();

    virtual QString getLocalDeleteStatement();
    virtual QString getLocalUpdateStatement();
    virtual QString getLocalInsertStatement();

    virtual QString getCentralDeleteStatement();
    virtual QString getCentralUpdateStatement();
    virtual QString getCentralInsertStatement();

    virtual QString getSQLExistsInMainDB();
    virtual RecordSet getRecords(RecordStatus status, bool fromMemory);
    virtual RecordSet getUnsent();

    virtual void refreshID(int oldID, int newRecordId);

    virtual void saveDependants();
    virtual void setStatusToUnmodified(bool removeDeleted, bool impactInMemmory, bool impactLocal);
    virtual bool canBeDeleted(QVariant ID);

    virtual bool localRecordIsEqualsTo(RecordPtr record);

    virtual LicenciaEmpleadoPtr getLicencia(int idLicencia, bool includeDeleted);
    virtual LicenciasEmpleadosLst getAllLicencias();
    virtual LicenciasEmpleadosLst getAllLicenciasEmpleado(int idEmpleado);
    virtual LicenciaEmpleadoPtr getLicenciaEmpleado(int idEmpleado, QDate& date);
    virtual bool isOnLicence(int idEmpleado, QDate& date);
    virtual QStringList getDistinctLicenceType();
protected:
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *item);
    virtual bool addNewWithAdditionalData(QVariant);
    virtual bool edit(QVariant ID);
    virtual bool editWithIDEmpleado(int ID, int idEmpleado);
    virtual bool edit(QTreeWidgetItem *item, QVariant ID);
    virtual bool deleteElement(QVariant ID);

signals:

public slots:

private:
    QMap<int, LicenciaEmpleadoPtr> m_Licencias;

};

typedef boost::shared_ptr<LicenciasEmpleados> LicenciasEmpleadosPtr;

#endif // LICENCIASEMPLEADOS_H
