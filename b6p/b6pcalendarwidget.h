#ifndef B6PCALENDARWIDGET_H
#define B6PCALENDARWIDGET_H

#include <QCalendarWidget>
#include "planificacionesdias.h"


class B6PCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit B6PCalendarWidget(QWidget *parent = 0);

protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

signals:

public slots:

};

#endif // B6PCALENDARWIDGET_H
