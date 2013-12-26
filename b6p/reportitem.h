#ifndef REPORTITEM_H
#define REPORTITEM_H

#include <QObject>
#include "planificacionsubsector.h"
#include <boost/shared_ptr.hpp>

class ReportItem : public QObject
{
    Q_OBJECT
public:
    explicit ReportItem(QObject *parent = 0);
    virtual ~ReportItem();

    void addReference(PlanificacionSubSectorPtr reference);

    NullableField<QDate> date();
    double hours();
    EmpleadoPtr employee();
signals:

public slots:

private:
    QList<PlanificacionSubSectorPtr> references;
};

typedef boost::shared_ptr<ReportItem> ReportItemPtr;

#endif // REPORTITEM_H
