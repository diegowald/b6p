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
    
    virtual QString getSqlString();
    virtual void addRecord(Record &record);
    virtual QString getDeleteStatement();
    virtual QString getUpdateStatement();
    virtual QString getInsertStatement();
    virtual RecordSet getRecords(RecordStatus status);
    virtual void defineHeaders(QStringList &list) ;
    virtual void fillData(QTreeWidget &tree);
    virtual bool addNew();
    virtual void edit(QVariant ID);
    virtual void deleteElement(QVariant ID);

    CalendarioPersonaLst getAll(int IDEmpleado);

signals:
    
public slots:
    
private:
    QList<CalendarioPersonaPtr> m_Calendarios;
};

typedef boost::shared_ptr<CalendarioPersonas> CalendarioPersonasPtr;

#endif // CALENDARIOPERSONAS_H
