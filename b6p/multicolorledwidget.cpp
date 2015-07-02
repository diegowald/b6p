#include "multicolorledwidget.h"

#include <QPainter>
#include <QsLog.h>

MulticolorLedWidget::MulticolorLedWidget(QWidget *parent) : QWidget(parent)
{
    QLOG_TRACE_FN();
    m_BackgroundColor = Qt::GlobalColor::white;
    //m_LedColor = Qt::GlobalColor::lightGray;
    m_LedColor = Qt::darkRed;

}

void MulticolorLedWidget::setBackgroundColor(QColor color)
{
    QLOG_TRACE_FN();
    m_BackgroundColor = color;
}

QColor MulticolorLedWidget::backgroundColor() const
{
    QLOG_TRACE_FN();
    return m_BackgroundColor;
}

void MulticolorLedWidget::setLedColor(QColor color)
{
    QLOG_TRACE_FN();
    m_LedColor = color;
}

QColor MulticolorLedWidget::ledColor() const
{
    QLOG_TRACE_FN();
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
    QRect circleRect(0, 0, 18, 18);
    circleRect.moveCenter(rect().center());
    painter.setBrush(QBrush(m_LedColor));
    painter.drawEllipse(circleRect);
}
