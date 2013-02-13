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
    virtual void addRecord(Record &record);
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual void defineHeaders(QStringList &list) ;
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual bool edit(QVariant ID);
    virtual bool deleteElement(QVariant ID);
    virtual void refreshID(int) {}
    virtual void saveDependants() {}
    virtual void setStatusToUnmodified();

    CalendarioPersonaLst getAll(int IDEmpleado);
    void updateCalendarFromData(CalendarioPersonaPtr dataFrom);
    void updateCalendarFromData(CalendarioPersonaLst dataList);

    void updateCalendarWithNewIDEmpleado(int oldId, int newId);

    CalendarioPersonaPtr get(int IDEmpleado, int Dia, QTime HoraInicio, QTime HoraFin);
signals:
    
public slots:
    
private:
    QList<CalendarioPersonaPtr> m_Calendarios;
};

typedef boost::shared_ptr<CalendarioPersonas> CalendarioPersonasPtr;

#endif // CALENDARIOPERSONAS_H
