#include "parametro.h"
#include <QsLog.h>

Parametro::Parametro(QObject *parent) :
    QObject(parent)
{
    QLOG_TRACE() << "Parametro::Parametro(QObject *parent)";
}
