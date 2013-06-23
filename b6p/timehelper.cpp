#include "timehelper.h"
#include <QsLog.h>


QTime TimeHelper::SecondsToQTime(int Seconds)
{
    QLOG_TRACE() << "QTime TimeHelper::SecondsToQTime(int Seconds)";
    int secs = Seconds;
    int hours = secs / 3600;
    secs -= (hours * 3600);
    int minutes = secs / 60;
    secs -= (minutes * 60);

    return QTime(hours, minutes, secs);
}

QString TimeHelper::SecondsToString(int Seconds)
{
    QLOG_TRACE() << "QString TimeHelper::SecondsToString(int Seconds)";

    if (Seconds == 86400)
        return "24:00";

    QTime time = SecondsToQTime(Seconds);
    return time.toString("HH:mm");
}
