#include "b6pcalendarwidget.h"
#include <QPainter>
#include <QStaticText>

B6PCalendarWidget::B6PCalendarWidget(QWidget *parent) :
    QCalendarWidget(parent)
{
    this->setGridVisible(true);
}

void B6PCalendarWidget::setDataModel(boost::shared_ptr<PlanificacionesDias> Model)
{
    model =  Model;
}

void B6PCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    QCalendarWidget::paintCell(painter, rect, date);
    PlanificacionDiaPtr planificacion = model->getByDay(date, false);
    if ((planificacion != PlanificacionDiaPtr()) && (rect.width() > 50) && (rect.height() > 50))
    {     // When the conditions are matched, passed QDate is drawn as we like.
        int hsPlanificadas = 0;
        int hsEstimadas = 0;
        QString estado = ""; //<b>" + QString::number(date.day()) + "</b>";
        QString estimado = "";
        QString planificado = "";
        hsPlanificadas = planificacion->HorasPlanificadas();
        EstimacionDiaPtr estimacion = planificacion->Estimacion();
        if (estimacion != EstimacionDiaPtr())
        {
            hsEstimadas = estimacion->EstimacionHoras().value();
        }

        estado = planificacion->Estado();
        estimado = QString("E:%1").arg(hsEstimadas);
        planificado = QString("P:%2").arg(hsPlanificadas);

        painter->save();
        painter->setPen(QColor(64, 64, 64, 192));
        //        painter->fillRect(rect, QBrush(QColor(255, 128, 64, 255)));
        //        painter->drawEllipse(rect);   // here we draw n ellipse and the day--

        QFont font = painter->font();
        font.setPixelSize(12);
        painter->setFont(font);

        QTextOption option;
        option.setAlignment(Qt::AlignLeft | Qt::AlignTop);
        QStaticText text;
        text.setTextOption(option);
        text.setText(estado);
        painter->drawStaticText(rect.left(), rect.top(), text);

        option.setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        text.setText(estimado);
        painter->drawStaticText(rect.left(), rect.bottom() - 13, text);

        option.setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        text.setText(planificado);
        painter->drawStaticText(rect.right() - rect.width() / 2,
                                rect.bottom() - 13, text);
        //           painter->drawText(rect, Qt::TextSingleLine, Qt::AlignCenter,QString::number(date.day()));
        painter->restore();
    }
}
