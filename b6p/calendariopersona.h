#ifndef CALENDARIOPERSONA_H
#define CALENDARIOPERSONA_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"

class CalendarioPersona;
typedef boost::shared_ptr<CalendarioPersona> CalendarioPersonaPtr;
typedef boost::shared_ptr<QList<CalendarioPersonaPtr> > CalendarioPersonaLst;


class CalendarioPersona : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit CalendarioPersona(QObject *parent = 0);
    
    NullableField<int>& Dia();
    NullableField<int>& IDEmpleado();
    NullableField<int>& HoraIngreso();
    NullableField<int>& HoraEgreso();

    virtual RecordPtr asRecordPtr();
    virtual bool isEqualsTo(RecordPtr record);
    bool EqualsTo(CalendarioPersonaPtr other);
    void updateWith(CalendarioPersonaPtr other);

    void updateIDEmpleado(int newId);
    bool canWork(int Dia, int HoraInicio, int HoraFin);

signals:
    
public slots:
    
private:
    NullableField<int> m_Dia;
    NullableField<int> m_IDEmpleado;
    NullableField<int> m_HoraIngreso;
    NullableField<int> m_HoraEgreso;
};

#endif // CALENDARIOPERSONA_H
