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

    c->Dia(NullableField<int>(record["Dia"].toInt()));
    c->IDEmpleado(NullableField<int>(record["IDEmpleado"].toInt()));
    c->HoraIngreso(NullableField<QTime>(record["HoraIngreso"].toTime()));
    c->HoraEgreso(NullableField<QTime>(record["HoraEgreso"].toTime()));

    m_Calendarios.push_back(c);
}

void CalendarioPersonas::saveData()
{
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

void CalendarioPersonas::edit(QVariant ID)
{
}

void CalendarioPersonas::deleteElement(QVariant ID)
{
}

CalendarioPersonaLst CalendarioPersonas::getAll(int IDEmpleado)
{
    CalendarioPersonaLst res(new QList<CalendarioPersonaPtr>());
    foreach (CalendarioPersonaPtr cal, m_Calendarios)
    {
        if (*cal->IDEmpleado().value() == IDEmpleado)
            res->push_back(cal);
    }
    return res;
}
