#ifndef CALENDARIOPERSONA_H
#define CALENDARIOPERSONA_H

#include <QObject>
#include <QTime>
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
    NullableField<QTime>& HoraIngreso();
    NullableField<QTime>& HoraEgreso();

/*    void Dia(NullableField<int> value);
    void IDEmpleado(NullableField<int> value);
    void HoraIngreso(NullableField<QTime> value);
    void HoraEgreso(NullableField<QTime> value);*/

    virtual RecordPtr asRecordPtr();
    bool EqualsTo(CalendarioPersonaPtr other);
    void updateWith(CalendarioPersonaPtr other);

signals:
    
public slots:
    
private:
    NullableField<int> m_Dia;
    NullableField<int> m_IDEmpleado;
    NullableField<QTime> m_HoraIngreso;
    NullableField<QTime> m_HoraEgreso;
};

#endif // CALENDARIOPERSONA_H
