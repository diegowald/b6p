#include "days.h"
#include <QObject>

QString Days::Days2String(DAYS day)
{
    switch (day)
    {
    case Sunday:
        return QObject::tr("Sunday");
        break;
    case Monday:
        return QObject::tr("Monday");
        break;
    case Tuesday:
        return QObject::tr("Tuesday");
        break;
    case Wednesday:
        return QObject::tr("Wednesday");
        break;
    case Thursday:
        return QObject::tr("Thursday");
        break;
    case Friday:
        return QObject::tr("Friday");
        break;
    case Saturday:
        return QObject::tr("Saturday");
        break;
    default:
        return "";
        break;
    }
}

DAYS Days::String2Day(QString day)
{
    if (day == QObject::tr("Sunday"))
        return Sunday;
    else if(day == QObject::tr("Monday"))
        return Monday;
    else if(day == QObject::tr("Tuesday"))
        return Tuesday;
    else if(day == QObject::tr("Wednesday"))
        return Wednesday;
    else if(day == QObject::tr("Thursday"))
        return Thursday;
    else if(day == QObject::tr("Friday"))
        return Friday;
    else if(day == QObject::tr("Saturday"))
        return Saturday;
    else
        return Sunday;
}
