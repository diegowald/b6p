/****************************************************************************
**
** Copyright (C) 2013 MKSIngenieria and/or its subsidiary(-ies).
**
** This file is part of the Big 6 Planner.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "timeassignment.h"

#include <QTime>
#include <QPainter>
#include <QsLog.h>
#include "datastore.h"

TimeAssignmentSlot::TimeAssignmentSlot()
{
    startAssignment = 0;
    endAssignment = 0;
    idSector = 0;
    idSubSector = 0;
}

QColor TimeAssignmentSlot::assignmentColor() const
{
    QColor color;
    switch (idSector)
    {
    case 1: //|Entrenamiento||1|1|1
        color = Qt::magenta;
        break;
    case 2: //|Cocina||1|1|1
        color = Qt::black;
        break;
    case 3: //|Cajas||1|1|1
        color = Qt::red;
        break;
    case 4: //|Cafeteria||1|1|1
        color = Qt::darkGreen;
        break;
    case 5: //|Salon||1|1|1
        color = Qt::blue;
        break;
    case 6: //|Depositos||1|1|1
    case 7: //|Eventos||1|1|1
    case 8: //|Supervisor||1|0|1
    case 9: //|Gerencia||1|0|1
    default:
        color = Qt::magenta;
        break;
    }
    return color;
}

QString TimeAssignmentSlot::label() const
{
    QString lbl = "";
    if (idSector != 0)
    {
        lbl = DataStore::instance()->getSectores()->getSector(idSector)->Nombre().value();
    }
    if (idSubSector != 0)
    {
        QString lblSS = DataStore::instance()->getSubSectores()->getSubSector(idSubSector)->Nombre().value();
        lbl += lblSS.length() > 0 ? " - " : "";
        lbl += lblSS;
    }
    return lbl;
}

TimeAssignment::TimeAssignment(QWidget *parent) :
    QWidget(parent)
{
    QLOG_TRACE_FN();
    m_BackgroundColor = QColor(255, 255, 255);
    m_TimelineColor = Qt::lightGray;
    m_HorizontalGap = 10;
    m_TimelineHeight = 4;
    m_AssignmentHeight = 6;
    m_FontSize = 10;
    m_InitialTimeline = 0;
    m_FinalTimeline = 86400;

    m_paintBackgroundReferences = true;
    m_paintVerticalGrid = false;
    m_showBackgroundText = false;
    m_HollowTimeLine = false;
    m_Assignments.clear();
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

    delta = (delta == 0) ? 1 : delta;
    return delta;
}

void TimeAssignment::paintEvent(QPaintEvent *)
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

    // Paint assignments.
    foreach (TimeAssignmentSlot assignment, m_Assignments)
    {
        QRectF a(timeline.left() + time2position(assignment.startAssignment, timeline.width()),
                          (height() - m_AssignmentHeight) / 2,
                          delta2screen(assignment.endAssignment - assignment.startAssignment, timeline.width()),
                          m_AssignmentHeight);

        painter.fillRect(a, assignment.assignmentColor());
        painter.setPen(assignment.assignmentColor());
        painter.drawRect(a);

        QString lbl = assignment.label();
        if (lbl.length() > 0)
        {
            qreal x1 = timeline.left() + time2position(assignment.startAssignment, timeline.width());
            int y1 = (height() / 2) - m_TimelineHeight;// - m_FontSize;
            QFont f = painter.font();
            f.setPixelSize(m_FontSize);
            painter.setFont(f);
            painter.drawText(x1, y1, lbl);
        }
    }
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

void TimeAssignment::addAssignment(TimeAssignmentSlot assignment)
{
    m_Assignments.push_back(assignment);
}

void TimeAssignment::clearAssignments()
{
    m_Assignments.clear();
}
