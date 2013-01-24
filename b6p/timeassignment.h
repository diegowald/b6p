#ifndef TIMEASSIGNMENT_H
#define TIMEASSIGNMENT_H

#include <QWidget>

namespace Ui {
class TimeAssignment;
}

class TimeAssignment : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimeAssignment(QWidget *parent = 0);
    ~TimeAssignment();
    
private:
    Ui::TimeAssignment *ui;
};

#endif // TIMEASSIGNMENT_H
