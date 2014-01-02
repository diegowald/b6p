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
#ifndef TIMEASSIGNMENT_H
#define TIMEASSIGNMENT_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>

class TimeAssignment : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignment(QWidget *parent = 0);
    ~TimeAssignment();
    
    void setBackgroundColor(QColor color);
    QColor backgroundColor() const;

    void setTimeLineColor(QColor color);
    QColor timeLineColor() const;

    void setAssignmentColor(QColor color);
    QColor assignmentColor() const;

    void setAssignmentHeight(int value);
    int AssignmentHeight() const;

    void setHorizontalGap(int value);
    int horizontalGap() const;

    void setTimeLineHeight(int value);
    int timelineHeight() const;

    void setFontSize(int value);
    int fontSize() const;

    void setInitialTimeline(int seconds);
    int initialTimeline() const;

    void setFinalTimeline(int seconds);
    int finalTimeline() const;

    int startAssignment1() const;
    int endAssignment1() const;

    int startAssignment2() const;
    int endAssignment2() const;

    bool PaintVerticalGrid();
    void setPaintVerticalGrid(bool paint);
    bool PaintBackgroundReferences();
    void setPaintBackgroundReferences(bool paint);
    bool ShowBackgroundText();
    void setShowBackgroundText(bool show);
    void setHollowTimeLine(bool hollow);
    bool HollowTimeLine() const;

public slots:
    void setStartAssignment(int seconds);
    void setEndAssignment(int seconds);
    void setStartAssignment2(int seconds);
    void setEndAssignment2(int seconds);

protected:
    void paintEvent(QPaintEvent *event);

    qreal time2position(int seconds, float w);
    qreal delta2screen(qreal delta, float w);
    int getNumberOfDivisions();
private:
    QColor m_BackgroundColor;
    QColor m_TimelineColor;
    QColor m_AssignmentColor;
    int m_HorizontalGap;
    int m_TimelineHeight;
    int m_AssignmentHeight;
    int m_FontSize;
    int m_InitialTimeline;
    int m_FinalTimeline;
    int m_StartAssignment;
    int m_EndAssignment;
    int m_StartAssignment2;
    int m_EndAssignment2;
    bool m_paintBackgroundReferences;
    bool m_showBackgroundText;
    bool m_paintVerticalGrid;
    bool m_HollowTimeLine;
};

#endif // TIMEASSIGNMENT_H
