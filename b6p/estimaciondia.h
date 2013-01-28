#ifndef ESTIMACIONDIA_H
#define ESTIMACIONDIA_H

#include <QObject>
#include <QDate>
#include <boost/shared_ptr.hpp>
#include "nullablefield.h"

class EstimacionDia : public QObject
{
    Q_OBJECT
public:
    explicit EstimacionDia(QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    NullableField<QDate> m_Dia;
    NullableField<int> m_EstimacionHoras;
};

typedef boost::shared_ptr<EstimacionDia> EstimacionDiaPtr;
#endif // ESTIMACIONDIA_H
