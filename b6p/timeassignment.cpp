#include "timeassignment.h"

#include <QTime>
#include <QPainter>
#include <QsLog.h>


TimeAssignment::TimeAssignment(QWidget *parent) :
    QWidget(parent)
{
    QLOG_TRACE_FN();
    m_BackgroundColor = QColor(255, 255, 255);
    m_TimelineColor = Qt::lightGray;
    m_AssignmentColor = Qt::darkRed;
    m_HorizontalGap = 10;
    m_TimelineHeight = 4;
    m_AssignmentHeight = 6;
    m_FontSize = 10;
    m_InitialTimeline = 0;
    m_FinalTimeline = 86400;
    m_StartAssignment = 0 * 3600;
    m_EndAssignment = 24 * 3600;

    m_paintBackgroundReferences = true;
    m_paintVerticalGrid = false;
    m_showBackgroundText = false;
    m_HollowTimeLine = false;
}

bool TimeAssignment::PaintBackgroundReferences()
{
    QLOG_TRACE_FN();
    return m_paintBackgroundReferences;
}

void TimeAssignment::setPaintBackgroundReferences(bool paint)
{
    QLOG_TRACE_FN();
    m_paintBackgroundReferences = paint;
    repaint();
}

bool TimeAssignment::ShowBackgroundText()
{
    QLOG_TRACE_FN();
    return m_showBackgroundText;
}

void TimeAssignment::setShowBackgroundText(bool show)
{
    QLOG_TRACE_FN();
    m_showBackgroundText = show;
    repaint();
}

bool TimeAssignment::PaintVerticalGrid()
{
    QLOG_TRACE_FN();
    return m_paintVerticalGrid;
}

void TimeAssignment::setPaintVerticalGrid(bool paint)
{
    QLOG_TRACE_FN();
    m_paintVerticalGrid = paint;
    repaint();
}

TimeAssignment::~TimeAssignment()
{
    QLOG_TRACE_FN();
}

int TimeAssignment::getNumberOfDivisions()
{
    QLOG_TRACE_FN();
    // In msecs:
    int delta = finalTimeline() - initialTimeline();
    // In hours
    delta /= 3600;

    //delta ++;

    delta = (delta == 0) ? 1 : delta;
    return delta;
}

void TimeAssignment::paintEvent(QPaintEvent */*event*/)
{
    QLOG_TRACE_FN();
    QPainter painter(this);
    // Paint background
    painter.drawRect(rect());
    painter.fillRect(rect(), m_BackgroundColor);

    // Paint Background timeline
    QRectF timeline(m_HorizontalGap, (height() - m_TimelineHeight) / 2, width() - 2 * m_HorizontalGap, m_TimelineHeight);
    if (!m_HollowTimeLine)
        painter.fillRect(timeline, m_TimelineColor);
    painter.setPen(m_TimelineColor);
    painter.drawRect(timeline);

    if (m_paintBackgroundReferences || m_paintVerticalGrid)
    {
        // Paint Background timeline references
        qreal timeWidth = timeline.width();
        int numberOfDivisions = getNumberOfDivisions();
        qreal slice = timeWidth / numberOfDivisions;
        for (int i = 0; i <= numberOfDivisions; i++)
        {
            qreal x1 = timeline.left() + i * slice;
            int y1 = 0;
            int h = height();
            if (m_paintBackgroundReferences)
            {
                y1 = (height() + m_TimelineHeight) / 2;
                h = y1 + m_TimelineHeight;
            }

            painter.drawLine(x1, y1, x1, h);
        }

        // Paint Background times
        if (m_showBackgroundText)
        {
            for (int i = 0; i <= numberOfDivisions; i+=2)
            {
                int aux = m_InitialTimeline;
                aux += (i * 3600);
                qreal x1 = timeline.left() + i * slice;
                int y1 = (height() / 2) + m_TimelineHeight + m_FontSize;
                QFont f = painter.font();
                f.setPixelSize(m_FontSize);
                painter.setFont(f);
                QTime tmp;
                tmp.setHMS(0, 0, 0);
                tmp = tmp.addSecs(aux);
                painter.drawText(x1, y1, tmp.toString("H:mm"));
            }
        }
    }

    // Paint Time Assignment
    QRectF assignment(timeline.left() + time2position(m_StartAssignment, timeline.width()),
                      (height() - m_AssignmentHeight) / 2,
                      delta2screen(m_EndAssignment - m_StartAssignment, timeline.width()),
                      m_AssignmentHeight);

    painter.fillRect(assignment, m_AssignmentColor);
    painter.setPen(m_AssignmentColor);
    painter.drawRect(assignment);
}

