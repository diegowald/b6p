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
