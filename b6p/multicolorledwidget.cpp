#include "multicolorledwidget.h"

#include <QPainter>
#include <QsLog.h>

MulticolorLedWidget::MulticolorLedWidget(QWidget *parent) : QWidget(parent)
{

}

void MulticolorLedWidget::setBackgroundColor(QColor color)
{
    m_BackgroundColor = color;
}

QColor MulticolorLedWidget::backgroundColor() const
{
    return m_BackgroundColor;
}

void MulticolorLedWidget::setLedColor(QColor color)
{
    m_LedColor = color;
}

QColor MulticolorLedWidget::ledColor() const
{
    return m_LedColor;
}


void MulticolorLedWidget::paintEvent(QPaintEvent *paintEvt)
{
    QLOG_TRACE_FN();
    QPainter painter(this);
    // Paint background
    painter.drawRect(rect());
    painter.fillRect(rect(), m_BackgroundColor);

    // paint led
    painter.setBrush(QBrush(m_LedColor));
    painter.drawEllipse(rect());
}
