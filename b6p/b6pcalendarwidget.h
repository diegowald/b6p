#ifndef B6PCALENDARWIDGET_H
#define B6PCALENDARWIDGET_H

#include <QCalendarWidget>
#include "planificacionesdias.h"


class B6PCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit B6PCalendarWidget(QWidget *parent = 0);
    void setDataModel(boost::shared_ptr<PlanificacionesDias> Model);

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

signals:

public slots:

private:
    boost::shared_ptr<PlanificacionesDias> model;
};

#endif // B6PCALENDARWIDGET_H
