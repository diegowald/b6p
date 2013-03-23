#ifndef CALENDARIOPERSONAS_H
#define CALENDARIOPERSONAS_H

#include <QObject>
#include "acollection.h"
#include "calendariopersona.h"

class CalendarioPersonas : public ACollection
{
    Q_OBJECT
public:
    explicit CalendarioPersonas(QObject *parent = 0);
    virtual ~CalendarioPersonas();
    virtual QString getSqlString();
    virtual QString getSQLExistsInMainDB();
    virtual void addRecord(RecordPtr record);
    virtual void updateRecord(RecordPtr record);
    virtual void deleteRecord(RecordPtr record);
    virtual bool exists(RecordPtr record);

    virtual QString getTableName() { return "calendariopersonas"; }
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual RecordSet getUnsent();
    virtual QString getSelectFromMainDB();
    virtual void defineHeaders(QStringList &list) ;
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool addNew(QTreeWidgetItem *) { return false; }
    virtual bool edit(QVariant ID);
    virtual bool edit(QTreeWidgetItem *, QVariant) {return false; }
    virtual bool deleteElement(QVariant ID);
    virtual bool canBeDeleted(QVariant ID);
    virtual void refreshID(int, int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified(bool removeDeleted);

    CalendarioPersonaLst getAll(int IDEmpleado, bool includeDeleted);
    void updateCalendarFromData(CalendarioPersonaPtr dataFrom);
    void updateCalendarFromData(CalendarioPersonaLst dataList);

    void updateCalendarWithNewIDEmpleado(int oldId, int newId);

    CalendarioPersonaPtr get(int IDEmpleado, int Dia, int HoraInicio, int HoraFin, bool includeDeleted);
signals:
    
public slots:
    
private:
    QList<CalendarioPersonaPtr> m_Calendarios;
};

typedef boost::shared_ptr<CalendarioPersonas> CalendarioPersonasPtr;

#endif // CALENDARIOPERSONAS_H
