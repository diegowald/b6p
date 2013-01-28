#ifndef DAYS_H
#define DAYS_H
#include <QString>

enum DAYS
{
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

class Days
{
public:
    static QString Days2String(DAYS day);
    static DAYS String2Day(QString day);
};

#endif // DAYS_H
