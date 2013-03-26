#include "calendariopersonas.h"

CalendarioPersonas::CalendarioPersonas(QObject *parent) :
    ACollection(tr("Employee availability"),
                "Employee availability", false, parent)
{
}

CalendarioPersonas::~CalendarioPersonas()
{
}

QString CalendarioPersonas::getSelectFromMainDB()
{
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso, LastUpdate from calendariopersonas "
                   " where LastUpdate >= :LASTUPDATE ;");
}

QString CalendarioPersonas::getSqlString()
{
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso, sent from calendariopersonas "
            " where RecordStatus <> %1;").arg(RECORD_DELETED);
}

QString CalendarioPersonas::getSQLExistsInMainDB()
{
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso from calendariopersonas "
                   " where Dia = :Dia and IDEmpleado = :IDEmpleado; ");
}

void CalendarioPersonas::addRecord(RecordPtr record)
{
    CalendarioPersonaPtr c = boost::make_shared<CalendarioPersona>(this);

    c->Dia().setValue((*record)["Dia"].toInt());
    c->IDEmpleado().setValue((*record)["IDEmpleado"].toInt());
    c->HoraIngreso().setValue((*record)["HoraIngreso"].toInt());
    c->HoraEgreso().setValue((*record)["HoraEgreso"].toInt());
    c->setSentStatus((*record)["sent"].toInt() == 1);
    c->setInitialized();
    m_Calendarios.push_back(c);
}

void CalendarioPersonas::updateRecord(RecordPtr)
{
}

void CalendarioPersonas::deleteRecord(RecordPtr)
{
}

bool CalendarioPersonas::exists(RecordPtr)
{
    return false;
}

QString CalendarioPersonas::getDeleteStatement()
{
    return QString("update calendariopersonas set RecordStatus = %1 where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(RECORD_DELETED);
}

QString CalendarioPersonas::getUpdateStatement()
{
    return QString("update calendariopersonas set HoraIngreso = :HoraIngreso, HoraEgreso = :HoraEgreso, "
                   " RecordStatus = %1 "
                   " where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(RECORD_MODIFIED);
}

QString CalendarioPersonas::getInsertStatement()
{
    return QString("insert into calendariopersonas "
            " (Dia, IDEmpleado, HoraIngreso, HoraEgreso, RecordStatus) "
            " values "
            " (:Dia, :IDEmpleado, :HoraIngreso, :HoraEgreso, %1);").arg(RECORD_NEW);
}

RecordSet CalendarioPersonas::getRecords(RecordStatus status)
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
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

RecordSet CalendarioPersonas::getUnsent()
{
    RecordSet res = boost::make_shared<QList<RecordPtr> >();
    foreach(CalendarioPersonaPtr c, m_Calendarios)
    {
        if (c->isUnSent())
            res->push_back(c->asRecordPtr());
    }
    return res;
}

void CalendarioPersonas::defineHeaders(QStringList &)
{
}

void CalendarioPersonas::fillData(QTreeWidget &)
{
}

bool CalendarioPersonas::addNew()
{
    return false;
}

bool CalendarioPersonas::edit(QVariant)
{
    return false;
}

bool CalendarioPersonas::deleteElement(QVariant)
{
    return false;
}

bool CalendarioPersonas::canBeDeleted(QVariant)
{
    return false;
}

CalendarioPersonaLst CalendarioPersonas::getAll(int IDEmpleado, bool includeDeleted)
{
    CalendarioPersonaLst res = boost::make_shared<QList<CalendarioPersonaPtr> >();
    foreach (CalendarioPersonaPtr cal, m_Calendarios)
    {
        if (cal->IDEmpleado().value() == IDEmpleado)
        {
            if (!cal->isDeleted())
                res->push_back(cal);
            else
                if (includeDeleted)
                    res->push_back(cal);
        }
    }
    return res;
}

CalendarioPersonaPtr CalendarioPersonas::get(int IDEmpleado, int Dia, int HoraInicio, int HoraFin, bool includeDeleted)
{
    CalendarioPersonaLst all = getAll(IDEmpleado, false);
    foreach(CalendarioPersonaPtr c, *all)
    {
        if (c->canWork(Dia, HoraInicio, HoraFin))
        {
            if (!c->isDeleted())
                return c;
            else
            {
                if (includeDeleted)
                    return c;
            }
        }
    }
    return CalendarioPersonaPtr();
}

void CalendarioPersonas::updateCalendarFromData(CalendarioPersonaLst dataList)
{
    foreach (CalendarioPersonaPtr c, *dataList)
    {
        updateCalendarFromData(c);
    }
}

void CalendarioPersonas::updateCalendarFromData(CalendarioPersonaPtr dataFrom)
{
    CalendarioPersonaLst cp = getAll(dataFrom->IDEmpleado().value(), false);
    foreach(CalendarioPersonaPtr c, *cp)
    {
        if (c->EqualsTo(dataFrom))
        {
            c->updateWith(dataFrom);
            return;
        }
    }

    // Si llega aca es porque no hay un elemento
    CalendarioPersonaPtr c = boost::make_shared<CalendarioPersona>(this);
    c->Dia().setValue(dataFrom->Dia().value());
    c->IDEmpleado().setValue(dataFrom->IDEmpleado().value());
    c->updateWith(dataFrom);
    c->setNew();
    m_Calendarios.push_back(c);
    return;
}

void CalendarioPersonas::updateCalendarWithNewIDEmpleado(int oldId, int newId)
{
    CalendarioPersonaLst cal = getAll(oldId, false);
    foreach (CalendarioPersonaPtr cp, *cal)
    {
        cp->updateIDEmpleado(newId);
    }
}

void CalendarioPersonas::setStatusToUnmodified(bool removeDeleted)
{
    QList<CalendarioPersonaPtr> toDelete;
    foreach(CalendarioPersonaPtr c, m_Calendarios)
    {
        if (removeDeleted && c->isDeleted())
            toDelete.push_back(c);
        else
            c->setUnmodified();
    }
    foreach(CalendarioPersonaPtr c, toDelete)
    {
        m_Calendarios.removeOne(c);
    }
}
