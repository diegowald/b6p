#include "timeassignment.h"

#include <QTime>
#include <QPainter>
#include <QDebug>

TimeAssignment::TimeAssignment(QWidget *parent) :
    QWidget(parent)
{
    m_BackgroundColor = QColor(255, 255, 50);
    m_TimelineColor = QColor(100, 100, 100);
    m_AssignmentColor = QColor(230, 12, 56);
    m_HorizontalGap = 10;
    m_TimelineHeight = 6;
    m_AssignmentHeight = 12;
    m_FontSize = 10;
    m_InitialTimeline.setDate(QDate::currentDate());
    m_InitialTimeline.setTime(QTime(0, 0, 0, 0));

    m_FinalTimeline.setDate(QDate::currentDate());
    m_FinalTimeline.setTime(QTime(23, 59, 59, 0));

    m_StartAssignment.setDate(QDate::currentDate());
    m_StartAssignment.setTime(QTime(12, 0, 0, 0));

    m_EndAssignment.setDate(QDate::currentDate());
    m_EndAssignment.setTime(QTime(16, 0, 0, 0));
}

TimeAssignment::~TimeAssignment()
{
}

void TimeAssignment::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    // Paint background
    painter.drawRect(rect());
    painter.fillRect(rect(), m_BackgroundColor);

    // Paint Background timeline
    QRectF timeline(m_HorizontalGap, (height() - m_TimelineHeight) / 2, width() - 2 * m_HorizontalGap, m_TimelineHeight);
    painter.fillRect(timeline, m_TimelineColor);
    painter.setPen(m_TimelineColor);
    painter.drawRect(timeline);
    //painter.drawArc(10, 10, 10, 10, 0, 16*360);

    // Paint Background timeline references
    int timeWidth = timeline.width();
    // Suponemos que hay 10 divisiones;
    float slice = timeWidth / 10.0;
    for (int i = 0; i <= 10; i++)
    {
        float x1 = timeline.left() + i * slice;
        int y1 = (height() + m_TimelineHeight) / 2;
        painter.drawLine(x1, y1, x1, y1 + m_TimelineHeight);
    }

    // Paint Background times
    for (int i = 0; i <= 10; i++)
    {
        int x1 = timeline.left() + i * slice;
        int y1 = (height() / 2) + m_TimelineHeight + m_FontSize;
        QFont f = painter.font();
        f.setPixelSize(m_FontSize);
        painter.setFont(f);
        painter.drawText(x1, y1, QString::number(i));
    }

    // Paint Time Assignment
    // Supongamos que es desde las 3 hasta las 6
    //QRectF assignment(m_HorizontalGap + slice * 3, (height() / 2) - 5, slice * (6 - 3), 10);
    QRectF assignment(m_HorizontalGap + time2position(m_StartAssignment, timeline.width()),
                      (height() - m_AssignmentHeight) / 2,
                      delta2screen(m_EndAssignment.toMSecsSinceEpoch() - m_StartAssignment.toMSecsSinceEpoch(), timeline.width()),
                      m_AssignmentHeight);

    painter.fillRect(assignment, m_AssignmentColor);
    painter.setPen(m_AssignmentColor);
    painter.drawRect(assignment);
}

float TimeAssignment::time2position(QDateTime time, float w)
{
    return delta2screen(time.toMSecsSinceEpoch() - m_InitialTimeline.toMSecsSinceEpoch(), w);
}

float TimeAssignment::delta2screen(float delta, float w)
{
    return delta * w / (m_FinalTimeline.toMSecsSinceEpoch() - m_InitialTimeline.toMSecsSinceEpoch());
}


void TimeAssignment::setBackgroundColor(QColor color)
{
    m_BackgroundColor = color;
    repaint();
}

QColor TimeAssignment::backgroundColor() const
{
    return m_BackgroundColor;
}

void TimeAssignment::setTimeLineColor(QColor color)
{
    m_TimelineColor = color;
    repaint();
}

QColor TimeAssignment::timeLineColor() const
{
    return m_TimelineColor;
}

void TimeAssignment::setAssignmentColor(QColor color)
{
    m_AssignmentColor = color;
    repaint();
}

QColor TimeAssignment::assignmentColor() const
{
    return m_AssignmentColor;
}

void TimeAssignment::setAssignmentHeight(int value)
{
    m_AssignmentHeight = value;
    repaint();
}

int TimeAssignment::AssignmentHeight() const
{
    return m_AssignmentHeight;
}

void TimeAssignment::setHorizontalGap(int value)
{
    m_HorizontalGap = value;
    repaint();
}

int TimeAssignment::horizontalGap() const
{
    return m_HorizontalGap;
}

void TimeAssignment::setTimeLineHeight(int value)
{
    m_TimelineHeight = value;
    repaint();
}

int TimeAssignment::timelineHeight() const
{
    return m_TimelineHeight;
}

void TimeAssignment::setFontSize(int value)
{
    m_FontSize = value;
    repaint();
}

int TimeAssignment::fontSize() const
{
    return m_FontSize;
}

void TimeAssignment::setInitialTimeline(QDateTime value)
{
    m_InitialTimeline = value;
    repaint();
}

QDateTime TimeAssignment::initialTimeline() const
{
    return m_InitialTimeline;
}

void TimeAssignment::setFinalTimeline(QDateTime value)
{
    m_FinalTimeline = value;
    repaint();
}

QDateTime TimeAssignment::finalTimeline() const
{
    return m_FinalTimeline;
}

void TimeAssignment::setStartAssignment(QDateTime value)
{
    qDebug() << value.toString();
    m_StartAssignment = value;
    repaint();
}

QDateTime TimeAssignment::startAssignment() const
{
    return m_StartAssignment;
}

void TimeAssignment::setEndAssignment(QDateTime value)
{
    m_EndAssignment = value;
    repaint();
}

QDateTime TimeAssignment::endAssignment() const
{
    return m_EndAssignment;
}
