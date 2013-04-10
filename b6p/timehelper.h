#ifndef TIMEHELPER_H
#define TIMEHELPER_H
#include <QTime>

class TimeHelper
{
public:
    static QTime SecondsToQTime(int Seconds);
    static QString SecondsToString(int Seconds);
};

#endif // TIMEHELPER_H
