#include "calendariopersonas.h"

CalendarioPersonas::CalendarioPersonas(QObject *parent) :
    ACollection(tr("Employee availability"), parent)
{
}

QString CalendarioPersonas::getSqlString()
{
    return "select Dia, IDEmpleado, HoraIngreso, HoraEgreso from calendariopersonas;";
}

void CalendarioPersonas::addRecord(Record &record)
{
    CalendarioPersonaPtr c(new CalendarioPersona(this));

    c->Dia().setValue(record["Dia"].toInt());
    c->IDEmpleado().setValue(record["IDEmpleado"].toInt());
    c->HoraIngreso().setValue(record["HoraIngreso"].toTime());
    c->HoraEgreso().setValue(record["HoraEgreso"].toTime());
    c->setInitialized();
    m_Calendarios.push_back(c);
}

QString CalendarioPersonas::getDeleteStatement()
{
    return "delete from calendariopersonas where Dia = :Dia and IDEmpleado = :IDEmpleado;";
}

QString CalendarioPersonas::getUpdateStatement()
{
    return "update calendariopersonas set HoraIngreso = :HoraIngreso, HoraEgreso = :HoraEgreso "
            " where Dia = :Dia and IDEmpleado = :IDEmpleado;";
}

QString CalendarioPersonas::getInsertStatement()
{
    return "insert into calendariopersonas "
            " (Dia, IDEmpleado, HoraIngreso, HoraEgreso) "
            " values "
            " (:Dia, :IDEmpleado, :HoraIngreso, :HoraEgreso);";
}

RecordSet CalendarioPersonas::getRecords(RecordStatus status)
{
    RecordSet res(new QList<RecordPtr>());
    foreach(CalendarioPersonaPtr c, m_Calendarios)
    {
        switch (status)
        {
        case NEW:
            if (c->isNew())
                res->push_back(c->asRecordPtr());
            break;
        case MODIFIED:
            if (c->isModified())
                res->push_back(c->asRecordPtr());
            break;
        case DELETED:
            if (c->isDeleted())
                res->push_back(c->asRecordPtr());
            break;
        default:
            break;
        }
    }
    return res;
}

void CalendarioPersonas::defineHeaders(QStringList &list)
{
}

void CalendarioPersonas::fillData(QTreeWidget &tree)
{
}

bool CalendarioPersonas::addNew()
{
}

bool CalendarioPersonas::edit(QVariant ID)
{
}

bool CalendarioPersonas::deleteElement(QVariant ID)
{
}

CalendarioPersonaLst CalendarioPersonas::getAll(int IDEmpleado)
{
    CalendarioPersonaLst res(new QList<CalendarioPersonaPtr>());
    foreach (CalendarioPersonaPtr cal, m_Calendarios)
    {
        if (cal->IDEmpleado().value() == IDEmpleado)
            res->push_back(cal);
    }
    return res;
}

void CalendarioPersonas::updateCalendarFromData(CalendarioPersonaPtr dataFrom)
{
    CalendarioPersonaLst cp = getAll(dataFrom->IDEmpleado().value());
    foreach(CalendarioPersonaPtr c, *cp)
    {
        if (c->EqualsTo(dataFrom))
        {aca esta rompiendo el shared pointer.
            c->updateWith(dataFrom);
            return;
        }
    }
}