qreal TimeAssignment::time2position(int seconds, float w)
{
    QLOG_TRACE_FN();
    return delta2screen(seconds - m_InitialTimeline, w);
}

qreal TimeAssignment::delta2screen(qreal delta, float w)
{
    QLOG_TRACE_FN();
    return delta * w / (m_FinalTimeline - m_InitialTimeline);
}


void TimeAssignment::setBackgroundColor(QColor color)
{
    QLOG_TRACE_FN();
    m_BackgroundColor = color;
    repaint();
}

QColor TimeAssignment::backgroundColor() const
{
    QLOG_TRACE_FN();
    return m_BackgroundColor;
}

void TimeAssignment::setTimeLineColor(QColor color)
{
    QLOG_TRACE_FN();
    m_TimelineColor = color;
    repaint();
}

QColor TimeAssignment::timeLineColor() const
{
    QLOG_TRACE_FN();
    return m_TimelineColor;
}

void TimeAssignment::setAssignmentColor(QColor color)
{
    QLOG_TRACE_FN();
    m_AssignmentColor = color;
    repaint();
}

QColor TimeAssignment::assignmentColor() const
{
    QLOG_TRACE_FN();
    return m_AssignmentColor;
}

void TimeAssignment::setAssignmentHeight(int value)
{
    QLOG_TRACE_FN();
    m_AssignmentHeight = value;
    repaint();
}

int TimeAssignment::AssignmentHeight() const
{
    QLOG_TRACE_FN();
    return m_AssignmentHeight;
}

void TimeAssignment::setHorizontalGap(int value)
{
    QLOG_TRACE_FN();
    m_HorizontalGap = value;
    repaint();
}

int TimeAssignment::horizontalGap() const
{
    QLOG_TRACE_FN();
    return m_HorizontalGap;
}

void TimeAssignment::setTimeLineHeight(int value)
{
    QLOG_TRACE_FN();
    m_TimelineHeight = value;
    repaint();
}

int TimeAssignment::timelineHeight() const
{
    QLOG_TRACE_FN();
    return m_TimelineHeight;
}

void TimeAssignment::setFontSize(int value)
{
    QLOG_TRACE_FN();
    m_FontSize = value;
    repaint();
}

int TimeAssignment::fontSize() const
{
    QLOG_TRACE_FN();
    return m_FontSize;
}

void TimeAssignment::setInitialTimeline(int seconds)
{
    QLOG_TRACE_FN();
    m_InitialTimeline = seconds;
    repaint();
}


int TimeAssignment::initialTimeline() const
{
    QLOG_TRACE_FN();
    return m_InitialTimeline;
}

void TimeAssignment::setFinalTimeline(int seconds)
{
    QLOG_TRACE_FN();
    m_FinalTimeline = seconds;
    repaint();
}

int TimeAssignment::finalTimeline() const
{
    QLOG_TRACE_FN();
    return m_FinalTimeline;
}

void TimeAssignment::setStartAssignment(int seconds)
{
    QLOG_TRACE_FN();
    m_StartAssignment = seconds;
    repaint();
}


int TimeAssignment::startAssignment() const
{
    QLOG_TRACE_FN();
    return m_StartAssignment;
}

void TimeAssignment::setEndAssignment(int seconds)
{
    QLOG_TRACE_FN();
    m_EndAssignment = seconds;
    repaint();
}

int TimeAssignment::endAssignment() const
{
    QLOG_TRACE_FN();
    return m_EndAssignment;
}

void TimeAssignment::setHollowTimeLine(bool hollow)
{
    QLOG_TRACE_FN();
    m_HollowTimeLine = hollow;
}

bool TimeAssignment::HollowTimeLine() const
{
    QLOG_TRACE_FN();
    return m_HollowTimeLine;
}
