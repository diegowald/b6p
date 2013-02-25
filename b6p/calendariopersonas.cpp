#include "calendariopersonas.h"

CalendarioPersonas::CalendarioPersonas(QObject *parent) :
    ACollection(tr("Employee availability"), false, parent)
{
}

CalendarioPersonas::~CalendarioPersonas()
{
}

QString CalendarioPersonas::getSqlString()
{
    return QString("select Dia, IDEmpleado, HoraIngreso, HoraEgreso from calendariopersonas ")
            + QString(" where RecordStatus <> ") + QString::number(RECORD_DELETED) + QString(";");
}

void CalendarioPersonas::addRecord(Record &record)
{
    CalendarioPersonaPtr c(new CalendarioPersona(this));

    c->Dia().setValue(record["Dia"].toInt());
    c->IDEmpleado().setValue(record["IDEmpleado"].toInt());
    c->HoraIngreso().setValue(record["HoraIngreso"].toInt());
    c->HoraEgreso().setValue(record["HoraEgreso"].toInt());
    c->setInitialized();
    m_Calendarios.push_back(c);
}

QString CalendarioPersonas::getDeleteStatement()
{
    return QString("update calendariopersonas set RecordStatus = %1 where Dia = :Dia and IDEmpleado = :IDEmpleado;").arg(RECORD_DELETED);
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

CalendarioPersonaLst CalendarioPersonas::getAll(int IDEmpleado, bool includeDeleted)
{
    CalendarioPersonaLst res(new QList<CalendarioPersonaPtr>());
    foreach (CalendarioPersonaPtr cal, m_Calendarios)
    {
        qDebug() << cal->IDEmpleado().value();
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
    CalendarioPersonaPtr c(new CalendarioPersona(this));
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
