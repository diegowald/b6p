#ifndef ESTIMACIONDIA_H
#define ESTIMACIONDIA_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"

class EstimacionDia : public QObject, public IRecord
{
    Q_OBJECT
public:
    explicit EstimacionDia(bool isNew, QObject *parent = 0);

    NullableField<QDate> &Dia();
    NullableField<int> &EstimacionHoras();

    /*void Dia(NullableField<QDate> value);
    void EstimacionHoras(NullableField<int> value);*/

    virtual RecordPtr asRecordPtr();
signals:
    
public slots:
    
private:
    NullableField<QDate> m_Dia;
    NullableField<int> m_EstimacionHoras;
};

typedef boost::shared_ptr<EstimacionDia> EstimacionDiaPtr;
typedef boost::shared_ptr<QList<EstimacionDiaPtr> > EstimacionDiaLst;
#endif // ESTIMACIONDIA_H
