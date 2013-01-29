#include "calendariopersonas.h"

CalendarioPersonas::CalendarioPersonas(QObject *parent) :
    ACollection(tr("Employee availability"), parent)
{
}

void CalendarioPersonas::loadData()
{
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
