#ifndef TIMEASSIGNMENT_H
#define TIMEASSIGNMENT_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>
#include <QDateTime>

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
    void setHorizontalGap(int value);
    int horizontalGap() const;
    void setTimeLineHeight(int value);
    int timelineHeight() const;
    void setFontSize(int value);
    int fontSize() const;
    void setInitialTimeline(QDateTime value);
    QDateTime initialTimeline() const;
    void setFinalTimeline(QDateTime value);
    QDateTime finalTimeline() const;
    void setStartAssignment(QDateTime value);
    QDateTime startAssignment() const;
    void setEndAssignment(QDateTime value);
    QDateTime endAssignment() const;

protected:
    void paintEvent(QPaintEvent *event);

    float time2position(QDateTime time, float w);
    float delta2screen(float delta, float w);
private:
    QColor m_BackgroundColor;
    QColor m_TimelineColor;
    QColor m_AssignmentColor;
    int m_HorizontalGap;
    int m_TimelineHeight;
    int m_AssignmentHeight;
    int m_FontSize;
    QDateTime m_InitialTimeline;
    QDateTime m_FinalTimeline;
    QDateTime m_StartAssignment;
    QDateTime m_EndAssignment;
};

#endif // TIMEASSIGNMENT_H
